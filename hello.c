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

jmp_buf env;

error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

 void startDoc(){
	
    pdf = HPDF_New(error_handler, NULL);    

    firstPage = HPDF_AddPage(pdf); 
    currentPage = firstPage;
    pageNumber = 1;

    defaultFont = HPDF_GetFont (pdf, "Helvetica", NULL);
    defaultSize = 12;
    HPDF_Page_SetFontAndSize(firstPage, defaultFont, defaultSize); 

    pageHeight = HPDF_Page_GetHeight(firstPage);
    pageWidth = HPDF_Page_GetWidth(firstPage);

    currentX = 0;
    currentY = pageHeight;

    HPDF_Page_BeginText (currentPage); 

}


void addPage(){

    HPDF_Page newPage;
    newPage = HPDF_AddPage(pdf);

    HPDF_Page_EndText(currentPage);

    currentPage = newPage;
    HPDF_Page_BeginText (currentPage);

    pageNumber = pageNumber + 1;

    currentX = 0;
    currentY = pageHeight;

}



void endDoc(){

    HPDF_Page_EndText (currentPage); 

    HPDF_SaveToFile (pdf, "text.pdf");

    HPDF_Free (pdf);

}

void write(char* text){
    HPDF_Page_TextOut (currentPage, currentX, 500, text);
}




int hello(int argc)
{

	const char *page_title = "Hello World";

	pdf = HPDF_New(NULL, NULL); //NULL -> void * user data used for error handling

    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    font = HPDF_GetFont (pdf, "Helvetica", NULL);
    page = HPDF_AddPage (pdf); //creates new page and adds it to end of document


    HPDF_Page_SetFontAndSize (page, font, 24); 

    HPDF_Page_BeginText (page); //begins text object and sets text position to (0, 0)


    HPDF_Page_TextOut (page, 60, 500, page_title); // prints text in specified position


    HPDF_Page_EndText (page); //ends a text object

    /* save the document to a file */
    HPDF_SaveToFile (pdf, "text.pdf");

    /* clean up */
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
