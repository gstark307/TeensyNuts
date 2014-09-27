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


#include <Arduino.h>
#include "serial.h"

void serial_init(HSQUIRRELVM v)
{
	sq_pushroottable(v);
    sq_pushstring(v,"Serial",-1);
    sq_newclass(v, SQFalse);

	sq_pushstring(v, "begin", -1);
	sq_newclosure(v, serial_begin, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "read", -1);
	sq_newclosure(v, serial_getchar, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "readBytesUntil", -1);
	sq_newclosure(v, serial_readbytesuntil, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "peekchar", -1);
	sq_newclosure(v, serial_peekchar, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "available", -1);
	sq_newclosure(v, serial_available, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "readBytes", -1);
	sq_newclosure(v, serial_readbytes, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "flush", -1);
	sq_newclosure(v, serial_flush, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "write", -1);
	sq_newclosure(v, serial_write, 0);
	sq_newslot(v, -3, SQFalse);

	sq_pushstring(v, "print", -1);
	sq_newclosure(v, serial_print, 0);
	sq_newslot(v, -3, SQFalse);

	sq_newslot(v, -3, SQFalse);

    sq_pop(v,1);
}

SQInteger serial_begin(HSQUIRRELVM v) { }

SQInteger serial_getchar(HSQUIRRELVM v)
{
	sq_pushinteger(v, Serial.read());
	return 1;
}

SQInteger serial_peekchar(HSQUIRRELVM v)
{
	sq_pushinteger(v, Serial.peek());
	return 1;
}

SQInteger serial_available(HSQUIRRELVM v)
{
	sq_pushinteger(v, Serial.available());
	return 1;
}

SQInteger serial_readbytes(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	if(nargs >= 2)
	{
		if(sq_gettype(v, 2) != OT_INTEGER)
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		int n;
		sq_getinteger(v, 2, &n);
		
		void* buffer = malloc(n);
		int len = Serial.readBytes((char*)buffer, n);
		sq_pushstring(v, (SQChar*)buffer, len);
		free(buffer);
		return 1;
	}
    return 0;
}

SQInteger serial_readbytesuntil(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	if(nargs >= 3)
	{
		if((sq_gettype(v, 2) != OT_INTEGER) || (sq_gettype(v, 3) != OT_INTEGER))
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		int character, n;
		sq_getinteger(v, 2, &character);
		sq_getinteger(v, 3, &n);
		
		void* buffer = malloc(n);
		int len = Serial.readBytesUntil(character, (char*)buffer, n);
		sq_pushstring(v, (SQChar*)buffer, len);
		free(buffer);
		return 1;
	}
    return 0;
}


SQInteger serial_flush(HSQUIRRELVM v)
{
	usb_serial_flush_output();
	return 0;
}


SQInteger serial_write(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);
	if(nargs == 2)
	{
		if(sq_gettype(v, 2) == OT_INTEGER)
		{
			int n;
			sq_getinteger(v, 2, &n);
			sq_pushinteger(v, Serial.write(n));
			return 1;
		}
		if(sq_gettype(v, 2) == OT_STRING)
		{
			const SQChar* st;
			sq_getstring(v, 2, &st);
			sq_pushinteger(v, Serial.write(st));
			return 1;
		}
	}
	return 0;
}




