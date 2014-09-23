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

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <squirrel.h>
#include "../vm_utils.h"

void time_init(HSQUIRRELVM v);
SQInteger time_millis(HSQUIRRELVM v);
SQInteger time_micros(HSQUIRRELVM v);
SQInteger time_delay(HSQUIRRELVM v);
SQInteger time_delayMicroseconds(HSQUIRRELVM v);

#endif

