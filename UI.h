#pragma once
#include <Windows.h>
#include <vector>
#define NULLSTR (char*)0
#define WHITE RGB(255,255,255)
#define BLACK RGB(0,0,0)
#define RED RGB(255,0,0)
#define CYAN RGB(0, 255, 255)
#define FONT_SIZE 15
#define MAX_LOADSTRING 100
#define BRUSH(x) CreateSolidBrush((COLORREF)x)
#define MsgBox(x, y) MessageBoxA(NULL, (LPCSTR)x, (LPCSTR)y, MB_OK);
typedef char* str;
typedef wchar_t* wstr;
typedef void* buffer;
int _lastID = 1000;

enum
{
	MOUSE_CLICK = WM_MBUTTONDOWN,
	WIN_CLOSE = WM_CLOSE
};

void clearBuffer(buffer _buf, int size)
{
	memset(_buf, 0, size);
}

void writeBuffer(buffer _buf, HDC dc)
{
	int x = 0, y = 0, c = 0;
	int* k = (int*)_buf;
	while (k[c++])
	{
		if (k[c - 1] == -1)
			y++, x = 0;
	}

}

size_t getTextSize(char* x) 
{
	if (!x) return 0;
	return strlen(x) * FONT_SIZE;
}

char* toUTF8(wstr _w)
{
	for (int a = 0; _w[a]; a++)
		_w[a] = _w[a] % 255;
	return (char*)_w;
}

void setFontSize(size_t x)
{
#undef FONT_SIZE
#define FONT_SIZE x
}

struct Event 
{
	int type;
	HWND handle = NULL;
	Event(int x) : type(x) , handle(GetForegroundWindow()) {}
	~Event()
	{
		type = 0;
	}
};

void initClass(WNDCLASSEXA* clsptr)
{
	clsptr->cbSize = sizeof(WNDCLASSEXA);
	clsptr->hInstance = NULL;
	clsptr->cbClsExtra = 0;
	clsptr->cbWndExtra = 0;
}

class Component
{
private:
	HWND handle;
	RECT pos = {0};
	WNDCLASSEXA cls;
	int id;
public:
	Component() { 
		handle = GetForegroundWindow();  
		GetWindowRect(handle, &pos);
		id = ++_lastID;
	}
	Component(HWND x) : handle(x) {
		GetWindowRect(handle, &pos);
		id = ++_lastID;
	}
	Component(int x) : id(x) {}
	HWND getHandle()
	{
		return handle ? handle : HWND_DESKTOP;
	}

	HDC getCanvas()
	{
		return GetDC(handle);
	}

	void setHandle(HWND x)
	{
		handle = x;
	}

	void drawPixel(int x, int y, int color)
	{
		SetPixel(GetWindowDC(handle), x, y, (COLORREF)color);
	}

	void setSize(int width, int height)
	{
		MoveWindow(handle, pos.left, pos.top, width, height, TRUE);
	}

	void regClass()
	{
		RegisterClassExA((const WNDCLASSEXA*) & cls);
	}

	int getID()
	{
		return this->id;
	}
};

void defClick(Event* x)
{
	if (!x) return;
	MessageBoxA(x->handle, "Clicked!", "", MB_OK);
	delete x;
}

class Button : public Component
{
private:
	HWND parent = HWND_DESKTOP;
	HWND handle = NULL;
	RECT pos;
public:
	Button() { pos.left = CW_USEDEFAULT;  }
	Button(int x1, int y1) 
	{
		pos.top = y1;
		pos.left = x1;
	}
	~Button(){
		if (handle)
			DestroyWindow(handle);
	}
	void create(char* title)
	{
		handle = CreateWindowA("BUTTON", title, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 10, 100, 50, parent, nullptr, nullptr, nullptr);
	}
	void create(const char* title)
	{
		create((char*)title);
	}
	void setText(char* title)
	{
		SendMessageA(handle, WM_SETTEXT, (WPARAM)0, (LPARAM)title);
	}
	void setText(const char* title)
	{
		setText((char*)title);
	}
	void setParent(Component x)
	{
		this->parent = x.getHandle();
	}
	void(*onClick)(Event*) = defClick;
};

class Label : public Component
{
private:
	HWND parent = HWND_DESKTOP;
	HWND handle = NULL;
	RECT pos;
public:
	Label() {}
	Label(char* text) {}
	~Label () {
		if (handle)
			DestroyWindow(handle);
	}
	void create(char* title)
	{
		handle = CreateWindowA("STATIC", title, WS_VISIBLE | WS_CHILD | SS_CENTER,
			10, 10, getTextSize(title), 50, parent, nullptr, nullptr, nullptr);
	}
	void setParent(Component x)
	{
		this->parent = x.getHandle();
	}
	void(*onClick)(Event*) = defClick;

};

class TextBox : public Component
{
private:
	HWND parent = HWND_DESKTOP;
	HWND handle = NULL;
	RECT pos;
public:
	TextBox() {}
	TextBox(char* text) {}
	~TextBox() {
		if (handle)
			DestroyWindow(handle);
	}
	void create(char* title)
	{
		handle = CreateWindowA("EDIT", title, WS_VISIBLE | WS_CHILD | BS_FLAT,
			10, 10, getTextSize(title), 50, parent, nullptr, nullptr, nullptr);
	}
	void setParent(Component x)
	{
		this->parent = x.getHandle();
	}
	void(*onClick)(Event*) = defClick;

};

class App
{
private:
	std::vector<Component> comp;
};