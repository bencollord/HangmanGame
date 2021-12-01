#include <windows.h>
#include "Utilities.h"

namespace Utilities
{
	void Console::clear()
	{
		Console::clear(0);
	}

	void Console::clear(unsigned int line)
	{
		char fill = ' ';
		COORD position = {0, line};
		CONSOLE_SCREEN_BUFFER_INFO buffer;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleScreenBufferInfo(console, &buffer);

		DWORD written;
		DWORD cells = buffer.dwSize.X * buffer.dwSize.Y;

		FillConsoleOutputCharacter(console, fill, cells, position, &written);
		FillConsoleOutputAttribute(console, buffer.wAttributes, cells, position, &written);
		SetConsoleCursorPosition(console, position);
	}
}