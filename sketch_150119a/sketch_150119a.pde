float x[]={0,0,0},y=0,flug=0;

void setup(){
size(300,300);

}

void draw(){
  background(255);
  quad(x[0],y,x[0]+30,y,x[0]+30,y+30,x[0],y+30);
  x[1]=x[0]+30;
  quad(x[1],y,x[1]+30,y,x[1]+30,y+30,x[1],y+30);
  x[2]=x[0]+60;
  quad(x[2],y,x[2]+30,y,x[2]+30,y+30,x[2],y+30);
  
  
  if(y>=300)y=0;
  
  if(flug==0)x[0]+=1;
  if(flug==1)x[0]-=1;
  
  if(x[2]==200){
    flug=1;
    y+=30;
  }
  if(x[0]==0){
  flug=0;
  y+=30;
  }
  
}
