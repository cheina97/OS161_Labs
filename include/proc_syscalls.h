#ifndef PROC_SYSCALL_H
#define PROC_SYSCALL_H
#include "addrspace.h"

void sys_exit(int n);
int sys_waitpid(pid_t pid);
pid_t sys_getpid(void);

#endif