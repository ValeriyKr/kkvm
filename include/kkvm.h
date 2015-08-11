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
<<<<<<< HEAD
void mul(kkvm *);
void sub(kkvm *);
void div(kkvm *);
void inc(kkvm *);
void dec(kkvm *);
void shr(kkvm *);
void shl(kkvm *);
void ror(kkvm *);
void rol(kkvm *);
=======
>>>>>>> 9882ea05b3a3806b9a8282ae7a61dafe28eb6f62

#endif // KKVM_H
