#include "siganture.h"
int main(int argc, char *argv[])
{
	long int size_block;
	if (argc == 4)//size block in mb
		size_block = atoi(argv[3])* 1048576;
	else
		size_block = 1048576;
	try {
		Siganture sign(argv[1], argv[2],size_block);
		sign.startProc();
	}
	catch(Siganture::ErrorOpen err)
	{
		return 0;
	}
	return 0;
}