#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <filesystem>

#include "../headers/GetPicture.h"

using std::string;

// Retrieves image from given url and saves it in ./pictures/$filename
int GetPicture(string url, string destination)
{
	// std::cout << "\nLOG: GetPicture run\n";
	
	// If image is downloaded successfully,
	if (S_OK == URLDownloadToFile(NULL, url.c_str(), destination.c_str(), 0, NULL))
	{
		return 0;
	}
	// otherwise,
	else
	{
		std::cerr << "Image could not be downloaded: " << destination << "\n";
		return -1;
	}
}