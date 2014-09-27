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

#include <SdFat.h>
#include "vm_utils.h"

extern "C" {
    int _getpid() {
        return 1;
    }

    int _kill(int pid, int sig) {
        return(-1);
    }
}


SQInteger register_global_func(HSQUIRRELVM v,SQFUNCTION f,const char *fname)
{
    sq_pushroottable(v);
    sq_pushstring(v,fname,-1);
    sq_newclosure(v,f,0); //create a new function
    sq_newslot(v,-3,SQFalse); 
    sq_pop(v,1); //pops the root table    
}

SQInteger file_read(SQUserPointer file,SQUserPointer buf,SQInteger size)
{
    ifstream* pfile = (ifstream*)file;
    SQInteger ret;
    ret = pfile->read(buf, size);
    if(ret != 0)
        return ret;
    return -1;
}

void util_init(HSQUIRRELVM v)
{
	register_global_func(v, util_use, "use");
}

SQInteger util_use(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v); //number of arguments
	if(nargs >= 2)
	{
		if(sq_gettype(v, 2) != OT_STRING)
		{
			sq_throwerror(v, "bad parameter");
			return 0;
		}

		const SQChar* libname;
		sq_getstring(v, 2, &libname);
		
		ifstream file(libname);
		if (!file.is_open())
		{
			sq_throwerror(v, "couldn't open file");
			return 0;
		}

		if(!SQ_SUCCEEDED(sq_readclosure(v,file_read,&file)))
		{
			sq_throwerror(v, "error using file");
		}

		sq_pushroottable(v); //push the root table(were the globals of the script will be stored)
        sq_call(v,1,SQTrue,SQTrue);
		file.close();
	}
	return 0;
}


