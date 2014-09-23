/*
    Copyright (C) 2014  Samuel Cowen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SQ_ARD_IO_INCLUDED
#define SQ_ARD_IO_INCLUDED

#include <squirrel.h>
#include "../vm_utils.h"

void io_init(HSQUIRRELVM v);
SQInteger io_pinmode(HSQUIRRELVM v);
SQInteger io_digitalwrite(HSQUIRRELVM v);
SQInteger io_digitalread(HSQUIRRELVM v);
SQInteger io_analogwrite(HSQUIRRELVM v);
SQInteger io_analogread(HSQUIRRELVM v);

#endif

