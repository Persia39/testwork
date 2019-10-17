#include "Siganture.h"


Siganture::Siganture(string f1,string f2,int k)
{
	size_block = k;
	outfile.open(f2, ios::binary);
	if (!outfile)
		throw ErrorOpen("Не удалось открыть файл для записи хэша.");
	infile.open(f1, ios::binary);
	if (!infile)
		throw ErrorOpen("Не удалось открыть файл для считывания данных.");

}



Siganture::~Siganture()
{
}

void Siganture::readText()// read date from file
{
	char* block=new char[size_block];
	while (infile.read(block,size_block))
	{
		if (infile.gcount() == size_block)
		{
			cntBlock++;
			m1.lock();
			blockList.push_back(block);
			m1.unlock();
			Sleep(4);
		}
	}
	if(infile.gcount()<size_block && infile.gcount()>0)//date < block
	{
		cntBlock++;
		int i = infile.gcount();
		while (i < size_block)
		{
			block[i] = '0';
			i++;
		}
		m1.lock();
		blockList.push_back(block);
		m1.unlock();
		Sleep(4);
	}
	EndBlock = true;
	infile.close();
	delete[] block;
}

void Siganture::writeHash()// hash and write to file
{
	while (!blockList.empty())
	{
		toHash = string(blockList.front(), size_block);
		blockList.front() = nullptr;
		outfile << sha512(toHash);//hash alg sha512
		toHash = "";
		m1.lock();
		blockList.pop_front();
		m1.unlock();
		cntOutBlock++;
	}
}

void Siganture::startProc() //thread
{
	thread t3(&Siganture::manager, this);
	thread t1(&Siganture::readText, this);
	t1.join();
	t3.join();
}

void Siganture::manager()// monitors the completion of the list
{
	while (1)
	{
		if (EndBlock && cntBlock == cntOutBlock)
			break;
		if (!blockList.empty())
		{
			thread t2(&Siganture::writeHash, this);
			t2.join();
		}

	}
	outfile.close();
}

