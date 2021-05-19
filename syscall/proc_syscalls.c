#include "proc_syscalls.h"
#include "addrspace.h"
#include "thread.h"
#include "proc.h"
#include "lib.h"
#include "current.h"

void sys_exit(int n){
    struct proc *p=curthread->t_proc;
    p->status=n;
    proc_remthread(curthread);
    V(p->semSyncExit);
    thread_exit();
}
