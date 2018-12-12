/*
 * << Haru Free PDF Library 2.0.0 >> -- attach.c
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"


// Document Handling
char fname[256];
HPDF_Doc pdf;

// Page Handling 
HPDF_Page firstPage;
HPDF_Page currentPage;

HPDF_REAL pageHeight;
HPDF_REAL pageWidth;

int pageNumber;

//Text Handling
HPDF_REAL currentX;
HPDF_REAL currentY;

float tw;

// Font Handling
HPDF_Font defaultFont;
HPDF_Font currentFont;
HPDF_REAL defaultSize;
HPDF_REAL currentSize;

HPDF_Font helvetica;
HPDF_Font helveticaItalic;
HPDF_Font helveticaBold;
	
HPDF_Font times;
HPDF_Font timesItalic;
HPDF_Font timesBold;

HPDF_Font courier;
HPDF_Font courierItalic;
HPDF_Font courierBold;

float textWidth;
char *alignment;

int *ptr_one;

ptr_one = (int *)malloc(sizeof(int));

if (ptr_one == 0)
{
	return 1;
}

*ptr_one = 25;

extern void start();

jmp_buf env;

// Error Handling

void
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


// PAGE HANDLING FUNCTIONS 

int  addPage(){

	/* creates and adds new page to PDF */
	HPDF_Page newPage;
	newPage = HPDF_AddPage(pdf);

	/* updates current page and page number */
	currentPage = newPage;
	pageNumber = pageNumber + 1;

	/* sets the font, size, and line width for page */
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	HPDF_Page_SetLineWidth(currentPage, 1);

    /* initializes value for pageHeight and pageWidth */
    pageHeight = HPDF_Page_GetHeight(currentPage);
    pageWidth = HPDF_Page_GetWidth(currentPage);

	/* sets  X and Y cooridintes to top left of page */
	currentX = 0;
	currentY = pageHeight;

	return 0;
}

// TEXT HANDLING FUNCTIONS 

int left(){
	alignment = "left";
	return 0;
}

int right(){
	alignment = "right";
	return 0;
}

