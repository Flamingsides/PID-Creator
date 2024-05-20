#pragma once

#include <ostream>
#include <string>

using std::string;

class Student
{
	private:
		string qr_url;
		string pid;
		string family_id;
		string full_name;
		string student_number;
		string grade;
		string track;
	
		const string grades[14] = 
		{"Pre-KG", "KG1", "KG2", "Y1", "Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9", "Y10", "Y11"};

		string convert_grade(int grade);

	public:
		Student
		(
		 string qr_url,
		 string pid,
		 string family_id,
		 string full_name,
		 string student_number,
		 string grade,
		 string track
		);

		string getQR_URL(void);
		string getPid(void);
		string getFamID(void);
		string getFName(void);
		string getSNum(void);
		string getGrade(void);
		string getTrack(void);

		void GetQR_Code(string destination);
		void GetPDF(string exe_path);

	friend std::ostream &operator<<(std::ostream &out, const Student &s);
};

