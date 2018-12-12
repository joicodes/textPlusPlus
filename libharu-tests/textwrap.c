#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"


jmp_buf env;
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}


int main(int argc, char **argv)
{
    HPDF_Doc pdf;
    HPDF_Font font;
    HPDF_Page page;
    HPDF_Rect rect;
    HPDF_TextWidth width;
    HPDF_REAL pageHeight;
    HPDF_REAL pageWidth;


    HPDF_REAL currentX;
    HPDF_REAL currentY;

    const char *line_one = "When I was three and Bailey four, we had arrived in the musty little town, wearing tags on our wrists whichanstructed-'To Whom It May Concern'-that we were Marguerite and Bailey Johnson Jr., from Long Beach, California, en route to Stamps, Arkansas, c/o Mrs. Annie Henderson.Our parents had decided to put an end to their calamitous marriage, and Father shipped us home to his mother. A porter had been charged with our welfare-he got off the train the next day in Arizona-and our tickets were pinned to my brother's inside coat pocket.I don't remember much of the trip, but after we reached the segregated southern part of the journey, things must have looked up. Negro passengers, who always traveled with loaded lunch boxes, felt sorry for 'the poor little motherless darlings' and plied us with cold fried chicken and potato salad.Years later I discovered that the United States had been crossed thousands of times by frightened Black children traveling alone to their newly affluent parents in Northern cities, or back to grandmothers in Southern towns when the urban North reneged on its economic promises.The town reacted to us as its inhabitants had reacted to all things new before our coming. It regarded us a while without curiosity but with caution, and after we were seen to be harmless (and children) it closed in around us, as a real mother embraces a stranger's child. Warmly, but not too familiarly.We lived with our grandmother and uncle in the rear of the Store (it was always spoken of with a capital s), which she had owned some twenty-five years.Early in the century, Momma (we soon stopped calling her Grandmother) sold lunches to the sawmen in the lumberyard (east Stamps) and the seedmen at the cotton gin (west Stamps). Her crisp meat pies and cool lemonade, when joined to her miraculous ability to be in two places at the same time, assured her business success. From being a mobile lunch counter, she set up a stand between the two points of fiscal interest and supplied the workers' needs for a few years. Then she had the Store built in the heart of the Negro area. Over the years it became the lay center of activities in town. On Saturdays, barbers sat their customers in the shade on the porch of the Store, and troubadours on their ceaseless crawlings through the South leaned across its benches and sang their sad songs of The Brazos while they played juice harps and cigarbox guitars.";

    const char *line_two = "by Michelle Obama";

    pdf = HPDF_New(error_handler, NULL); //NULL -> void * user data used for error handling

    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    font = HPDF_GetFont (pdf, "Helvetica", NULL);
    page = HPDF_AddPage (pdf); //creates new page and adds it to end of document

    pageHeight = HPDF_Page_GetHeight(page);
    pageWidth = HPDF_Page_GetWidth(page);
    currentX = 0 + 25;
    currentY = pageHeight - 25;

    int right_margin = pageWidth - 25;
    int left_margin = 25;
    int page_limit = pageWidth - (2 * left_margin);

    int f_height = HPDF_Font_GetCapHeight(font);
    int f_lower_height = HPDF_Font_GetXHeight (font);
    int f_real_h = f_height * 12 / 1000.0;
    int f_real_h_l = f_lower_height * 12 / 1000.0;

    int descent = HPDF_Font_GetDescent(font);
    int descent_real = descent * 12 /1000.0;
    printf("font height: %d\n lowercase: %d descent: %d\n", f_real_h, f_real_h_l, descent_real);

    //printf("%d\n", page_limit);
    //printf("%d\n", right_margin);
    //printf("%f\n", pageWidth);
    
    
    HPDF_Page_SetFontAndSize (page, font, 12); 
    HPDF_Page_BeginText(page);
    
    int pos = 0;
    for(;;){
        int b = HPDF_Page_MeasureText(page, line_one, page_limit, HPDF_TRUE, NULL);
        printf("text measuretext:%d\n", b);

        char *start = &line_one[pos];
        char *end = &line_one[pos + b];
        while(*end != ' '){
            end-=1;
        }
        end+=1;

        char *curr_string = (char *) malloc(b);
        memcpy(curr_string, start, end - start);
        
        int a = HPDF_Page_TextWidth(page, curr_string);
        printf("text width:%d\n", a);


        HPDF_Page_TextOut (page, 25, pageHeight - 25, curr_string);

        HPDF_Page_TextOut (page, 25, pageHeight - 25 - f_real_h - f_real_h, "YOLOLLLLO I'M SO HAPPPPY HAPPY");

        free(curr_string);
        break;
    }

      
    HPDF_Page_EndText (page);

    /* save the document to a file */
    HPDF_SaveToFile (pdf, "text.pdf");

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}