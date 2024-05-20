#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../headers/ReadTSV.h"

const char DELIMITER = '\t';

/* 
Function that returns a 2 - dimensional vector containing data from given data.tsv file
2-dimensional vector in the form:
{
	{QR_Url, PID, Family_ID, Full_Name, Student_Number, Grade, Track},  <-- Student 1
	{QR_Url, PID, Family_ID, Full_Name, Student_Number, Grade, Track},  <-- Student 2
	...
	{QR_Url, PID, Family_ID, Full_Name, Student_Number, Grade, Track},  <-- Student n where n is the number of students
}
*/
std::vector<std::vector<std::string>> GetData(std::string filename)
{
	// .tsv file to read data from
	std::ifstream DataFile;
	// Temporarily stores a line from $DataFile
	std::string line;
	// Vector of vectors, each meant to contain a record (data on a specific student)
	std::vector<std::vector<std::string>> data;
	// Temporarily stores each record to be placed in $data
	std::vector<std::string> record;
	// Temporarily holds each field (one piece of data on a student) to be put into $record
	std::string field;

	// Open data file from given relative path
	DataFile.open(filename);	
	
	// If file successfully opened, 
	if (DataFile.is_open())
	{
		// While loop goes through all lines in DataFile, storing them in line
		while (getline(DataFile, line))
		{
			// For every character in line
			for (const char c : line)
			{
				// If character is the delimiter
				if (c == DELIMITER)
				{
					// Add the current contents of field in the vector record
					record.push_back(field);
					// Reset field value
					field = "";
				}
				// If the character is not the delimiter
				else
				{
					// Append it to field
					field += c;
				}
			}
			// Add the last value of field to record
			// We need to do this as there is no delimiter at the end of a line
			record.push_back(field);
			// Reset field
			field = "";

			// Add record to data
			data.push_back(record);
			// Reset record
			record.clear();
		}
	}
	else
	{
		// Update
		std::cout << "File Could Not Be Opened!\n";
	}
	
	// 2-dimensional vector with student data
	return data;
}