#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>
#include <time.h>
struct winsize w;

//this draw simple ascii circle
void crcdraw(int r,float cx,float cy,int sx,int sy){ //r is diameter cx/y is center sx/y is screen size
	for(int xy = 0;xy<=sx*sy;xy++){
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
	time_t start, now;
	struct timespec delay;
	delay.tv_sec = 0;
	delay.tv_nsec = ms * 999999L;
	time(&start);
	float cx = w.ws_col/2,cy = w.ws_row/2;
	float gF = 0.1;
	float Vx = 0,Vy = 0;
	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		int sx = w.ws_col,sy = w.ws_row;
		int r = 10;
		Vy += gF;
		cx += Vx;cy += Vy;
		if(cy+r/2 >= sy || cy-r/2 <= 0){
			if(cy<=cy-Vy){gF = 0;Vy = 0;}else{Vy*=-1;}
		}
		else{gF = 0.1;}
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

//simplest circle draw that uses printf i can think of :)
int simpcir(){
	for(int xy = 0;xy<10000;xy++){
		int x = xy % 100,y = ceil(xy / 100);
		if(xy == y*100){printf("\n");}
		if(y >= 45 && y <= 55){
			char pr = (pow(x-50,2) + pow((y-50)*2,2) <= 100) ? '#':' ';
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
