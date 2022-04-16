#pragma once
#include <stdio.h>
#include <string>
#include <iostream>

class File
{
private:
	FILE* io[2];
	char* name;
public:
	File() {}
	File(char* fname)
	{
		name = fname;
		io[0] = fopen(fname, "r");
		io[1] = fopen(fname, "w");
	}
	~File()
	{
		fclose(io[0]), fclose(io[1]);
	}
	void write(char* buf)
	{
		fprintf(io[1], "%s", buf);
	}
	void write(std::string buf)
	{
		fprintf(io[1], "%s", buf.c_str());
	}
	void read(char* buf, size_t siz)
	{
		if (!buf) return;
		fread(buf, 1, siz, io[0]);
	}
	int get()
	{
		if (io[0] == NULL) return -1;
		return fgetc(io[0]);
	}
	void creat(char* x)
	{
		name = x;
		io[0] = fopen(x, "x");
		io[1] = io[0];
	}
};