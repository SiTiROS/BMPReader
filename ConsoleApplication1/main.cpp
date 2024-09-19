#include <locale>
#include "BMPReader.h"

void setConsoleFont(const std::wstring& fontName, int fontSize)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };

	if (GetCurrentConsoleFontEx(hConsole, FALSE, &cfi))
	{
		wcscpy_s(cfi.FaceName, fontName.c_str());
		cfi.dwFontSize.Y = fontSize;  // Высота шрифта
		SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	}
}

void setConsoleSize(int width, int height)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Устанавливаем размер буфера экрана
	COORD newSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
	SetConsoleScreenBufferSize(hConsole, newSize);

	// Устанавливаем размер окна
	SMALL_RECT windowSize = { 500, 500, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	setConsoleFont(L"Consolas", 12);  // Устанавливаем шрифт Consolas размером 16
	setConsoleSize(1000, 1000);       // Устанавливаем размеры буфера экрана и окна консоли чтобы не уезжали большие картинки

	std::string filePath;
	if (argc == 2)
	{
		filePath = argv[1];
	}
	else
	{
		std::cout << "Введите путь к BMP файлу: ";
		std::getline(std::cin, filePath);
	}
	std::cout << "filePath:" << filePath << std::endl;


	BMPReader bmpReader;
	if (bmpReader.openBMP(filePath))
	{
		bmpReader.displayBMPInfo();
		bmpReader.displayBMP();
		bmpReader.closeBMP();
	}


	if (argc != 2)
	{
		std::cout << "Нажмите любую кнопку для выхода" << std::endl;
		std::cin.get();
	}

	return 0;
}