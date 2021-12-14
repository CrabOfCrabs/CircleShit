#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>


int step(float InfT[],float ypos)
{

	float rwy = InfT[6];
	float rwx = InfT[5]*2;
	float mx = InfT[3];
	float my = ypos;

	//print frame
	for(int f=1;f<=InfT[0];f++){
		//print y axis
		for(int y=1;y<=InfT[2];y++){

			//clears a line of old frame
			for(int ch=1;ch<InfT[2];ch++){
				printf("\b");
			}
			//print x axis
			for(int x=1;x<=InfT[1];x++){
				float dx = (x-mx)*(x-mx);
				float dy = (y-my)*(y-my);
				float rx = (rwx)*(rwx);
				float ry = (rwy)*(rwy);

				//checks top
				if((dx/rx) + (((y-0.5-my)*(y-0.5-my))/ry) <= 1){

					//full if top and bottom
					if((dx/rx) + (dy/ry) <= 1){
						fputs("█",stdout);}
					else{
						fputs("▀",stdout);}

				//checks bottom
				}else if((dx/rx) + (dy/ry) <= 1){
					fputs("▄",stdout);}

				//in no top or bottom then non
				else{
					fputs(" ",stdout);}
			}
			printf("\n");
		}
		fflush(stdout);}
	return 0;
}




int main(){

	int ms = 10;
	time_t start, now;
	struct timespec delay;
	float MDir = 0,grav = 0,ypos;
	delay.tv_sec = 0;
	delay.tv_nsec = ms * 1000000L;
	time(&start);
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// 1:for frames 2,3: x,y screen size 4,5: x,y figure center 6,7: x,y elipse radius
	
	float InfT[] = {1,w.ws_col,w.ws_row,w.ws_col/2+0.5,11,10,10};
	ypos = InfT[4];
	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		float InfT[] = {1,w.ws_col,w.ws_row,w.ws_col/2+0.5,11,10,10};
		MDir = MDir-grav;
		ypos=ypos+MDir;
		
		if((ypos<=-w.ws_row+InfT[6]+1 && ypos<ypos-MDir) || (ypos>=-10 && ypos>ypos-MDir)){
			MDir*=-1;
		}else if(ypos<-w.ws_row+InfT[6]+1 && ypos<=ypos-MDir){
			grav = 0;
			MDir = 0;
		}else if(!(ypos<-w.ws_row+InfT[6]+1 && ypos<=ypos-MDir))
			grav = 0.1
		}
	
		printf("\033[2J");
		printf("\033[0;0H");
		nanosleep(&delay,NULL);
		step(InfT,-ypos);				
		

	}
	return 0;
}
