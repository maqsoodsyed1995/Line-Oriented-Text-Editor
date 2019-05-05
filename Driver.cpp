#include<iostream>
#include "Command.h"
#include "Led.h"
/*
* The main function if given takes the filename from the user(Command Line)
* and calls the run method of the Led class which inturn initializes the buffer with the contents of the file.
* If the filename is not given in the command line then the run method will create an empty buffer.
*/
int main(int argc, char* argv[])
{
	string flname;
	switch (argc)
	{
	case 1:
		break;
	case 2:
	{
		flname = argv[1];
		break;
	}
	default:
	{
		cout << "(Too many arguments-all discarded)" << endl;
		break;
	}
	}
	led editor(flname);
	editor.run();
	system("pause");
}
