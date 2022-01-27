#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>

//loop hell
int rlcirc9(){	
	struct winsize w; 
	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		int sx = w.ws_col,sy = w.ws_row;
		int r = 10;
		int cx = sx/2,cy = sy/2;
		system("clear");

			for(int xy = 0;xy<sx*sy;xy++){
				int x = xy % sx,y = ceil(xy / sx);
				if(xy == y*sx){printf("\n");}

				if(y >= cy - r/2 && y <= cy + r/2){
					char pr = (pow(x-cx,2) + pow((y-cy)*2,2) <= r*r) ? '#':' ';
					printf("%c",pr);
				}
			}
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


int main(){
	//simpcir();
	//rlcirc9();
return 0;
}
