/*
	Copyright 2015-2016 Valeriy Kireev
	
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

#include "kkvm.h"

kkvm::kkvm() {
	for (size_t i = 0; i < RAMSIZE; RAM[i++] = 0);
	for (size_t i = 0; i < STACKSIZE; Stack[i++] = 0);
	sp = ip = 0xffffffff;
}

void kkvm::run() {
	if (RAM[0] != 0x6D766B6B) {
		state = NotProgram;
		return;
	}
	
	state = Run;
	offset = RAM[1];
	ip = offset;
	while (state == Run) {
		/*dumpStack();
		dumpRAM();
		dumpRegisters();
		getchar();*/
		if (ip < offset ||
			ip >= RAMSIZE ||
			RAM[ip] >= INSTRUCTIONSCOUNT
			) {
			state = Fail;
		} else {
			instrSet[RAM[ip]](this);
			ip++;
		}
	}
}

void kkvm::dumpStack() {
	std::cout << "\nDUMP Stack:\n";
	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex | std::ios::uppercase);
	std::cout.fill('0');
	for (size_t i = 0; i < STACKSIZE; i++) {
		std::cout.width(8);
		std::cout << i << "\t" << Stack[i] << (sp == i ? "    <-" : "") << std::endl;
	}
	std::cout.unsetf(std::ios::hex | std::ios::uppercase);
	std::cout.fill(' ');
	std::cout << "DUMP END\n";
}

void kkvm::dumpRAM() {
	std::cout << "\nDUMP RAM:\n";
	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex | std::ios::uppercase);
	std::cout.fill('0');
	for (size_t i = 0; i < RAMSIZE; i++) {
		std::cout.width(8);
		std::cout << i << "\t" << RAM[i] << (ip == i ? "    <-" : "")<< std::endl;
	}
	std::cout.unsetf(std::ios::hex | std::ios::uppercase);
	std::cout.fill(' ');
	std::cout << "DUMP END\n";
}

void kkvm::dumpRegisters() {
	std::cout << "\nStack Ptr: " << sp << "\nInstruction Ptr: " << ip << "\nOffset: " << offset << "\nState: " << state << std::endl;
}
