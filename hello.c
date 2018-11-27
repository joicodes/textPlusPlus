#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"

int hello(int argc)
{
	HPDF_Doc pdf;
	HPDF_Font font;
	HPDF_Page page;

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
