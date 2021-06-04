#ifndef PROC_SYSCALL_H
#define PROC_SYSCALL_H
#include "addrspace.h"

void sys_exit(int n);
int sys_waitpid(pid_t pid);
pid_t sys_getpid(void);
int sys_open(char *pathname, int flags);
int sys_close(int fd);
ssize_t mysys_read(int fd, void *buf, size_t count);
ssize_t mysys_write(int fd, void *buf, size_t count);
int sys_remove(char * pathname);

#endif