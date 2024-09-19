#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

class BMPReader
{

public:

	bool openBMP(const std::string& fileName);

	void displayBMP();

	void displayBMPInfo();

	void closeBMP();

	~BMPReader();

private:
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	unsigned char* pixelData = nullptr;
	std::ifstream bmpFile;
};