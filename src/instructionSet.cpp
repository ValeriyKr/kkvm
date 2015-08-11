#include "kkvm.h"

void (*instrSet[INSTRUCTIONSCOUNT])(kkvm *) = {
	fail,
	nop,
	push,
	pop,
	dup,
	swap,
	deep,
	add,
	mul,
	sub,
	div,
	inc,
	dec,
	shr,
	shl,
	ror,
	rol,
	bnot,
	band,
	bor,
	bxor,
	dip,
	iip,
	deip,
	ieip,
	dnip,
	inip,
	writew,
	readw,
	writea,
	reada
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

void mul(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] * vm->Stack[vm->sp-1];
	vm->sp--;
}

void sub(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] - vm->Stack[vm->sp-1];
	vm->sp--;
}

void div(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	Word divisor = vm->Stack[vm->sp];
	vm->Stack[vm->sp] = divisor % vm->Stack[vm->sp-1];
	vm->Stack[vm->sp-1] = divisor / vm->Stack[vm->sp-1];
}

void inc(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp]++;
}

void dec(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp]--;
}

void shr(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= STACKSIZE || vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] >>= vm->RAM[vm->ip];
}

void shl(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= STACKSIZE || vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] <<= vm->RAM[vm->ip];
}

void ror(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= STACKSIZE || vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = (vm->Stack[vm->sp] >> vm->RAM[vm->ip]) | (vm->Stack[vm->sp] << (8*sizeof(Word)-vm->RAM[vm->ip]));
}

void rol(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= STACKSIZE || vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = (vm->Stack[vm->sp] << vm->RAM[vm->ip]) | (vm->Stack[vm->sp] >> (8*sizeof(Word)-vm->RAM[vm->ip]));
}

void bnot(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = ~vm->Stack[vm->sp];
}

void band(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] & vm->Stack[vm->sp-1];
	vm->sp--;
}

void bor(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] | vm->Stack[vm->sp-1];
	vm->sp--;
}

void bxor(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] ^ vm->Stack[vm->sp-1];
	vm->sp--;
}

void dip(kkvm *vm) {
	vm->ip -= vm->RAM[vm->ip+1];
	if (vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
}

void iip(kkvm *vm) {
	vm->ip += vm->RAM[vm->ip+1];
	if (vm->ip >= RAMSIZE) {
		vm->state = Fail;
		return;
	}
}

void deip(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] == 0) {
		vm->ip -= vm->RAM[vm->ip+1];
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void ieip(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] == 0) {
		vm->ip += vm->RAM[vm->ip+1];
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void dnip(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] != 0) {
		vm->ip -= vm->RAM[vm->ip+1];
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void inip(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] != 0) {
		vm->ip += vm->RAM[vm->ip+1];
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void writew(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	printf("%u", vm->Stack[vm->sp]);
	vm->sp--;
}

void readw(kkvm *vm) {
	vm->sp++;
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	scanf("%u", vm->Stack[vm->sp]);
}

void writea(kkvm *vm) {
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	putchar((char) (vm->Stack[vm->sp] % 256));
	vm->sp--;
}

void reada(kkvm *vm) {
	vm->sp++;
	if (vm->sp >= STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = getchar();
}
