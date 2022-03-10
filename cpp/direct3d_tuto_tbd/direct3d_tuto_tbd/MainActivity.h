#pragma once

#include <Windows.h>


class MainActivity
{
public:
	MainActivity(int width, int height);
	virtual ~MainActivity();

	HWND getTheHandle();

protected:
	HWND _handle;
};

