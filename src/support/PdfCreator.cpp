#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <hpdf.h>

#include "../headers/PdfCreator.h"
#include "../headers/Student.h"

using std::string;

// Error handler as defined by documentation
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
	std::cerr << "ERROR: error_no: " << (unsigned int)error_no << ", detail_no: " << (int)detail_no << "\n";
	throw std::exception();
}

/* Custom Function Declarations */
void PDFWriteLine(HPDF_Page page, string line, HPDF_Font font, HPDF_REAL Pos, HPDF_REAL x, HPDF_REAL y, HPDF_REAL font_size);
HPDF_Image PDFAddImage(HPDF_Doc pdf, HPDF_Page page, string ImRelativePath, HPDF_REAL Pos = NULL, HPDF_REAL x = 0, HPDF_REAL y = 0, HPDF_REAL w = NULL, HPDF_REAL h = NULL);

int CreatePdf(Student &s, string exe_path)
{
	HPDF_Doc pdf = HPDF_New(error_handler, NULL);
	std::cout << "LOG: CreatePDF Run\n";
	if (!pdf)
	{
		std::cout << "Error: couldn't create pdf object\n";
		return -1;
	}
	std::cout << "LOG: Pdf Created\n";

	try
	{
		HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

		HPDF_Page page = HPDF_AddPage(pdf);
		HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A5, HPDF_PAGE_PORTRAIT);
		std::cout << "LOG: Page Created.\n";

		string font_path = exe_path + "\\Calibri\\calibrib.ttf";
		// std::cout << "font_path: " << font_path << "\n";
		const char* cbfont = HPDF_LoadTTFontFromFile(pdf, font_path.c_str(), HPDF_TRUE);
		HPDF_Font calibri_bold = HPDF_GetFont(pdf, cbfont, NULL);
		std::cout << "LOG: Fonts Loaded\n";

		string logo_path = exe_path + "\\pictures\\logo.png";
		HPDF_Image Logo_Image = PDFAddImage(pdf, page, logo_path.c_str(), NULL, 0, 0, (HPDF_REAL)512 / 4, (HPDF_REAL)271 / 4);
		std::cout << "LOG: Logo Image added\n";

		string qr_path = exe_path + "\\pictures\\qr.png";
		HPDF_Image QR_Image = PDFAddImage(pdf, page, qr_path.c_str(), 1, NULL, 75, 170, 170);
		std::cout << "LOG: Qr Image added\n";

		PDFWriteLine(page, s.getPid(), calibri_bold, 1, NULL, 300, 65);
		std::cout << "LOG: PID Written\n";

		HPDF_REAL RectWidth = 300;
		HPDF_REAL RectHeight = 95;
		HPDF_Page_SetLineWidth(page, 1);
		HPDF_Page_Rectangle(page, (HPDF_Page_GetWidth(page) - RectWidth) / 2, HPDF_Page_GetHeight(page) - (320 + RectHeight),  RectWidth, RectHeight);
		HPDF_Page_Stroke(page);
		std::cout << "LOG: Rectangle Drawn\n";

		string StudentDetails[5] = 
		{
			"Academic Year: 2022 - 2023",
			"Family ID: " + s.getFamID(),
			"Year Level: " + s.getGrade() + "    Class: " + s.getTrack(),
			"Student REF: " + s.getFName(),
			"Student ID REF: " + s.getSNum()
		};

		HPDF_REAL CurPosX = (HPDF_Page_GetWidth(page) - RectWidth) / 2 + 20;
		HPDF_REAL CurPosY = 340;
		for (int i = 0; i < 5; i++)
		{
			PDFWriteLine(page, StudentDetails[i], calibri_bold, NULL, CurPosX, CurPosY + i * 15, 10);
		}
		std::cout << "LOG: Student Details Filled.\n";

		std::string pdf_path = exe_path;
		 std::cout << "LOG: PDF Path before: " << pdf_path << "\n";
		while (pdf_path[pdf_path.length() - 1] == '\\')
		{
			pdf_path.pop_back();
		}
		 std::cout << "LOG: PDF Path in between: " << pdf_path << "\n";
		while (pdf_path[pdf_path.length() - 1] != '\\')
		{
			pdf_path.pop_back();
		}
		pdf_path += "\\PIDs\\";
		std::cout << "LOG: PDF Path after: " << pdf_path << "\n";

		string pdfname = pdf_path + s.getFName() + " - " + s.getSNum() + ".pdf";
		HPDF_SaveToFile(pdf, pdfname.c_str());
		std::cout << "LOG: Saved PDF: " << pdfname << "\n";
	}
	catch (...)
	{
		HPDF_Free(pdf);
		return 1;
	}
	std::cout << "LOG: Freeing pdf\n";
	HPDF_Free(pdf);
	std::cout << "LOG: Freed pdf\n";
	return 0;
}

void PDFWriteLine(HPDF_Page page, string line, HPDF_Font font, HPDF_REAL Pos, HPDF_REAL x, HPDF_REAL y, HPDF_REAL font_size)
{
	HPDF_Page_SetFontAndSize(page, font, font_size);

	HPDF_REAL PHeight = HPDF_Page_GetHeight(page);
	HPDF_REAL PWidth = HPDF_Page_GetWidth(page);
	HPDF_REAL TWidth = HPDF_Page_TextWidth(page, line.c_str());
	if (Pos == 1)
	{
		x = (PWidth - TWidth) / 2;
	}

	HPDF_Page_BeginText(page);
	HPDF_Page_TextOut(page, x, PHeight - y, line.c_str());
	HPDF_Page_EndText(page);
}

HPDF_Image PDFAddImage(HPDF_Doc pdf, HPDF_Page page, string ImRelativePath, HPDF_REAL Pos, HPDF_REAL x, HPDF_REAL y, HPDF_REAL w, HPDF_REAL h)
{
	HPDF_Image Image = HPDF_LoadPngImageFromFile(pdf, ImRelativePath.c_str());
		
	HPDF_REAL PHeight = HPDF_Page_GetHeight(page);
	HPDF_REAL PWidth = HPDF_Page_GetWidth(page);

	if (!w)
	{
		w = HPDF_Image_GetWidth(Image);
	}

	if (!h)
	{
		h = HPDF_Image_GetHeight(Image);
	}

	if (Pos == 1)
	{
		x = (PWidth - w) / 2;
	}

	HPDF_Page_DrawImage(page, Image, x, PHeight - y - h, w, h);

	return Image;
}