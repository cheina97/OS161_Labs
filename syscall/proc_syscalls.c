#include "proc_syscalls.h"
#include "addrspace.h"
#include "thread.h"
#include "proc.h"
#include "lib.h"
#include "current.h"

void sys_exit(int n){
    kprintf("EXITING PID: %d\n",sys_getpid());
    struct proc *p=curthread->t_proc;
    p->status=n;
    proc_remthread(curthread);
    V(p->semSyncExit);
    thread_exit();
}

int sys_waitpid(pid_t pid){
    int status=proc_waitpid(pid);
    return status;
}

pid_t sys_getpid(){
    return curthread->t_proc->pid;
}