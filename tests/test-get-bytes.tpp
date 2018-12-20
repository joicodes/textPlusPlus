def void start(){
	int x;
	x = getTextBytes("Hello World", 25, 25);

	/* Hello World is < page_limit so should return bytes in Hello World */
	if(x == 11){
		write("Correct Bytes to fit on Page");
	}else{
		write("Incorrect Bytes to fit on Page");
	}
}