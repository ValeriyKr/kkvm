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

using namespace std;

kkvm::kkvm(size_t ms, size_t ss) {
	RAMSIZE = ms;
	STACKSIZE = ss;
	RAM = new Word[RAMSIZE];
	Stack = new Word[STACKSIZE];
	for (size_t i = 0; i < RAMSIZE; RAM[i++] = 0);
	for (size_t i = 0; i < STACKSIZE; Stack[i++] = 0);
	sp = ip = 0xffffffffffffffff;
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
	cout << "\nDUMP Stack:\n";
	cout.unsetf(ios::dec);
	cout.setf(ios::hex | ios::uppercase);
	cout.fill('0');
	for (size_t i = 0; i < STACKSIZE; i++) {
		cout.width(8);
		cout << i << "\t" << Stack[i] << (sp == i ? "    <-" : "") << endl;
	}
	cout.unsetf(ios::hex | ios::uppercase);
	cout.fill(' ');
	cout << "DUMP END\n";
}

void kkvm::dumpRAM() {
	cout << "\nDUMP RAM:\n";
	cout.unsetf(ios::dec);
	cout.setf(ios::hex | ios::uppercase);
	cout.fill('0');
	for (size_t i = 0; i < RAMSIZE; i++) {
		cout.width(8);
		cout << i << "\t" << RAM[i] << (ip == i ? "    <-" : "")<< endl;
	}
	cout.unsetf(ios::hex | ios::uppercase);
	cout.fill(' ');
	cout << "DUMP END\n";
}

void kkvm::dumpRegisters() {
	cout << "\nStack Ptr: " << sp << "\nInstruction Ptr: " << ip
         << "\nOffset: " << offset << "\nState: " << state << endl;
}

kkvm::~kkvm() {
	delete [] RAM;
	delete [] Stack;
}
