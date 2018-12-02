#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"


char fname[256];
HPDF_Doc pdf;


HPDF_Page firstPage;
HPDF_Page currentPage;
int pageNumber;


HPDF_Font defaultFont;
HPDF_Font currentFont;
HPDF_REAL defaultSize;
HPDF_REAL currentSize;
char *style;


HPDF_REAL pageHeight;
HPDF_REAL pageWidth;


HPDF_REAL currentX;
HPDF_REAL currentY;

extern void start();

jmp_buf env;

HPDF_Font helvetica;
HPDF_Font helveticaItalic;
HPDF_Font helveticaBold;
	
HPDF_Font times;
HPDF_Font timesItalic;
HPDF_Font timesBold;

HPDF_Font courier;
HPDF_Font courierItalic;
HPDF_Font courierBold;

// adding a comment
void
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


int  addPage( int num){

    HPDF_Page newPage;
    newPage = HPDF_AddPage(pdf);

    HPDF_Page_EndText(currentPage);

    currentPage = newPage;
    HPDF_Page_BeginText (currentPage);

    pageNumber = pageNumber + 1;

    currentX = 0;
    currentY = pageHeight;
    
    return 0;

}


int write( char * num){
    const char *text = "Hello World";
    HPDF_Page_TextOut (currentPage, currentX, currentY-currentSize, num);
    return 0;

}


int bold( int num ){

	// Helvetica Bold

	if ((currentFont == helvetica) || (currentFont == helveticaItalic)){
		
		HPDF_Page_EndText(currentPage);

		currentFont = helveticaBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);	
	}
	
	// Times Bold

	if ((currentFont == times) || (currentFont == timesItalic)){

		HPDF_Page_EndText(currentPage);

		currentFont = timesBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);
	}

	// Courier Bold

	if ((currentFont == courier) || (currentFont == courierItalic)){

		HPDF_Page_EndText(currentPage);

		currentFont = courierBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);
	}

	return 0;

}

int italic( int num ){

	// Helvetica Italic

	if ((currentFont == helvetica) || (currentFont == helveticaBold)){
		
		HPDF_Page_EndText(currentPage);

		currentFont = helveticaItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);	
	}
	
	// Times Italic

	if ((currentFont == times) || (currentFont == timesBold)){

		HPDF_Page_EndText(currentPage);

		currentFont = timesItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);
	}

	// Courier Italic

	if ((currentFont == courier) || (currentFont == courierBold)){

		HPDF_Page_EndText(currentPage);

		currentFont = courierItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);
	}

	return 0;

}


int regular( int num ){

	// Helvetica 

	if ((currentFont == helveticaItalic) || (currentFont == helveticaBold)){
		
		HPDF_Page_EndText(currentPage);

		currentFont = helvetica;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);	
	}
	
	// Times Italic

	if ((currentFont == timesItalic) || (currentFont == timesBold)){

		HPDF_Page_EndText(currentPage);

		currentFont = times;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);
	}

	// Courier Italic

	if ((currentFont == courierItalic) || (currentFont == courierBold)){

		HPDF_Page_EndText(currentPage);

		currentFont = courier;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

		HPDF_Page_BeginText(currentPage);
	}

	return 0;

}



int main(int argc)
{
    // Starts Document 

    pdf = HPDF_New(error_handler, NULL);   

    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    } 
	
	
   // Initializes Fonts
	helvetica = HPDF_GetFont(pdf, "Helvetica", NULL);
	helveticaItalic = HPDF_GetFont(pdf, "Helvetica-Oblique", NULL);
	helveticaBold = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);

	times = HPDF_GetFont(pdf, "Times-Roman", NULL);
	timesItalic = HPDF_GetFont(pdf, "Times-Italic", NULL);
	timesBold = HPDF_GetFont(pdf, "Times-Bold", NULL);

	courier = HPDF_GetFont(pdf, "Courier", NULL);
	courierItalic = HPDF_GetFont(pdf, "Courier-Oblique", NULL);
	courierBold = HPDF_GetFont(pdf, "Courier-Bold", NULL);

  // Creates First Page

    firstPage = HPDF_AddPage(pdf); 
    currentPage = firstPage;
    pageNumber = 1;

    defaultFont = HPDF_GetFont (pdf, "Helvetica", NULL);
    currentFont = defaultFont;
    defaultSize = 12;
    currentSize = defaultSize;
    HPDF_Page_SetFontAndSize(firstPage, defaultFont, defaultSize); 

    pageHeight = HPDF_Page_GetHeight(firstPage);
    pageWidth = HPDF_Page_GetWidth(firstPage);

    currentX = 0;
    currentY = pageHeight;

    HPDF_Page_BeginText (currentPage);


    //HPDF_Page_TextOut (currentPage, 60, 500, page_title); // prints text in specified position



    // Program starts
    start();



    // Ends program
    HPDF_Page_EndText (currentPage);
    HPDF_SaveToFile (pdf, "text.pdf");
    HPDF_Free (pdf);

    return 0;
}

#ifdef BUILD_TEST
int main()
{
    hello(0);
    return 0;
}
#endif
