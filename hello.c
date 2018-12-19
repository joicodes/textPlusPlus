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

int pnumber;

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
int alignment;


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
	pnumber = pnumber + 1;

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

	alignment = 0;
	return 0;
}

int right(){
	alignment = 1;
	return 0;
}

int center(){
	alignment = 2;
	return 0;
}

int write(char * text){
    // align: 0 means left, 1 means right, 2 means center

    int right_margin = pageWidth - 25;
    int left_margin = 25;
    int page_limit = pageWidth - (2 * left_margin);

    int f_height_point = HPDF_Font_GetCapHeight(currentFont);
    int f_real_h = f_height_point * currentSize / 1000.0;

    int last_line = 0;

    int pos = 0;

    int textWidth = 0;
    int move_right = 0;

    HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize); 
    HPDF_Page_BeginText(currentPage);

    for(;;){

    	int bytes = HPDF_Page_MeasureText(currentPage, text, page_limit, HPDF_TRUE, NULL);
        char *start = &text[pos];
        char *end = &text[pos + bytes];
        size_t length = end - start;
        
        char *curr_string = (char *) malloc(length + 1);
        memcpy(curr_string, start, length); 
        curr_string[length] = '\0';

        switch(alignment) {
        	case 0: ; //left alighnment
        		HPDF_Page_TextOut (currentPage, currentX, currentY, curr_string);
        		break;

        	case 1: ; //right alighnment
        		textWidth = HPDF_Page_TextWidth(currentPage, curr_string);
                move_right = (pageWidth - 25) - (textWidth + 25);
                HPDF_Page_TextOut (currentPage, currentX + move_right, currentY, curr_string);
                break;

        	case 2: ; //means center
        		textWidth = HPDF_Page_TextWidth(currentPage, curr_string);
                move_right = ((pageWidth - 25) - (textWidth + 25)) / 2;
                HPDF_Page_TextOut (currentPage, currentX + move_right, currentY, curr_string);
                break;
        }
        
        free(curr_string);
        currentY = currentY - 2 * f_real_h;
        text = text + bytes;

        //for the case the person writes stuff thats longer
        //than the page can fit
        if (currentY <= 25){ //here 25 is the bottom margin
            HPDF_Page_EndText (currentPage);

            HPDF_Page newPage;
            newPage = HPDF_AddPage(pdf);

            currentPage = newPage;

            HPDF_Page_BeginText (currentPage);
            HPDF_Page_SetFontAndSize (currentPage, currentFont, currentSize);
            
            currentX = 25; //set it to the margin
            currentY = pageHeight - 25;
        }

        if (last_line == 1){
            break;
        }

        if (strlen(text) <= bytes){
            last_line = 1;
        }

    }

    HPDF_Page_EndText (currentPage);

    return 0;
}

int textOut(int x, int y, char * text){
	// align: 0 means left, 1 means right, 2 means center

    currentX = x;
    currentY = y;

    int right_margin = pageWidth - 25;
    int left_margin = 25;
    int page_limit = pageWidth - (2 * left_margin);

    int f_height_point = HPDF_Font_GetCapHeight(currentFont);
    int f_real_h = f_height_point * currentSize / 1000.0;

    int last_line = 0;

    int pos = 0;

    int textWidth = 0;
    int move_right = 0;

    HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize); 
    HPDF_Page_BeginText(currentPage);

    for(;;){

    	int bytes = HPDF_Page_MeasureText(currentPage, text, page_limit, HPDF_TRUE, NULL);
        char *start = &text[pos];
        char *end = &text[pos + bytes];
        size_t length = end - start;
        
        char *curr_string = (char *) malloc(length + 1);
        memcpy(curr_string, start, length); 
        curr_string[length] = '\0';

        switch(alignment) {
        	case 0: ; //left alighnment
        		HPDF_Page_TextOut (currentPage, currentX, currentY, curr_string);
        		break;

        	case 1: ; //right alighnment
        		textWidth = HPDF_Page_TextWidth(currentPage, curr_string);
                move_right = (pageWidth - 25) - (textWidth + 25);
                HPDF_Page_TextOut (currentPage, currentX + move_right, currentY, curr_string);
                break;

        	case 2: ; //means center
        		textWidth = HPDF_Page_TextWidth(currentPage, curr_string);
                move_right = ((pageWidth - 25) - (textWidth + 25)) / 2;
                HPDF_Page_TextOut (currentPage, currentX + move_right, currentY, curr_string);
                break;
        }
        
        free(curr_string);
        currentY = currentY - 2 * f_real_h;
        text = text + bytes;

        //for the case the person writes stuff thats longer
        //than the page can fit
        if (currentY <= 25){ //here 25 is the bottom margin
            HPDF_Page_EndText (currentPage);

            HPDF_Page newPage;
            newPage = HPDF_AddPage(pdf);

            currentPage = newPage;

            HPDF_Page_BeginText (currentPage);
            HPDF_Page_SetFontAndSize (currentPage, currentFont, currentSize);
            
            currentX = 25; //set it to the margin
            currentY = pageHeight - 25;
        }

        if (last_line == 1){
            break;
        }

        if (strlen(text) <= bytes){
            last_line = 1;
        }

    }

    HPDF_Page_EndText (currentPage);

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



