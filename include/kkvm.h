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

#ifndef KKVM_H
#define KKVM_H

#include <iostream>
#include <cstdio>

#include <inttypes.h>

#include "globals.h"

enum State {Halt, Run, Fail, NotProgram};

class kkvm {
	public:
		kkvm();
		void run();
		void dumpStack();
		void dumpRAM();
		void dumpRegisters();

		Word RAM[RAMSIZE];
		Word Stack[STACKSIZE];
		Word sp, ip, offset, state;
};

extern void (*instrSet[INSTRUCTIONSCOUNT])(kkvm *);

void fail(kkvm *);
void nop(kkvm *);
void push(kkvm *);
void pop(kkvm *);
void dup(kkvm *);
void swap(kkvm *);
void deep(kkvm *);
void add(kkvm *);
void mul(kkvm *);
void sub(kkvm *);
void div(kkvm *);
void inc(kkvm *);
void dec(kkvm *);
void shr(kkvm *);
void shl(kkvm *);
void ror(kkvm *);
void rol(kkvm *);
void bnot(kkvm *);
void band(kkvm *);
void bor(kkvm *);
void bxor(kkvm *);
void dip(kkvm *);
void iip(kkvm *);
void deip(kkvm *);
void ieip(kkvm *);
void dnip(kkvm *);
void inip(kkvm *);
void writew(kkvm *);
void readw(kkvm *);
void writea(kkvm *);
void reada(kkvm *);
void deeps(kkvm *);
void halt(kkvm *);

#endif // KKVM_H
