#include "kkvm.h"

void (*instrSet[INSTRUCTIONSCOUNT])(kkvm *) = {
	fail,
	nop,
	push,
	pop,
	dup,
	swap,
	deep,
	add
};

void fail(kkvm *vm) {
	vm->state = Fail;
}

void nop(kkvm *vm) {}

void push(kkvm *vm) {
	vm->ip++;
	vm->sp++;
	if (vm->sp >= STACKSIZE || vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = vm->RAM[vm->ip];
}

void pop(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->sp--;
}

void dup(kkvm *vm) {
	if (vm->sp >= STACKSIZE || vm->sp+1 >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->sp++;
	vm->Stack[vm->sp] = vm->Stack[vm->sp - 1];
}

void swap(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	std::swap(vm->Stack[vm->sp], vm->Stack[vm->sp-1]);
}

void deep(kkvm *vm) {
	vm->ip++;
	if (vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->RAM[vm->ip] > vm->sp) {
		vm->state = Fail;
		return;
	}
	vm->sp++;
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = vm->Stack[vm->sp - vm->RAM[vm->ip] - 1];
}

void add(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] + vm->Stack[vm->sp-1];
	vm->sp--;
}
