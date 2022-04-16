#include <Windows.h>

class Input
{
public:
	static bool isPressed(char key)
	{
		return (GetKeyState(key) & 0x8000);
	}
};