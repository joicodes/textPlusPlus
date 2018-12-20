def void start(){
	int x;
	changeFontSize("Helvetica", 12);
	x = getCapHeight();

	if(x == 8){
		write("Correct Height");
	}else{
		write("Incorrect Height");
	}
}