#ifndef __SHELL_H__
#define __SHELL_H__

void initShell(void);
void startShell(void);

void addNewCmd(	unsigned char *cmd,
			int (*func)(int argc, unsigned char **argv),
			void (*help_func)(void),
			unsigned char* description);
            
#endif