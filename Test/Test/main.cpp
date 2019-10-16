#include "siganture.h"
int main(int argc, char *argv[])
{
	int size_block;
	if (argc == 4)//Размер блока в байтах
		size_block = atoi(argv[3]);
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