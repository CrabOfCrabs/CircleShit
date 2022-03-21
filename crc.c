#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>
#include <time.h>
struct winsize w;

//this draw simple ascii circle
void crcdraw(int r,float cx,float cy,int sx,int sy){ //r is diameter cx/y is center sx/y is screen size
	int xy;
	for(xy = 0;xy<=sx*sy;xy++){
		int x = xy % sx,y = ceil(xy / sx);
		if(xy == y*sx){printf("\n");}

		if(y >= cy - r/2 && y <= cy + r/2){
			char pr = (pow(x-cx,2) + pow((y-cy)*2,2) <= r*r) ? '#':' ';
			printf("%c",pr);
		}
	}
}


//puts in the middle of the screen
int gravcrc9(){	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	int ms = 9;
	float //declare all the values 
	      cx = w.ws_col/2,cy = w.ws_row/2,  	//starting x,y
	      gF = 0.1, 				//gravity
	      Vx = 4,Vy = 1, 				//initial velocity
	      Fy = 0.98,Fx = 0.98; 			//floor & wall friction

	time_t start, now;struct timespec delay;delay.tv_sec = 0;delay.tv_nsec = ms * 999999L;time(&start);

	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		int sx = w.ws_col-1,sy = w.ws_row-1;
		int r = 10;
		
		Vy += gF;cx += Vx;cy += Vy;
		//y boundries collision
		if(cy+r/2 > sy){cy = sy-(r/2);Vy*=-Fy;Vx*=Fx;}
		else if(cy-r/2 < 1){cy = 1+(r/2); Vy*=-Fy;Vx*=Fx;}
		//x boundries collision
		if(cx+r/2 > sx){cx = sx-(r/2);Vx*=-Fx;Vy*=Fy;}
		else if(cx-r/2 < 1){cx = 1+(r/2);Vx*=-Fx;Vy*=Fy;}

		nanosleep(&delay,NULL);
		system("clear");

		crcdraw(r,cx,cy,sx,sy);//magic
	}
	return 0;
}

//puts in the middle of the screen
int rlcirc9(){	
	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		int sx = w.ws_col,sy = w.ws_row;
		int r = 10;
		int cx = sx/2,cy = sy/2;
		system("clear");

		crcdraw(r,cx,cy,sx,sy);//magic
	}
	return 0;
}

//simplest circle draw that i can think of :)
int simpcir(){
	for(int xy = 0;xy<10000;xy++){
		int x = xy % 100,y = ceil(xy / 100);
		if(xy == y*100){printf("\n");}
		if(y >= 45 && y <= 55){
			char pr = (pow(x-50,2) + pow(2*y-100,2) <= 100) ? '#':' ';
			printf("%c",pr);
		}
	}
return 0;
}


int main(){gravcrc9();
	//simpcir();
	//rlcirc9();
return 0;
}
