def void start()
{

	/*  Header */
	center();
	changeFontSize("Times-Roman", 18);
	textOut(0, 775, "COMS W4115 Programming Languages and Translators");
	textOut(0, 755, "Homework Assignment 3");
	left();
	changeFontSize("Times-Roman", 12);
	textOut(100, 725, "Prof. Stephen A. Edwards                  Due Tuesday, December 4th, 2018 at 11:59 PM");


	/* Instructions */
	changeFontSize("Times-Roman", 10);
	setRMargin(45);
	textOut(40, 700, "   Submit this assignment online via Courseworks as a PDF file. Fill in or annotate this PDF or print it out, write on it, and scan it. Please keep your answer in the boxes.");
	textOut(45, 675, " Do this assignment alone. You may consult the instructor and the TAs, but not other students.");


	/* Name + Uni Field */
	textOut(40, 645, "Name:");
	drawRectangle(70, 640, 350, 20 );
	textOut(430, 645, "Uni:");
	drawRectangle(455, 640, 50, 20);


	/* Problem 1 */
	textOut(40, 615, "1. (20 pts.) For the following C array on a processor with the usual alignment rules,");
	changeFontSize("Courier", 10);
	bold();
	textOut(50, 600, "int");
	regular();
	textOut(70, 600, "a[2][3];");


	/* Part A */
	changeFontSize("Times-Roman", 10);
	textOut(55, 575, "(a)  Show the order in which its elements are arranged in memory.");
	drawRectangle(70, 500, 475, 70);

	/* Part B */	
	textOut(55, 485, "(b)  Write an expression for the byte address of");
	bold();
	changeFontSize("Courier", 10);
	textOut(246, 485, "a[i][j]");
	changeFontSize("Times-Roman", 10);
	textOut(290, 485, "in terms of");
	italic();
	textOut(337, 485, "a");
	regular();
	textOut(345, 485, "(the address of the start of the array),");
	
	italic();
	textOut(495, 485, "i,");
	regular();
	textOut(503, 485, "and");

	italic();
	textOut(520, 484, "j.");
	regular();
	
	drawRectangle(70, 460, 475, 20);

	/* Part C */

	textOut(55, 440, "(c)  Verify parts a) and b) by writing a small C program that");
	bold();
	textOut(298, 440, "tests your hypothesis.");
	regular();
	textOut(390, 440, "Examine the assembly language output with");
	setRMargin(70);
	textOut(70, 430, "the C compiler's -S flag (e.g. gcc -O -S array.c). Such a program should be simple and contain and access such an array, but not be so simple that the compiler optimizes most of it away. On the next page, ");
	bold();
	textOut(390, 418, "include an annotated assembly listing");
	regular();
	textOut(70, 408, "that explains how it verified your hypothesis. Make sure the assembly listing is no more than about 40 lines, either by simplifying your program or trimming the output.");
	textOut(70, 380, "C program:");

	drawRectangle(70, 100, 475, 270);




























}