int center(){
	alignment = "center";
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

int textOut( char * text, int x, int y){
	HPDF_REAL x_pos = x; //Harcoded for now 50
	HPDF_REAL y_pos = y; //Hardcoded for now 400

    HPDF_Page_BeginText(currentPage);
    HPDF_Page_SetFontAndSize (currentPage, times, 12);
    HPDF_Page_TextRect(currentPage, x_pos, y_pos, pageWidth - 25, 0, text, HPDF_TALIGN_LEFT, NULL);
    HPDF_Page_EndText(currentPage);

    return 0;

}

int moveTo(int x , int y){
	//take page, x, and y position 
	HPDF_REAL x_pos = x; //Harcoded for now 50
	HPDF_REAL y_pos = y;
	HPDF_Page_MoveTo(currentPage, x_pos, y_pos);

	return 0;
}


// FONT HANDLING FUNCTIONS 

int bold(){

	/* changes current font to Helvetica Bold */
	if ((currentFont == helvetica) || (currentFont == helveticaItalic)){
		currentFont = helveticaBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	/* changes current font to Times Bold */
	if ((currentFont == times) || (currentFont == timesItalic)){
		currentFont = timesBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	/* changes current font to Courier Bold */
	if ((currentFont == courier) || (currentFont == courierItalic)){
		currentFont = courierBold;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	return 0;
}

int italic(){

	/* changes current font to Helvetica Italic */
	if ((currentFont == helvetica) || (currentFont == helveticaBold)){	
		currentFont = helveticaItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	/* changes current font to Times Italic */
	if ((currentFont == times) || (currentFont == timesBold)){
		currentFont = timesItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	/* changes current font to Courier Italic */
	if ((currentFont == courier) || (currentFont == courierBold)){
		currentFont = courierItalic;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	return 0;
}

int regular(){

	/* changes current font to Helvetica */ 
	if ((currentFont == helveticaItalic) || (currentFont == helveticaBold)){
		currentFont = helvetica;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	/* changes current font to Times */
	if ((currentFont == timesItalic) || (currentFont == timesBold)){
		currentFont = times;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	/* changes current font to Courier */
	if ((currentFont == courierItalic) || (currentFont == courierBold)){
		currentFont = courier;
		HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	}

	return 0;
}

int changeColor( float red, float green, float blue){

	/* sets the RGB values for the font */
	HPDF_Page_SetRGBFill(currentPage, red, green, blue);
	return 0;
} 

int changeFontSize (char * font, int newSize){

	/* updates current font and size */
	currentFont = HPDF_GetFont(pdf, font, NULL);
	currentSize = newSize;

	/* set new font and size to current page */
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}


// SHAPE + LINE HANDLING FUNCTIONS 

int drawLine( int startX, int startY, int endX, int endY){
	
	// Draws a line from (startX, startY) to (endX, endY)
	HPDF_Page_MoveTo(currentPage, startX, startY);
	HPDF_Page_LineTo(currentPage, endX, endY);
	HPDF_Page_Stroke(currentPage);

	return 0;
}

int drawRectangle( int lowerLeftX, int lowerLeftY, int rectangleWidth, int rectangleHeight){
	
	/* draws a rectangle on dimentions (rectangleWidth x rectangleHeight) 
	 with bottom left corner of rectangle at (lowerLeftX, lowerLeftY) */

	HPDF_Page_Rectangle(currentPage, lowerLeftX, lowerLeftY, rectangleWidth, rectangleHeight);
	HPDF_Page_Stroke(currentPage);

	return 0;
}


// GETTER FUNCTIONS


int getPageNumber(){
	
	return 1;
}

int getTextWidth(char *text){

	//*ptr_tw = HPDF_Page_TextWidth(currentPage, text);
	// *ptr_tw = 25.0;

	return *ptr_one;

} 

float getPageHeight(){
	
	return 1;
} 

float getPageWidth(){
	
	return 1;
} 


int main(int argc){

    /* starts program
	 * creates a PDF document */

    pdf = HPDF_New(error_handler, NULL);   

    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    } 
	
	
    /* initializing fonts */
	helvetica = HPDF_GetFont(pdf, "Helvetica", NULL);
	helveticaItalic = HPDF_GetFont(pdf, "Helvetica-Oblique", NULL);
	helveticaBold = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);

	times = HPDF_GetFont(pdf, "Times-Roman", NULL);
	timesItalic = HPDF_GetFont(pdf, "Times-Italic", NULL);
	timesBold = HPDF_GetFont(pdf, "Times-Bold", NULL);

	courier = HPDF_GetFont(pdf, "Courier", NULL);
	courierItalic = HPDF_GetFont(pdf, "Courier-Oblique", NULL);
	courierBold = HPDF_GetFont(pdf, "Courier-Bold", NULL);


	/* creates and adds new page to PDF */
    firstPage = HPDF_AddPage(pdf); 
    currentPage = firstPage;
    pageNumber = 1;


    /* sets default color, size, and font */
    defaultFont = HPDF_GetFont (pdf, "Helvetica", NULL);
    currentFont = defaultFont;
    defaultSize = 12;
    currentSize = defaultSize;
    HPDF_Page_SetFontAndSize(firstPage, defaultFont, defaultSize); 

	/* sets the default alignment to left*/
	alignment = "left";

    /* initializes value for pageHeight and pageWidth */
    pageHeight = HPDF_Page_GetHeight(firstPage);
    pageWidth = HPDF_Page_GetWidth(firstPage);

    /* sets line  stroke width */
    HPDF_Page_SetLineWidth(firstPage, 1);

	/* sets  X and Y cooridintes to top left of page */
    currentX = 0;
    currentY = pageHeight;

    /* program starts */
    start();


    /* ends program 
     * saves file as 'text.pdf' */
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
