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

void (*instrSet[INSTRUCTIONSCOUNT])(kkvm *) = {
	fail,     // 0x0
	nop,
	push,
	pop,
	dup,      // 0x4
	swap,
	deep,
	add,
	mul,      // 0x8
	sub,
	div,
	inc,
	dec,      // 0xC
	shr,
	shl,
	ror,
	rol,      // 0x10
	bnot,
	band,
	bor,
	bxor,     // 0x14
	dip,
	iip,
	deip,
	ieip,     // 0x18
	dnip,
	inip,
	writew,
	readw,    // 0x1C
	writea,
	reada,
	deeps,
	halt,     // 0x20
	mpeek,
	mpush,
	mpop,
	minc,     // 0x24
	mdec
};

void fail(kkvm *vm) {
	vm->state = Fail;
}

void nop(kkvm *vm) {}

void push(kkvm *vm) {
	vm->ip++;
	vm->sp++;
	if (vm->sp >= vm->STACKSIZE || vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = vm->RAM[vm->ip];
}

void pop(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->sp--;
}

void dup(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE || vm->sp+1 >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->sp++;
	vm->Stack[vm->sp] = vm->Stack[vm->sp - 1];
}

void swap(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	std::swap(vm->Stack[vm->sp], vm->Stack[vm->sp-1]);
}

void deep(kkvm *vm) {
	vm->ip++;
	if (vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->RAM[vm->ip] > vm->sp) {
		vm->state = Fail;
		return;
	}
	vm->sp++;
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = vm->Stack[vm->sp - vm->RAM[vm->ip] - 1];
}

void add(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] + vm->Stack[vm->sp-1];
	vm->sp--;
}

void mul(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] * vm->Stack[vm->sp-1];
	vm->sp--;
}

void sub(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] - vm->Stack[vm->sp-1];
	vm->sp--;
}

void div(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	Word divisor = vm->Stack[vm->sp];
	vm->Stack[vm->sp] = divisor % vm->Stack[vm->sp-1];
	vm->Stack[vm->sp-1] = divisor / vm->Stack[vm->sp-1];
}

void inc(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp]++;
}

void dec(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp]--;
}

void shr(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= vm->STACKSIZE || vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] >>= vm->RAM[vm->ip];
}

void shl(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= vm->STACKSIZE || vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] <<= vm->RAM[vm->ip];
}

void ror(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= vm->STACKSIZE || vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = (vm->Stack[vm->sp] >> vm->RAM[vm->ip]) | (vm->Stack[vm->sp] << (8*sizeof(Word)-vm->RAM[vm->ip]));
}

void rol(kkvm *vm) {
	vm->ip++;
	if (vm->sp >= vm->STACKSIZE || vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = (vm->Stack[vm->sp] << vm->RAM[vm->ip]) | (vm->Stack[vm->sp] >> (8*sizeof(Word)-vm->RAM[vm->ip]));
}

void bnot(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = ~vm->Stack[vm->sp];
}

void band(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] & vm->Stack[vm->sp-1];
	vm->sp--;
}

void bor(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] | vm->Stack[vm->sp-1];
	vm->sp--;
}

void bxor(kkvm *vm) {
	if (vm->sp == 0 || vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp-1] = vm->Stack[vm->sp] ^ vm->Stack[vm->sp-1];
	vm->sp--;
}

void dip(kkvm *vm) {
	vm->ip -= vm->RAM[vm->ip+1];
	if ((vm->ip - vm->offset) >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
}

void iip(kkvm *vm) {
	vm->ip += vm->RAM[vm->ip+1];
	if (vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
}

void deip(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] == 0) {
		vm->ip -= vm->RAM[vm->ip+1];
		if ((vm->ip - vm->offset)  >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void ieip(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] == 0) {
		vm->ip += vm->RAM[vm->ip+1];
		if (vm->ip >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void dnip(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] != 0) {
		vm->ip -= vm->RAM[vm->ip+1];
		if ((vm->ip - vm->offset)  >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void inip(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->Stack[vm->sp] != 0) {
		vm->ip += vm->RAM[vm->ip+1];
		if (vm->ip >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	} else {
		vm->ip++;
		if (vm->ip >= vm->RAMSIZE) {
			vm->state = Fail;
			return;
		}
	}
	vm->sp--;
	return;
}

void writew(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	printf("%u", vm->Stack[vm->sp]);
	fflush(stdout);
	vm->sp--;
}

void readw(kkvm *vm) {
	vm->sp++;
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	scanf("%u", &(vm->Stack[vm->sp]));
}

void writea(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	putchar((char) (vm->Stack[vm->sp] % 256));
	fflush(stdout);
	vm->sp--;
}

void reada(kkvm *vm) {
	vm->sp++;
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = getchar();
}

void deeps(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->sp - vm->Stack[vm->sp] >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = vm->Stack[vm->sp - vm->Stack[vm->sp]];
}

void halt(kkvm *vm) {
	vm->state = Halt;
}

void mpeek(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->ip++;
	if (vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->RAM[vm->ip] < 2 || vm->RAM[vm->ip] >= vm->offset) {
		vm->state = Fail;
		return;
	}
	vm->RAM[vm->RAM[vm->ip]] = vm->Stack[vm->sp];
}

void mpush(kkvm *vm) {
	vm->sp++;
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->ip++;
	if (vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	vm->Stack[vm->sp] = vm->RAM[vm->RAM[vm->ip]];
}

void mpop(kkvm *vm) {
	if (vm->sp >= vm->STACKSIZE) {
		vm->state = Fail;
		return;
	}
	vm->ip++;
	if (vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->RAM[vm->ip] < 2 || vm->RAM[vm->ip] >= vm->offset) {
		vm->state = Fail;
		return;
	}
	vm->RAM[vm->RAM[vm->ip]] = vm->Stack[vm->sp];
	vm->sp--;
}

void minc(kkvm *vm) {
	vm->ip++;
	if (vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->RAM[vm->ip] < 2 || vm->RAM[vm->ip] >= vm->offset) {
		vm->state = Fail;
		return;
	}
	vm->RAM[vm->RAM[vm->ip]]++;
}

void mdec(kkvm *vm) {
	vm->ip++;
	if (vm->ip >= vm->RAMSIZE) {
		vm->state = Fail;
		return;
	}
	if (vm->RAM[vm->ip] < 2 || vm->RAM[vm->ip] >= vm->offset) {
		vm->state = Fail;
		return;
	}
	vm->RAM[vm->RAM[vm->ip]]--;
}
