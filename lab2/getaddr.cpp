#include <iostream>

int main()
{
    int address = 0;
    __asm
    {
		xor eax, eax
		mov eax, fs:[0x30]
		mov eax, [eax + 0x0C]
		mov eax, [eax + 0x14]
		mov eax, [eax]
		mov eax, [eax]
		mov eax, [eax + 0x10]
		mov address, eax
    }
    std::cout << "kernel32 address is: " << std::hex << address << std::endl;
    return 0;
}