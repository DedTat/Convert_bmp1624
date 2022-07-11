#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void main()
{

	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	HANDLE hInputFile, hOutputFile;
	DWORD RW;
	WORD *inBuf;
	RGBTRIPLE *outBuf;
	int Width, Height;

	hInputFile = CreateFile("16.bmp", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hInputFile == INVALID_HANDLE_VALUE)
		return;

	hOutputFile = CreateFile("244.bmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hOutputFile == INVALID_HANDLE_VALUE)
		return;

	ReadFile(hInputFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW, NULL);
	ReadFile(hInputFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW, NULL);
	
	DWORD RW1;
	
	Width = bmpInfoHeader.biWidth;
	Height = bmpInfoHeader.biHeight;

	bmpInfoHeader.biBitCount = 24;
	
	WriteFile(hOutputFile, &bmpFileHeader, sizeof(bmpFileHeader), &RW1, NULL);
	WriteFile(hOutputFile, &bmpInfoHeader, sizeof(bmpInfoHeader), &RW1, NULL);

	inBuf = new WORD[Width];
	outBuf = new RGBTRIPLE[Width];

	int i, j;

	for (i = 0; i < Height; i++) {

		ReadFile(hInputFile, inBuf, sizeof(WORD) * Width, &RW, NULL);

		for (j = 0; j < Width; j++) {

			outBuf[j].rgbtRed = (inBuf[j] >> 10) << 3;
			outBuf[j].rgbtGreen = ((inBuf[j] << 6) >> 11) << 3;
			outBuf[j].rgbtBlue = (inBuf[j] << 12) >> 9;

		}

		WriteFile(hOutputFile, outBuf, sizeof(RGBTRIPLE) * Width, &RW1, NULL);
	}

	CloseHandle(hOutputFile);
	CloseHandle(hInputFile);

	delete[] inBuf;
	delete[] outBuf;

	cout << "Updating has come to the end successfully!" << "\n";
	system("pause");
}

