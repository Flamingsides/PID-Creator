#include <iostream>
#include <windows.h>
#include <commdlg.h>

 char* GetFile(const char* file_type)
{
	OPENFILENAMEA ofn;
	char filepath[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = file_type;
	ofn.lpstrFile = filepath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;


	if (GetOpenFileNameA(&ofn))
	{
		printf("Retrieved Data File: %s", filepath);
	}
	else
	{
		std::cout << "Couldn't Get Data File.\n";
	}

	return filepath;
}