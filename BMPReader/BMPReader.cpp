#include "BMPReader.h"

bool BMPReader::openBMP(const std::string& fileName)
{
	bmpFile.open(fileName, std::ios::binary);

	if (!bmpFile)
	{
		std::cout << "Ошибка открытия файла: " << fileName << std::endl;
		return false;
	}

	// Чтение заголовков BMP
	bmpFile.read(reinterpret_cast<char*>(&fileHeader), sizeof(BITMAPFILEHEADER));
	bmpFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(BITMAPINFOHEADER));

	// Проверка формата (24 или 32 бита)
	if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32)
	{
		std::cout << "Неподдерживаемый формат BMP. Поддерживаются только 24 и 32 битные изображения." << std::endl;
		closeBMP();
		return false;
	}

	// Выделение памяти для пиксельных данных
	int dataSize = infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8);
	pixelData = new unsigned char[dataSize];

	// Переход к пиксельным данным
	bmpFile.seekg(fileHeader.bfOffBits, std::ios::beg);
	bmpFile.read(reinterpret_cast<char*>(pixelData), dataSize);

	return true;
}


void BMPReader::displayBMP()
{
	int bytesPerPixel = infoHeader.biBitCount / 8;  // Количество байт на пиксель (3 для 24-битного BMP)
	int width = infoHeader.biWidth;
	int height = infoHeader.biHeight;

	// Вычисляем padding: строки в BMP выравниваются по границе в 4 байта
	int padding = (4 - (width * bytesPerPixel) % 4) % 4;

	// Чтение строк изображения снизу вверх
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			// Индекс пикселя с учётом padding
			int index = y * (width * bytesPerPixel + padding) + (x * bytesPerPixel);

			// Чтение компонентов цвета (синий, зеленый, красный)
			unsigned char blue = pixelData[index];
			unsigned char green = pixelData[index + 1];
			unsigned char red = pixelData[index + 2];

			// Отображаем пиксель на основе цвета
			if (red == 0 && green == 0 && blue == 0)
			{
				std::cout << "  ";  // Черный цвет
			}
			else if (red == 255 && green == 255 && blue == 255)
			{
				std::cout << "оо";  // Белый цвет
			}
			else
			{
				std::cout << "++";  // Цветной пиксель
			}
		}

		std::cout << std::endl;  // Переход на следующую строку
	}
}


void BMPReader::displayBMPInfo()
{
	if (!pixelData)
	{
		std::cout << "Данные изображения не загружены." << std::endl;
		return;
	}

	std::cout << "Информация о BMP файле:" << std::endl;

	// BITMAPFILEHEADER
	std::cout << "  BITMAPFILEHEADER:" << std::endl;
	std::cout << "    bfType: " << fileHeader.bfType << std::endl;
	std::cout << "    bfSize: " << fileHeader.bfSize << std::endl;
	std::cout << "    bfReserved1: " << fileHeader.bfReserved1 << std::endl;
	std::cout << "    bfReserved2: " << fileHeader.bfReserved2 << std::endl;
	std::cout << "    bfOffBits: " << fileHeader.bfOffBits << std::endl;

	// BITMAPINFOHEADER
	std::cout << "  BITMAPINFOHEADER:" << std::endl;
	std::cout << "    biSize: " << infoHeader.biSize << std::endl;
	std::cout << "    biWidth: " << infoHeader.biWidth << std::endl;
	std::cout << "    biHeight: " << infoHeader.biHeight << std::endl;
	std::cout << "    biPlanes: " << infoHeader.biPlanes << std::endl;
	std::cout << "    biBitCount: " << infoHeader.biBitCount << std::endl;
	std::cout << "    biCompression: " << infoHeader.biCompression << std::endl;
	std::cout << "    biSizeImage: " << infoHeader.biSizeImage << std::endl;
	std::cout << "    biXPelsPerMeter: " << infoHeader.biXPelsPerMeter << std::endl;
	std::cout << "    biYPelsPerMeter: " << infoHeader.biYPelsPerMeter << std::endl;
	std::cout << "    biClrUsed: " << infoHeader.biClrUsed << std::endl;
	std::cout << "    biClrImportant: " << infoHeader.biClrImportant << std::endl;
}


void BMPReader::closeBMP()
{
	if (pixelData)
	{
		delete[] pixelData;
		pixelData = nullptr;
	}
	if (bmpFile.is_open())
	{
		bmpFile.close();
	}
}


BMPReader::~BMPReader()
{
	closeBMP();
}
