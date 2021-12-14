#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>


int RLtimeren(){
	int ms = 9;
	time_t start, now;
	struct timespec delay;
	float MDirY = 0,MDirX = 0,grav = 0,ypos,xpos,VectrY,VectrX=1;
	delay.tv_sec = 0;
	delay.tv_nsec = ms * 999999L;
	time(&start);
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// 1:for frames 2,3: x,y screen size 4,5: x,y figure center 6,7: x,y elipse radius
	
	float InfT[] = {1,w.ws_col,w.ws_row,w.ws_col/2+0.5,w.ws_row/2,10,10};
	ypos = InfT[3];
	xpos = InfT[4];
	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);		
		float InfT[] = {1,w.ws_col,w.ws_row,w.ws_col/2+0.5,w.ws_row/2,10,10};
		MDirY=MDirY-grav+VectrY;
		MDirX=MDirX+VectrX;
		ypos+=MDirY;
		xpos+=VectrX;
                if((xpos>=w.ws_col-InfT[6]-1 && xpos>xpos-VectrX) || (xpos<=0+InfT[6] && xpos<xpos-VectrX)){
			VectrX*=-1;
		}
		int RLtimeren(){
	int ms = 9;
	time_t start, now;
	struct timespec delay;
	float MDirY = 0,MDirX = 0,grav = 0,ypos,xpos,VectrY,VectrX=1;
	delay.tv_sec = 0;
	delay.tv_nsec = ms * 999999L;
	time(&start);
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// 1:for frames 2,3: x,y screen size 4,5: x,y figure center 6,7: x,y elipse radius
	
	float InfT[] = {1,w.ws_col,w.ws_row,w.ws_col/2+0.5,w.ws_row/2,10,10};
	ypos = InfT[3];
	xpos = InfT[4];
	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);		
		float InfT[] = {1,w.ws_col,w.ws_row,w.ws_col/2+0.5,w.ws_row/2,10,10};
		MDirY=MDirY-grav+VectrY;
		MDirX=MDirX+VectrX;
		ypos+=MDirY;
		xpos+=VectrX;
                if((xpos>=w.ws_col-InfT[6]-1 && xpos>xpos-VectrX) || (xpos<=0+InfT[6] && xpos<xpos-VectrX)){
			VectrX*=-1;
		}
		else if(xpos>w.ws_col-InfT[5]-1 && xpos>=xpos-MDirX){
		VectrX = 0;
		}
		else
		{

		}

		if((ypos<=-w.ws_row+InfT[5]+1 && ypos<ypos-MDirY) || (ypos>=-10 && ypos>ypos-MDirY)){
			MDirY*=-1;
		}
		else if(ypos<-w.ws_row+InfT[5]+1 && ypos<=ypos-MDirY){
		grav = 0;
		MDirY = 0;
		}
		else
		{
		grav= 0.1;

		}
		
		
		float rwy = InfT[6];
		float rwx = InfT[5]*2;
		float mx = xpos;
		float my = -ypos;

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
					if((dx/rx) + (dy/ry) <= 1){

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
		
		printf("\032[2J");
		printf("\032[0;0H");
		nanosleep(&delay,NULL);
	}
	return 0;
}


int main(){

	RLtimeren();
	return 0;
}
