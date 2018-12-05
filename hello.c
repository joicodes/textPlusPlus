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

float textWidth;

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


void
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


int  addPage(void){

    HPDF_Page newPage;
    newPage = HPDF_AddPage(pdf);

    currentPage = newPage;

    pageNumber = pageNumber + 1;

    HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
    HPDF_Page_SetLineWidth(currentPage, 1);

    currentX = 0;
    currentY = pageHeight;
    
    return 0;

}


int write( char * text){
    HPDF_Rect rect;

    //currentX = 0;
    //currentY = pageHeight;

    rect.left = currentX + 25; // 25 is for margins
    rect.top = currentY - 25; // 25 is for margins
    rect.right = pageWidth - 25;
    rect.bottom = 0;

    HPDF_Page_BeginText(currentPage);
    HPDF_Page_TextRect(currentPage, rect.left, rect.top, rect.right, rect.bottom, text, HPDF_TALIGN_LEFT, NULL);
    HPDF_Page_EndText(currentPage);

    //update currentX and currentY?

    return 0;

}

int textOut( char * text){
	HPDF_REAL x_pos = 50; //Harcoded for now
	HPDF_REAL y_pos = 400; //Hardcoded for now

    HPDF_Page_BeginText(currentPage);
    HPDF_Page_SetFontAndSize (currentPage, times, 12);
    HPDF_Page_TextRect(currentPage, x_pos, y_pos, pageWidth - 25, 0, text, HPDF_TALIGN_LEFT, NULL);
    HPDF_Page_EndText(currentPage);

    return 0;

}

int moveTo(int dummy){
	//take page, x, and y position 
	HPDF_Page_MoveTo(currentPage, currentX, currentY);

	return 0;
}


int bold( ){

	// Helvetica Bold

	if ((currentFont == helvetica) || (currentFont == helveticaItalic)){
		

		currentFont = helveticaBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	
	}
	
	// Times Bold

	if ((currentFont == times) || (currentFont == timesItalic)){

		currentFont = timesBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

	}

	// Courier Bold

	if ((currentFont == courier) || (currentFont == courierItalic)){


		currentFont = courierBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

	}

	return 0;

}

int italic( ){

	// Helvetica Italic

	if ((currentFont == helvetica) || (currentFont == helveticaBold)){
		
		currentFont = helveticaItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}
	
	// Times Italic

	if ((currentFont == times) || (currentFont == timesBold)){

		currentFont = timesItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

	}

	// Courier Italic

	if ((currentFont == courier) || (currentFont == courierBold)){

		currentFont = courierItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	return 0;

}


int regular( ){

	// Helvetica 

	if ((currentFont == helveticaItalic) || (currentFont == helveticaBold)){

		currentFont = helvetica;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);

	}
	
	// Times Italic

	if ((currentFont == timesItalic) || (currentFont == timesBold)){

		currentFont = times;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	// Courier Italic

	if ((currentFont == courierItalic) || (currentFont == courierBold)){

		currentFont = courier;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);


	}

	return 0;

}


int changeColor( char * colorName ){
	
	if (strcmp( colorName, "black") == 0){
		HPDF_Page_SetRGBFill(currentPage, 0.0, 0.0, 0.0);
	}

	if (strcmp( colorName, "red") == 0){
		HPDF_Page_SetRGBFill(currentPage, 1.0, 0.0, 0.0);
	}
	if (strcmp( colorName, "green") == 0){
		HPDF_Page_SetRGBFill(currentPage, 0.0, 1.0, 0.0);
	}
	if (strcmp( colorName, "blue") == 0){
		HPDF_Page_SetRGBFill(currentPage, 0.0, 0.0, 1.0);
	}

	return 0;
} 



int changeFontSize (int ft, int newSize ){

	// Note FIX PARAMETERS to char * newFont, int newSize, hard coding for now
	char * newFont = "Courier";

	currentFont = HPDF_GetFont(pdf, newFont, NULL);
	currentSize = newSize;
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}




int drawLine( int num){

	int startX;
	int endX;
	int startY;
	int endY;

	// sample input
	startX = 10;
	startY = 400;
	endX = startX + 200;
	endY = startY;
	
	HPDF_Page_MoveTo(currentPage, startX, startY);
	HPDF_Page_LineTo(currentPage, endX, endY);
	HPDF_Page_Stroke(currentPage);

	return 0;

}

int drawRectangle( int num){
	
	// lower left point of rectangle	
	int x;  
	int y;

	// rectangle dimensions
	int height;
	int width;


	//sample input
	x = 30;
	y= 200;
	width  = 100;
	height = 100;

	HPDF_Page_Rectangle(currentPage, x, y, width, height);
	HPDF_Page_Stroke(currentPage);

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


    // Sets default color, size, and font

    //HPDF_Page_SetRGBFill(firstPage, 0.0, 0.0, 0.0);
    defaultFont = HPDF_GetFont (pdf, "Helvetica", NULL);
    currentFont = defaultFont;
    defaultSize = 12;
    currentSize = defaultSize;
    HPDF_Page_SetFontAndSize(firstPage, defaultFont, defaultSize); 

    pageHeight = HPDF_Page_GetHeight(firstPage);
    pageWidth = HPDF_Page_GetWidth(firstPage);

    HPDF_Page_SetLineWidth(firstPage, 1);

    currentX = 0;
    currentY = pageHeight;

    //HPDF_Page_BeginText (currentPage);


    //HPDF_Page_TextOut (currentPage, 60, 500, page_title); // prints text in specified position



    // Program starts
    start();



    // Ends program
    //HPDF_Page_EndText (currentPage);
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
