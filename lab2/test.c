#include <stdio.h>

int main() {
	__asm {
		int 3
	}
	char buffer[20];
	printf("Zadej jmeno: ");
	gets(buffer);
	printf("Ahoj, %s\n", buffer);
	return 0;
}