/*
The use() function loads and executes a bytecode file.

use() makes everything in the file available, similar to #include in C/C++
A better comparison might be pythons import keyword. 

In this case, the print file contains the function 'helloworld'. 

*/

use("print"); 

while(true)
{
	helloworld();
	delay(1000);
}

