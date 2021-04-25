#include <types.h>
#include "file_syscalls.h"
#include <lib.h>

static
void
backsp(void)
{
	putch('\b');
	putch(' ');
	putch('\b');
}

ssize_t sys_read(int filehandle, void* buf, size_t size) {
    size_t pos = 0;
	int ch;
    char *data=(char*)buf;
    (void)filehandle;

	while (1) {
		ch = getch();
		if (ch=='\n' || ch=='\r') {
			putch('\n');
			break;
		}

		/* Only allow the normal 7-bit ascii */
		if (ch>=32 && ch<127 && pos < size-1) {
			putch(ch);
			data[pos++] = ch;
		}
		else if ((ch=='\b' || ch==127) && pos>0) {
			/* backspace */
			backsp();
			pos--;
		}
		else if (ch==3) {
			/* ^C - return empty string */
			putch('^');
			putch('C');
			putch('\n');
			pos = 0;
			break;
		}
		else if (ch==18) {
			/* ^R - reprint input */
			data[pos] = 0;
			kprintf("^R\n%s", data);
		}
		else if (ch==21) {
			/* ^U - erase line */
			while (pos > 0) {
				backsp();
				pos--;
			}
		}
		else if (ch==23) {
			/* ^W - erase word */
			while (pos > 0 && data[pos-1]==' ') {
				backsp();
				pos--;
			}
			while (pos > 0 && data[pos-1]!=' ') {
				backsp();
				pos--;
			}
		}
		else {
			beep();
		}
	}

	data[pos] = 0;
    return size;
}

ssize_t sys_write(int filehandle, const void* buf, size_t size) {
    size_t i;
    char *data=(char*)buf;
    (void)filehandle;
    
    for (i=0; i<size; i++) {
		putch(data[i]);
	}
    return size;
}