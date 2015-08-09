#include "main.h"

kkvm vm;

int main() {
	std::ios_base::sync_with_stdio(0);
	
	vm.RAM[0] = 0x0;
	vm.RAM[1] = 0x0;
	vm.RAM[2] = 0x1;
	vm.RAM[3] = 0x2;
	vm.RAM[4] = 0x190;
	vm.RAM[5] = 0x2;
	vm.RAM[6] = 0x20;
	vm.RAM[7] = 0x7;
	
	vm.run();
	
	return 0;
}
