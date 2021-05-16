#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "conio_repl.h"


bool gameover = false;
int	height = 19;
int width=23;
char cactus_asset[5][8] = {"  /\\  ",
					  		 	"/\\||  ",
					 			"||||/\\",
					 			"\\    /",
					 			" |  | "};
char dino_norm[6][17]= {"         ____    ",
							   " \\     _| o _\\  ",
							   "  |   /   /_     ",
							   "  |  |   |-      ",
							   "  \\ /___/       ",
							   "     | |         " };
char dino_down[4][17]= { 
							   "     ____ ____   ",
					   		   " \\  /   __|_o__\\ ",
					   		   "  \\/___/''      ",
					   		   "    | |          "};
char bird [3][10]= {"         ",
					   "<o)  <(>",
					   "          "};
			   		   
struct Cactus_Dat{
	int cac_iter;
	int inter_cac_length;
	int cactus_num;
	int inter_cac_length_gen;
}Cactus;

struct Dino_Dat{
	int jump_flag;
	int jump_y;
	int jump_x;
	bool upper_flag;
	bool feet_flag;
	bool print_dino;
}Dino;

struct Bird_Dat{
	bool bird_print_flag;
	bool print_bird;
	int bird_x_in;
	int bird_y_in;
	int flap_flag;
	int bird_y_iter;
	int bird_cactus_length;
}Bird;

bool nextBool(double probability)
{
    return rand() <  probability * ((double)RAND_MAX + 1.0);
}

