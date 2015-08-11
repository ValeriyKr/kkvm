#ifndef KKVM_H
#define KKVM_H

#include <iostream>
#include <cstdio>
#include <inttypes.h>

#include "globals.h"

enum State {Halt, Run, Fail};

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

#endif // KKVM_H
