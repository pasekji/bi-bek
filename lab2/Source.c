#include <stdio.h>

int main() {
	__asm {
			int 3
	}
	char buffer[20];
	printf("What is your name?\n");
	gets(buffer);
	printf("Hi, %s!\n", buffer);
	return 0;
}