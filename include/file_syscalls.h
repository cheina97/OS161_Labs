#ifndef FILE_SYSCALLS_H
#define FILE_SYSCALLS_H

#include <types.h>

ssize_t sys_read(int filehandle, void* buf, size_t size);
ssize_t sys_write(int filehandle, const void* buf, size_t size);

#endif