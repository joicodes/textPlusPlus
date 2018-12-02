def void start()
{

  italic(0);
  changeColor("blue");
   write("Helvetica Italic Page One!");
  
  addPage(0);
  changeFontSize(45);
  changeColor("red");
  bold(0);
  write("Helvetica Bold Page Two");
  
  addPage(0);
  changeFontSize(30);
  regular(0);
  write("Plain Ol' Helvetica Page Three");
  
  addPage(0);   
  return;
}
