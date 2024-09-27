#pragma once

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

class BMPReader
{

public:

	~BMPReader();

	bool openBMP(const std::string& fileName);

	void closeBMP();

	void displayBMP() const;

	void displayBMPInfo() const;

private:
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	unsigned char* pixelData = nullptr;
	std::ifstream bmpFile;
};