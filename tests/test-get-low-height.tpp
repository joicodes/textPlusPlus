def void start(){
	int x;
	changeFontSize("Helvetica", 12);
	x = getLowHeight();

	if(x == 6){
		write("Correct Height");
	}else{
		write("Incorrect Height");
	}
}