/*
	Copyright 2015 Valeriy Kireev
	
	This file is part of kkvm.
	
	kkvm is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	kkvm is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with kkvm. If not, see <http://www.gnu.org/licenses/>.
*/

#include "main.h"

kkvm vm;

int main(int argc, char *argv[]) {
	std::ios_base::sync_with_stdio(0);
	
	/*
	//PROGRAM EXAMPLE
	
	vm.RAM[0] = 0x0;
	vm.RAM[1] = 0x0;
	vm.RAM[2] = 0x1;
	vm.RAM[3] = 0x2;    // push 0x1   ; 0x1
	vm.RAM[4] = 0x1;
	vm.RAM[5] = 0x4;    // dup        ; 0x1 0x1
	vm.RAM[6] = 0x2;    // push 0xa   ; 0x1 0x1 0xa
	vm.RAM[7] = 0xa;
	vm.RAM[8] = 0x6;    // deep 0x2   ; 0x1 0x1 0xa 0x1
	vm.RAM[9] = 0x2;
	vm.RAM[10] = 0x6;   // deep 0x2   ; 0x1 0x1 0xa 0x1 0x1
	vm.RAM[11] = 0x2;
	vm.RAM[12] = 0x7;   // add        ; 0x1 0x1 0xa 0x2
	vm.RAM[13] = 0x5;   // swap       ; 0x1 0x1 0x2 0xa
	vm.RAM[14] = 0xc;   // dec        ; 0x1 0x1 0x2 0x9
	vm.RAM[15] = 0x4;   // dup        ; 0x1 0x1 0x2 0x9 0x9
	vm.RAM[16] = 0x19;  // dnip 0x9
	vm.RAM[17] = 0x9;
	vm.RAM[18] = 0x3;   // pop        ; [result]
	vm.RAM[19] = 0x2;   // push 0xc;
	vm.RAM[20] = 0xc;
	vm.RAM[21] = 0x5;   // swap       ; [result-1] 0xc [result_last]
	vm.RAM[22] = 0x1b;  // writew     ; [result-1] 0xc
	vm.RAM[23] = 0x2;   // push 0x20  ; [result-1] 0xc <SPACE>
	vm.RAM[24] = 0x20;
	vm.RAM[25] = 0x1d;  // writea     ; [result-1] 0xc
	vm.RAM[26] = 0xc;   // dec        ; [result-1] 0xb
	vm.RAM[27] = 0x4;   // dup        ; [result-1] 0xb 0xb
	vm.RAM[28] = 0x19;  // dnip 0x8
	vm.RAM[29] = 0x8;
	*/
	
	if (argc != 2) {
		std::cout << "Usage: kkvm <program>\n";
		return 0;
	}
	
	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		std::cerr << "Reading error\n";
		return 1;
	}
	fread(vm.RAM, sizeof(Word), RAMSIZE, fp);
	
	vm.run();
	if (vm.state == Fail) {
		vm.dumpStack();
		vm.dumpRAM();
		vm.dumpRegisters();
	}
	std::cout << std::endl;
	
	fclose(fp);
	
	return 0;
}
