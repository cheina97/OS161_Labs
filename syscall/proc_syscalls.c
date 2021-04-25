#include "proc_syscalls.h"
#include "addrspace.h"
#include "thread.h"
#include "proc.h"
#include "lib.h"

void sys_exit(int n){
    (void)n;
    as_destroy(proc_getas());
    thread_exit();
    panic("NON HA FUNZIONATO LA SYSEXIT");
}
