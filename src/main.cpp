#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>

#include "headers/ReadTSV.h"
#include "headers/Student.h"
#include "headers/GetPicture.h"
#include "headers/PdfCreator.h"
#include "headers/GetFile.h"

int main(void)
{
	std::stringstream ss;
	ss << std::filesystem::current_path();
	std::string exe_path = ss.str().substr(1, ss.str().length() - 2);
	std::cout << exe_path << "\n";
	//// Get .tsv file name from user
	//std::string filename;
	//std::cout << "File Name: ";
	//std::getline(std::cin, filename);

	//// Add extension ".tsv" if not provided by user
	//if (!filename.ends_with(".tsv"))
	//{
	//	filename += ".tsv";
	//}
	//filename = "../" + filename;

	std::string tsvpath = GetFile(".tsv");
	std::cout << std::filesystem::current_path() << "\n";
	std::cout << "LOG: Data file found: " << tsvpath << "\n\n";

	// Reading from .tsv file as a 2-dimensional vector
	std::vector<std::vector<std::string>> data = GetData(tsvpath);

	// Vector of Student objects to be used later (see Students.cpp)
	std::vector<Student> students;

	// For every record in the 2D Vector
	for (int i = 1; i < data.size(); i++)
	{
		std::vector<std::string> r = data[i];

		// Create Student object from record i
		Student* s = new Student(r[0], r[1], r[2], r[3], r[4], r[5], r[6]);
		// Store in students vector
		students.push_back(*s);
		// Clean up
		delete s;
	}

	// Every student
	for (Student s : students)
	{
		// Get qr code from url and download as ./pictures/qr.png (file is overwritten for each student)
		s.GetQR_Code(exe_path + "\\pictures\\qr.png");

		// Create pdfs and download in ./PIDS/
		s.GetPDF(exe_path);
	}

	std::cout << "\n\nProcess Finished, Alhamdulillah.\nPress Enter to end...\n";
	std::cin.get();
	return 0;
}