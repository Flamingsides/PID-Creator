#include <iostream>
#include <string>

#include "../headers/Student.h"
#include "../headers/GetPicture.h"
#include "../headers/PdfCreator.h"

using std::string;

// Get appropriate grade name from an array defined in Student.h
string Student::convert_grade(int grade)
{
	// Adjusting index
	return grades[grade + 2];
}

Student::Student
(
	// Parameters
	 string qr_url,
	 string pid,
	 string family_id,
	 string full_name,
	 string student_number,
	 string grade,
	 string track
)
{  
	// Setting attributes
	this->qr_url = qr_url;
	this->pid = pid;
	this->family_id = family_id;
	this->full_name = full_name;
	this->student_number = student_number;
	this->grade = this->convert_grade(std::stoi(grade));
	this->track = track;
}

// Overloading insertion operator for output stream
std::ostream &operator<<(std::ostream &out, const Student &s)
{
	out << "=========================\n";
	out << "QR: " << s.qr_url << "\n";
	out << "PID: " << s.pid << "\n";
	out << "Family ID: " << s.family_id << "\n";
	out << "Full Name: " << s.full_name << "\n";
	out << "Student Number: " << s.student_number << "\n";
	out << "Grade: " << s.grade << "\n";
	out << "Track: " << s.track << "\n";
	out << "=========================\n";
	return out;
}

// Getters
string Student::getQR_URL(void) { return this->qr_url; }
string Student::getPid(void)	{ return this->pid; }
string Student::getFamID(void)	{ return this->family_id; }
string Student::getFName(void)	{ return this->full_name; }
string Student::getSNum(void)	{ return this->student_number; }
string Student::getGrade(void)	{ return this->grade; }
string Student::getTrack(void)	{ return this->track; }

// Getting QR Code
void Student::GetQR_Code(string destination)
{
	// Retrieve qr.png from url given; $qr_url
	int saved = GetPicture(this->qr_url, destination);
	if (!saved)
	{
		// Update
		std::cout << "\nLOG: QR Retreived: " << this->getSNum() << "\n";
	}
	else
	{
		// Update
		std::cerr << "ERROR: QR Retreival Failed: " << this->getSNum() << "\n";
	}
}

// Create pdf for student
void Student::GetPDF(string exe_path)
{
	// Pass Student object to $CreatePdf() from PdfCreator.cpp
	CreatePdf(*this, exe_path);
}