float x=0,y=0,flug=0;

void setup(){
size(300,300);

}

void draw(){
  background(255);
  quad(x,y,x+100,y,x+100,y+30,x,y+30);
  
  if(y>=300)y=0;
  
  if(flug==0)x+=1;
  if(flug==1)x-=1;
  
  if(x==200){
    flug=1;
    y+=30;
  }
  if(x==0){
  flug=0;
  y+=30;
  }
  
}
