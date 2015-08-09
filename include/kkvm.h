#ifndef KKVM_H
#define KKVM_H

#include <iostream>
#include <climits>

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

#endif // KKVM_H