int pageNumber(int x, int y){

	char strPageNumber[100];
	sprintf(strPageNumber, "%d", pnumber);

    HPDF_Page_BeginText(currentPage);
    HPDF_Page_TextOut(currentPage, x, y, strPageNumber);
    HPDF_Page_EndText(currentPage);

	return 0;
}


// Getter Functions
int getTextWidth(char *text){
	return HPDF_Page_TextWidth(currentPage, text);
} 

int getPageHeight(){
	
	return (int)pageHeight;
} 

int getPageWidth(){
	
	return (int)pageWidth;
} 

int getCurrentX(){
    return (int)currentX;
}

int getCurrentY(){
    return (int)currentY;
}

// FUNCTIONS FOR STANDARD LIBRARY


// Writes a centered single line on the current page
int pageTitle(char* text){

	HPDF_Page_SetFontAndSize (currentPage, currentFont, currentSize);
	tw = HPDF_Page_TextWidth (currentPage, text);
	HPDF_Page_BeginText (currentPage);
	HPDF_Page_TextOut (currentPage, (HPDF_Page_GetWidth(currentPage) - tw) / 2, HPDF_Page_GetHeight (currentPage) - currentSize, text);
	HPDF_Page_EndText (currentPage);

	return 0;

}

// Headings - changes the font size accordingly (based on HTML standards)
int heading1(){
	currentSize = 32;
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}

int heading2(){
	currentSize = 24;
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}

int heading3(){
	currentSize = 18;
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}

int heading4(){
	currentSize = 16;
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}

int heading5(){
	currentSize = 14;
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}

int heading6(){
	currentSize = 12;
	HPDF_Page_SetFontAndSize(currentPage, currentFont, currentSize);
	return 0;
}

// Draws a horizantal in the current position
int horizantalLine(){

	HPDF_Page_MoveTo(currentPage, currentX, currentY);
	HPDF_Page_LineTo(currentPage, pageWidth, currentY);
	HPDF_Page_Stroke(currentPage);

	return 0;
}

int table(int row, int column, int tableWidth, int tableHeight){

	int horizontalMax;
	int verticalMax;
	int rowHeight;
	int columnWidth;

	int r;
	int c;

	int i;
	int j;

	r = row +1;
	c = column + 1;


	if (tableWidth > (pageWidth - currentX)){
		horizontalMax = pageWidth - currentX;
	} 
	else {
		horizontalMax = tableWidth;
	}

	if (tableHeight >  currentY){
		verticalMax = currentY;
	} 
	else {
		verticalMax = tableHeight;
	}

	rowHeight = verticalMax / row;
	columnWidth = horizontalMax / column;


	// Draw horizantal lines
	 for ( i = 0 ; i < r ; i++ ){

		HPDF_Page_MoveTo(currentPage, currentX, currentY - (rowHeight * i));
		HPDF_Page_LineTo(currentPage, horizontalMax, currentY - (rowHeight * i));
		HPDF_Page_Stroke(currentPage);

	 }
    
	// Draw vertical lines
	 for ( j = 1 ; j < c ; j++ ){

		HPDF_Page_MoveTo(currentPage, currentX + (columnWidth * j), currentY);
		HPDF_Page_LineTo(currentPage, currentX + (columnWidth * j), currentY - verticalMax);
		HPDF_Page_Stroke(currentPage);

	 }

	 return 0;

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
    pnumber = 1;


    /* sets default color, size, and font */
    defaultFont = HPDF_GetFont (pdf, "Helvetica", NULL);
    currentFont = defaultFont;
    defaultSize = 12;
    currentSize = defaultSize;
    HPDF_Page_SetFontAndSize(firstPage, defaultFont, defaultSize); 

	/* sets the default alignment to left*/
	alignment = 0;

    /* initializes value for pageHeight and pageWidth */
    pageHeight = HPDF_Page_GetHeight(firstPage);
    pageWidth = HPDF_Page_GetWidth(firstPage);

    /* sets line  stroke width */
    HPDF_Page_SetLineWidth(firstPage, 1);

	/* sets  X and Y cooridintes to top left of page */
    currentX = 25;
    currentY = pageHeight - 25;

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
