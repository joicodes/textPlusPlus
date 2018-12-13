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
    int font_size = 12;


    HPDF_REAL currentX;
    HPDF_REAL currentY;

    const char *line_one = "At school we were given an hour-long break for lunch each day. Because my mother didn’t work and our apartment was so close by, I usually marched home with four or five other girls in tow, all of us talking nonstop, ready to sprawl on the kitchen floor to play jacks and watch All My Children while my mom handed out sandwiches. This, for me, began a habit that has sustained me for life, keeping a close and high-spirited council of girlfriends—a safe harbor of female wisdom. In my lunch group, we dissected whatever had gone on that morning at school, any beefs we had with teachers, any assignments that struck us as useless. Our opinions were largely formed by committee. We idolized the Jackson 5 and weren’t sure how we felt about the Osmonds. Watergate had happened, but none of us understood it. It seemed like a lot of old guys talking into microphones in Washington, D.C., which to us was just a faraway city filled with a lot of white buildings and white men. My mom, meanwhile, was plenty happy to serve us. It gave her an easy window into our world. As my friends and I ate and gossiped, she often stood by quietly, engaged in some household chore, not hiding the fact that she was taking in every word. In my family, with four of us packed into less than nine hundred square feet of living space, we’d never had any privacy anyway. It mattered only sometimes. Craig, who was suddenly interested in girls, had started taking his phone calls behind closed doors in the bathroom, the phone’s curlicue cord stretched taut across the hallway from its wall-mounted base in the kitchen.As Chicago schools went, Bryn Mawr fell somewhere between a bad school and a good school. Racial and economic sorting in the South Shore neighborhood continued through the 1970s, meaning that the student population only grew blacker and poorer with each year. There was, for a time, a citywide integration movement to bus kids to new schools, but Bryn Mawr parents had successfully fought it off, arguing that the money was better spent improving the school itself. As a kid, I had no perspective on whether the facilities were run-down or whether it mattered that there were hardly any white kids left. The school ran from kindergarten all the way through eighth grade, which meant that by the time I’d reached the upper grades, I knew every light switch, every chalkboard and cracked patch of hallway. I knew nearly every teacher and most of the kids. For me, Bryn Mawr was practically an extension of home. As I was entering seventh grade, the Chicago Defender, a weekly newspaper that was popular with African American readers, ran a vitriolic opinion piece that claimed Bryn Mawr had gone, in the span of a few years, from being one of the city’s best public schools to a “run- down slum” governed by a “ghetto mentality.” Our school principal, Dr. Lavizzo, immediately hit back with a letter to the editor, defending his community of parents and students and deeming the newspaper piece “an outrageous lie, which seems designed to incite only feelings of failure and flight.Dr. Lavizzo was a round, cheery man who had an Afro that puffed out on either side of his bald spot and who spent most of his time in an office near the building’s front door. It’s clear from his letter that he understood precisely what he was up against. Failure is a feeling long before it becomes an actual result. It’s vulnerability that breeds with self- doubt and then is escalated, often deliberately, by fear. Those “feelings of failure” he mentioned were everywhere already in my neighborhood, in the form of parents who couldn’t get ahead financially, of kids who were starting to suspect that their lives would be no different, of families who watched their better-off neighbors leave for the suburbs or transfer their children to Catholic schools. There were predatory real estate agents roaming South Shore all the while, whispering to homeowners that they should sell before it was too late, that they’d help them get out while you still can. The inference being that failure was coming, that it was inevitable, that it had already half arrived. You could get caught up in the ruin or you could escape it. They used the word everyone was most afraid of— “ghetto”—dropping it like a lit match. My mother bought into none of this. She’d lived in South Shore for ten years already and would end up staying another forty. She didn’t buy into fearmongering and at the same time seemed equally inoculated against any sort of pie-in-the-sky idealism. She was a straight-down-the-line realist, controlling what she could. At Bryn Mawr, she became one of the most active members of the PTA, helping raise funds for new classroom equipment, throwing appreciation dinners for the teachers, and lobbying for the creation of a special multigrade classroom that catered to higher-performing students. This last effort was the brainchild of Dr. Lavizzo, who’d gone to night school to get his PhD in education and had studied a new trend in grouping students by ability rather than by age—in essence, putting the brighter kids together so they could learn at a faster pace.";

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
    printf("page_limit: %d\n", page_limit);

    int f_height = HPDF_Font_GetCapHeight(font);
    int f_real_h = f_height * font_size / 1000.0;
    
    HPDF_Page_SetFontAndSize (page, font, 12); 
    HPDF_Page_BeginText(page);

    int last_line = 0;
    int alignment = 1; // 0 means left, 1 means right, 2 means center

    int pos = 0;

    switch(alignment) {
        case 0 : ; //left alighnment
            for(;;){

                int bytes = HPDF_Page_MeasureText(page, line_one, page_limit, HPDF_TRUE, NULL);
                char *start = &line_one[pos];
                char *end = &line_one[pos + bytes];
                size_t length = end - start;
                
                
                char *curr_string = (char *) malloc(length + 1);
                memcpy(curr_string, start, length); 
                curr_string[length] = '\0';
                
                HPDF_Page_TextOut (page, 25, currentY, curr_string);
                free(curr_string);

                currentY = currentY - 2 * f_real_h;
                line_one = line_one + bytes;

                //for the case the person writes stuff thats longer
                //than the page can fit
                if (currentY <= 25){
                    HPDF_Page_EndText (page);

                    HPDF_Page newPage;
                    newPage = HPDF_AddPage(pdf);

                    page = newPage;

                    HPDF_Page_BeginText (page);
                    HPDF_Page_SetFontAndSize (page, font, 12);
                    
                    currentX = 0 + 25;
                    currentY = pageHeight - 25;
                }

                if (last_line == 1){
                    break;
                }

                if (strlen(line_one) <= bytes){
                    last_line = 1;
                }
            }

            case 1 : ; //right alighnment
            for(;;){

                int bytes = HPDF_Page_MeasureText(page, line_one, page_limit, HPDF_TRUE, NULL);
                char *start = &line_one[pos];
                char *end = &line_one[pos + bytes];
                size_t length = end - start;
                
                
                char *curr_string = (char *) malloc(length + 1);
                memcpy(curr_string, start, length); 
                curr_string[length] = '\0';
                int textWidth = HPDF_Page_TextWidth(page, curr_string);

                printf("******textWidth*******\n");
                printf("%d\n", textWidth);
                printf("******textWidth*******\n");

                int move_right = page_limit - textWidth;
                printf("******moveright*******\n");
                printf("%d\n", move_right);
                printf("******moveright*******\n");
                
                HPDF_Page_TextOut (page, 25 + move_right, currentY, curr_string);
                free(curr_string);

                currentY = currentY - 2 * f_real_h;
                line_one = line_one + bytes;

                //for the case the person writes stuff thats longer
                //than the page can fit
                if (currentY <= 25){
                    HPDF_Page_EndText (page);

                    HPDF_Page newPage;
                    newPage = HPDF_AddPage(pdf);

                    page = newPage;

                    HPDF_Page_BeginText (page);
                    HPDF_Page_SetFontAndSize (page, font, 12);
                    
                    currentX = 0 + 25;
                    currentY = pageHeight - 25;
                }

                if (last_line == 1){
                    break;
                }

                if (strlen(line_one) <= bytes){
                    last_line = 1;
                }
            }
    }    

    HPDF_Page_EndText (page);

    /* save the document to a file */
    HPDF_SaveToFile (pdf, "text.pdf");

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}