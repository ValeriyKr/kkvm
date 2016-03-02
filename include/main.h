/*
	Copyright 2015-2016 Valeriy Kireev
	
	This file is part of kkvm.
	
	kkvm is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Foobar is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with kkvm. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdio>
#include <inttypes.h>
#include <cstring>

#include "kkvm.h"
#include "globals.h"

int parse_args(int, char**);
void print_usage(bool);
void print_version();

size_t STACKSIZE = 0;
size_t RAMSIZE = 0;

#endif // MAIN_H
