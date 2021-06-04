#include "proc_syscalls.h"

#include <limits.h>
#include <uio.h>
#include <vfs.h>
#include <vnode.h>

#include "addrspace.h"
#include "current.h"
#include "lib.h"
#include "proc.h"
#include "thread.h"

#define STDIN_FILENO  0      /* Standard input */
#define STDOUT_FILENO 1      /* Standard output */
#define STDERR_FILENO 2      /* Standard error */

struct vnode *file_table[OPEN_MAX] = {NULL};
int last_desc = 3;
int total_desc = 3;

int sys_remove(char * pathname){
    kprintf("%s adsadada\n",pathname);
    return vfs_remove(pathname);
}

int sys_open(char *pathname, int flags) {
    if (total_desc == OPEN_MAX) return 1;
    struct vnode *v;
    int result;
    result = vfs_open(pathname, flags, 0, &v);
    if (result) {
        return result;
    }

    while (file_table[last_desc] != NULL) {
        if (OPEN_MAX == last_desc)
            last_desc = 3;
        else
            last_desc++;
    }
    file_table[last_desc] = v;
    total_desc++;
    return last_desc;
}
int sys_close(int fd) {
    if (fd <= 2 || fd >= OPEN_MAX) return 1;
    if(file_table[fd]==NULL) return -1;
    vfs_close(file_table[fd]);
    file_table[fd] = NULL;
    total_desc--;
    return 0;
}
ssize_t mysys_read(int fd, void *buf, size_t count) {
    if (fd == STDIN_FILENO) {
        kgets(buf, count);
        return count;
    } else {
        int result;
        struct iovec iov;
        struct uio ku;

        uio_kinit(&iov, &ku, buf, count, 0, UIO_READ);
        result = VOP_READ(file_table[fd], &ku);
        if (result) return result;
        return ku.uio_offset;
    }
}
ssize_t mysys_write(int fd, void *buf, size_t count) {
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        kprintf("%s",(char*)buf);
        return count;
    } else {
        int result;
        struct iovec iov;
        struct uio ku;

        uio_kinit(&iov, &ku, buf, count, 0, UIO_WRITE);
        result = VOP_WRITE(file_table[fd], &ku);
        if (result) return result;
        return ku.uio_offset;
    }
}

void sys_exit(int n) {
    kprintf("EXITING PID: %d\n", sys_getpid());
    struct proc *p = curthread->t_proc;
    p->status = n;
    proc_remthread(curthread);
    V(p->semSyncExit);
    thread_exit();
}

int sys_waitpid(pid_t pid) {
    int status = proc_waitpid(pid);
    return status;
}

pid_t sys_getpid() {
    return curthread->t_proc->pid;
}