void draw(struct Dino_Dat *Dino, struct Cactus_Dat *Cactus, struct Bird_Dat *Bird){
	srand(time(0));			
	if(Dino->jump_flag == 1 || Dino->jump_flag==0){
		switch(Dino->feet_flag){
			case false:
				dino_norm[5][7]='`';
				dino_norm[5][5]='|';
				Dino->feet_flag = true;
				break;
			case true:
				dino_norm[5][7]='|';
				dino_norm[5][5]='`';
				Dino->feet_flag = false;
				break;
		}
	}else if (Dino->jump_flag==2){
		switch(Dino->feet_flag){
			case false:
				dino_down[3][6]='`';
				dino_down[3][4]='|';
				Dino->feet_flag = true;
				break;
			case true:
				dino_down[3][6]='|';
				dino_down[3][4]='`';
				Dino->feet_flag = false;
				break;
		}
	}					
	Bird->bird_y_in = 0;
	switch (Bird->flap_flag){
		case 1:
			bird[0][4]='(';
			bird[0][5]='/';
			bird[2][4]=' ';
			bird[2][5]=' ';
			bird[1][3]='<';
			bird[1][4]='<';
			Bird->flap_flag = 2;
			break;
		case 2:
			bird[0][4]=' ';
			bird[0][5]=' ';
			bird[2][4]=' ';
			bird[2][5]=' ';
			bird[1][3]='(';
			bird[1][4]='|';
			Bird->flap_flag = 3;
			break;
		case 3:
			bird[0][4]=' ';
			bird[0][5]=' ';
			bird[2][4]='(';
			bird[2][5]='\\';
			bird[1][3]='<';
			bird[1][4]='<';
			Bird->flap_flag = 4;
			break;
		case 4:
			bird[0][4]=' ';
			bird[0][5]=' ';
			bird[2][6]=' ';
			bird[2][7]=' ';
			bird[1][3]='(';
			bird[1][4]='|';
			Bird->flap_flag = 1;
			break;
	}
	system("clear");
	int print_fail;	   
    int i,j,k,r;
    Dino->print_dino = false;
	k = 0;
	bool print_cac [4]= {false, false, false,false};
	int x_coor [4] = {0,0,0,0};
	int y_coor [4] = {0,0,0,0};
	int print;
	for (i = 0; i < height; i++) {
        int l = 0;
        if (Dino->print_dino){
        	k++;
        	Dino->print_dino = false;
		}
		for(r=0;r<Cactus->cactus_num;r++){
				x_coor[r] = 0;
		        if (print_cac[r]){
		        	y_coor[r]++;
		        	print_cac[r] = false;
				}
		}
		if (Bird->print_bird){
				Bird->bird_y_in++;
				Bird->print_bird=false;
		}
		print_fail = 0;
		Bird->bird_x_in = 0;
		for (j = 0; j < 5*width; j++) {
			print = 0;
            if (i == 0 || i == height - 1 || i == height - 3) {
                printf("-");
            }else{
            	Cactus->inter_cac_length = 0;
	            print_fail = 1;
	            for (r=0;r<Cactus->cactus_num;r++){
	              	if (j<5*width-Cactus->cac_iter-Cactus->inter_cac_length+Cactus->inter_cac_length_gen*Cactus->cactus_num&&
					  j>5*width-8-Cactus->cac_iter-Cactus->inter_cac_length+Cactus->inter_cac_length_gen*Cactus->cactus_num&&
					  i<height-3&&i>height-9){
						printf("%c", cactus_asset[y_coor[r]][x_coor[r]]);
						print_cac[r] = true;
						x_coor[r]++;
						print++;				
					}else{
						print_fail++;
					}
					Cactus->inter_cac_length+=Cactus->inter_cac_length_gen;
						
				}
				switch(Dino->jump_flag){
					case 1:
						if(i <= Dino->jump_y && j <= 14 && i >= Dino->jump_y-5){
							printf("%c", dino_norm[k][l]);
				           	Dino->print_dino = true;
				           	l++;
				           	print++;
				        }else{
							print_fail++;
						}
						break;
					case 2:
						if(i <= height-3 && j <= 15 && i >= height-7){
							Dino->jump_x = 7;
			            	Dino->jump_y = 14;
							printf("%c", dino_down[k][l]);
			            	Dino->print_dino = true;
			            	l++;
			            	print++;
			            	
						}else{
							print_fail++;
						}
						break;
					case 0:
						if(i <= height-4 && j <= 14 && i >= height-9){
							Dino->jump_x = 0;
							printf("%c", dino_norm[k][l]);
			            	Dino->print_dino = true;
			            	l++;
			            	print++;
			            	
						}else{
							print_fail++;
						}
						break;	
				}
				if(j<5*width+Bird->bird_cactus_length-Cactus->cac_iter+Cactus->inter_cac_length_gen*Cactus->cactus_num&&
				j>5*width+Bird->bird_cactus_length-11-Cactus->cac_iter+Cactus->inter_cac_length_gen*Cactus->cactus_num&&
				i<5+Bird->bird_y_iter&&
				i>1+Bird->bird_y_iter&&
				Bird->bird_print_flag==true){
		    		printf("%c", bird[Bird->bird_y_in][Bird->bird_x_in]);
		    		Bird->bird_x_in++;
		    		Bird->print_bird = true;
		    		print++;
				}else{
					print_fail++;
				}		
			}
			if (print_fail==Cactus->cactus_num+3){
				printf(" ");
			}
			if (print==2){
				gameover = true;
				break;			
			}
    	}
	    printf("\n");
	}

	if (Dino->jump_y>6 && Dino->jump_flag==1 && Dino->upper_flag==false){
		Dino->jump_y -= 2;
		if (Dino->jump_y==6){
			Dino->jump_x++;
		}
		if (Dino->jump_x==7){
			Dino->upper_flag = true;
			Dino->jump_x = 0;
		}
	}else if (Dino->jump_y<=height-5 && Dino->jump_flag==1){
		Dino->jump_y += 2;
	}else if (Dino->jump_flag==1){
		Dino->jump_flag = 0;
		Dino->upper_flag = false;
		Dino->jump_y = 14;
	}
	Cactus->cac_iter+=3;
	if (Cactus->cac_iter > 5*width + (Cactus->inter_cac_length)+(8*Cactus->cactus_num)+30){
		Cactus->cactus_num = rand()%3+1;
		Bird->bird_print_flag = nextBool(1);
		Bird->bird_y_iter = rand()%8;
		if (Cactus->cactus_num != 3){
			Cactus->inter_cac_length_gen = rand()%10+9 ;
		}else{
			Cactus->inter_cac_length_gen = 9;
		}
		Cactus->cac_iter = 0;
	}
	if(Dino->jump_flag==2){
    	Dino->jump_flag=0;
	}
}
	    


void input (struct Dino_Dat *Dino){
    if (kbhit()){
	    switch (getch()){
            case 'w':
                Dino->jump_flag = 1;
                break;
            case 's':
                Dino->jump_flag = 2;
                break;
            case 'x':
               gameover = 1;
                break;
        }
	}
}


int main(){
	Dino.jump_flag = 0;
	Dino.jump_y = 14;
	Dino.jump_x = 0;
	Dino.upper_flag = false;
	Dino.feet_flag = false;
	Cactus.cac_iter = 0;
	Cactus.inter_cac_length = 0;
	Cactus.cactus_num = 1;
	Cactus.inter_cac_length_gen = 9;
	Bird.bird_print_flag = true;
	Bird.print_bird = false;
	Bird.bird_x_in = 0;
	Bird.bird_y_in = 0;
	Bird.flap_flag = 1;
	Bird.bird_y_iter = 0;
	Bird.bird_cactus_length=40;
	struct Dino_Dat *dino_ptr = &Dino;
	struct Cactus_Dat *cactus_ptr = &Cactus;
	struct Bird_Dat *bird_ptr = &Bird;	
	int score = 0;
	while (!gameover){
		usleep(100000);
		score += 1;
		draw(dino_ptr, cactus_ptr, bird_ptr);
		input(dino_ptr);
		printf("\n\n Score : %d", score);
	}
	printf("\n\n Gameover!!!");
	
					   
	
}
