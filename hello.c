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

void
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
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
    
    return 0;

}


int write( int num){
    const char *text = "Hello World";
    HPDF_Page_TextOut (currentPage, currentX, 500, text);
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
