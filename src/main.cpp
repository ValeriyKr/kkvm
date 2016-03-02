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

#include "main.h"

int main(int argc, char *argv[]) {
	std::ios_base::sync_with_stdio(0);

	RAMSIZE = RAMSIZE_DEFAULT;
	STACKSIZE = STACKSIZE_DEFAULT;
	if (int help = parse_args(argc, argv)) {
		if (help < 3) {
			print_usage(help == 2);
		}
		return 0;
	}

	kkvm vm(RAMSIZE, STACKSIZE);

	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		std::cerr << "Reading error\n";
		return 1;
	}
	fread(vm.RAM, sizeof(Word), vm.RAMSIZE, fp);

	vm.run();
	if (vm.state == Fail) {
		vm.dumpStack();
		vm.dumpRAM();
		vm.dumpRegisters();
	} else if (vm.state == NotProgram) {
		std::cerr << argv[0] << ": " << argv[1] << ": is not a program";
	}
	std::cout << std::endl;

	fclose(fp);

	return 0;
}


int parse_args(int argc, char *argv[]) {
	if (argc < 2) {
		return 1;
	}
	if (!strcmp(argv[1], "--help")) {
		return 2;
	}
	if (!strcmp(argv[1], "--version")) {
		print_version();
		return 3;
	}

	for (int i = 2; i < argc; ++i) {
		if (!strcmp(argv[i], "--help")) {
			return 2;
		} else if (!strcmp(argv[i], "--version")) {
			print_version();
			return 3;
		} else if (!strcmp(argv[i], "--stack-size")) {
			if (i++ == argc) {
				return 1;
			}
			char *end_ptr = NULL;
			STACKSIZE = strtoull(argv[i], &end_ptr, 0);
			if (argv[i] == end_ptr) {
				return 1;
			}
		} else if (!strcmp(argv[i], "--ram-size")) {
			if (i++ == argc) {
				return 1;
			}
			char *end_ptr = NULL;
			RAMSIZE = strtoull(argv[i], &end_ptr, 0);
			if (argv[i] == end_ptr) {
				return 1;
			}
		} else {
			return 1;
		}
	}

	return 0;
}


void print_usage(bool help) {
	std::cout << "Usage: kkvm <program> [OPTIONS]" << std::endl;

	if (help) {
		std::cout << "       kkvm --help" << std::endl;
		std::cout << "       kkvm --version" << std::endl;
		std::cout << std::endl;
		std::cout << "Options:" << std::endl;
		std::cout << "  --help                 Output this help and exit" << std::endl;
		std::cout << "  --stack-size <size>    Set size of Stack if Words" << std::endl;
		std::cout << "  --ram-size <size>      Set size of RAM in Words" << std::endl;
		std::cout << "  --version              Osutput version information and exit" << std::endl;
		std::cout << std::endl;
		std::cout << "More information at <https://github.com/ValeriyKr/kkvm>" << std::endl;
	} else {
		std::cout << "Try 'kkvm --help' for more information" << std::endl;
	}
}


void print_version() {
	std::cout << "kkvm 1.0" << std::endl;
	std::cout << "Copyright (C) 2016 Valeriy Kireev <valeriykireev@gmail.com>" << std::endl;
	std::cout << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << std::endl;
	std::cout << "This is free software: you are free to change and redistribute it." << std::endl;
	std::cout << "There is NO WARRANTY, to the extent permitted by law." << std::endl;
	std::cout << std::endl;
	std::cout << "Written by Valeriy Kireev." << std::endl;

}