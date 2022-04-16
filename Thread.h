#pragma once
#include <windows.h>
#include <stdlib.h>
#define STACK_SIZE 64 * 1024

class Thread
{
private:
	HANDLE thread;
	void* memory;
	DWORD id;
public:
	void resume()
	{
		ResumeThread(thread);
	}
	Thread(LPTHREAD_START_ROUTINE routine)
	{
		memory = malloc(10);
		thread = CreateThread(NULL, STACK_SIZE, routine, memory, 0, &id);
	}

	~Thread()
	{
		free(memory);
		TerminateThread(thread, 0);
	}

	void close(DWORD c)
	{
		TerminateThread(thread, c);
	}

	void open()
	{
		
	}
};

