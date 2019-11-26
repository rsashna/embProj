/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher and Graphic Demo
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include <stdlib.h>

extern unsigned char ClockLEDOn;
extern unsigned char ClockLEDOff;
extern unsigned char ClockANI;
extern unsigned char dkir[];
extern unsigned char isthis[];
extern unsigned char huh[];
extern unsigned char smFR[];
extern unsigned char smFL[];
extern unsigned char smD[];
extern unsigned char pball[];
extern unsigned char expb[];

//GAME GLOBALS
int movePi=120;
int ranum;
int i=0;
int raFlag = 0;
int endFlag = 100;



int selector=0;
int temp=0;
void delay(int g){
int p,b;
int i = 0;
for (p = 0; p < g; p++){
b = p+1;
}
}

int delayUntilRi(){
  int p,b;
	while(get_button() !=  KBD_RIGHT){
		if(get_button() ==  KBD_DOWN){
		return(1);
		}
			b = p+1;

	}
	return(2);
}

void playGame1(){
		GLCD_Clear  (Black);
		GLCD_DisplayString(0, 0, 1, "Les Games     ");
		ranum = (rand() % (5 - 1 + 1) + 1);

	  while (get_button() !=  KBD_DOWN){
			for(i=0; i<ranum; i++ ){
		GLCD_Clear  (Black);
		GLCD_Bitmap (  movePi,   150, 60,  60, smD); //x then y
		delay(30000000);//exactly 1s
		movePi+=15;
		GLCD_Clear  (Black);
		GLCD_Bitmap (  movePi,   150, 60,  60, smD);
		delay(30000000);
		movePi-=15;
			}
			raFlag = (rand() % (3 - 2 + 1) + 2);
			switch (raFlag){
				case 2:
					GLCD_Clear  (Black);
					for(i=0; i<endFlag; i++){//endFlag originally 100 loops difficulty
					GLCD_Bitmap (  movePi,   150, 60,  50, smFR); //x then y
					delay(30000);
						if(get_button() ==  KBD_RIGHT){
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Blue);
							GLCD_DisplayString(0, 0, 1, "CORRECT!      ");
							delay(30000000);
							endFlag-=20;
						break;
						}
						else if(i == (endFlag-1)){
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Blue);
							GLCD_DisplayString(0, 0, 1, "MISSED!      ");
							GLCD_DisplayString(0, 0, 1, "-END OF GAME-      ");
							delay(30000000);
							endFlag=100; //reset difficulty for future replay
							return;
						}
					}
					break;
				case 3:
				GLCD_Clear  (Black);
				for(i=0; i<endFlag; i++){//endFlag originally 100 loops
					GLCD_Bitmap (  movePi,   150, 60,  55, smFL);
					delay(30000);
					if(get_button() ==  KBD_LEFT){
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Blue);
							GLCD_DisplayString(0, 0, 1, "CORRECT!      ");
							delay(30000000);
							endFlag-=20;
						break;
						}
						else if(i == (endFlag-1)){
							GLCD_SetBackColor(White);
							GLCD_SetTextColor(Blue);
							GLCD_DisplayString(0, 0, 1, "MISSED!      ");
							GLCD_DisplayString(0, 0, 1, "-END OF GAME-      ");
							delay(30000000);
							endFlag=100; //reset difficulty for future replay
							return;
						}
					}
				break;
			}
		}
		GLCD_Clear  (White); //down pressed

}



void showGalery(){

while(get_button() !=  KBD_DOWN){
    GLCD_Clear  (White);
    GLCD_SetBackColor(Blue);
    GLCD_SetTextColor(Yellow);
    GLCD_DisplayString(0, 0, 1, "Galerie des Memes      ");
    GLCD_Bitmap (  100,   50, 100, 92, expb); //x then y
    temp=delayUntilRi();
		if(temp==1)
			return;
    GLCD_Clear  (White);
		GLCD_DisplayString(0, 0, 1, "Galerie des Memes      ");
    GLCD_Bitmap (  100,   50, 100, 60, dkir);
    temp=delayUntilRi();
		if(temp==1){
			temp=0;
			return;
		}
    GLCD_Clear  (White);
		GLCD_DisplayString(0, 0, 1, "Galerie des Memes      ");
    GLCD_Bitmap (  100,   50, 100, 100, huh);
    temp=delayUntilRi();
		if(temp==1){
			temp=0;
			return;
		}
    GLCD_Clear  (White);
		GLCD_DisplayString(0, 0, 1, "Galerie des Memes      ");
    GLCD_Bitmap (  100,   50, 100, 60, isthis);
    temp=delayUntilRi();
		if(temp==1){
			temp=0;
			return;
		}
    }
		GLCD_Clear  (White);

}

	void selectorChoose(char inc){
	if (selector==0 && inc=='p'){
	selector=1;//gal
	GLCD_DisplayString(5, 0, 1, "~Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games             ");
	}
	if (selector==1 && inc=='p'){
	selector=2;//aud
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, "~L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games             ");
	}
	if (selector==2 && inc=='p'){
	selector=3;//game
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, "~Les Games             ");
	}
	if (selector==3 && inc=='p'){
	selector=3;//game
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, "~Les Games             ");
	}
	if (selector==0 && inc=='m'){
	selector=0;
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games             ");
	}
	if (selector==1 && inc=='m'){
	selector=1;
	GLCD_DisplayString(5, 0, 1, "~Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games             ");
	}
	if (selector==2 && inc=='m'){
	selector=1;
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, "~L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games             ");
	}
	if (selector==3 && inc=='m'){
	selector=2;
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, "~L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games             ");
	}

	}
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
<<<<<<< Updated upstream
int main (void) {                     /* Main Program                       */
=======
int main (void) {                       /* Main Program                       */
>>>>>>> Stashed changes

  LED_Init ();
  GLCD_Init();
  KBD_Init();

	GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, 1, " COE718                ");
	GLCD_SetTextColor(White);
  GLCD_DisplayString(1, 0, 1, " Final Project         ");
  GLCD_DisplayString(2, 0, 1, "                       ");
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);

	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games             ");

	SysTick_Config(SystemCoreClock/100);

while(1){
//CHECK SELECTOR VALUES
	if (get_button() ==  KBD_DOWN){
	selectorChoose('p');
	}
		if (get_button() ==  KBD_UP){
	selectorChoose('m');
	}

	if (get_button() ==  KBD_SELECT){
//case
		switch (selector){
			case 1:
				if (get_button() ==  KBD_SELECT){
					LED_On(0);
					LED_On(1);
					LED_Off(2);
					LED_Off(3);
					LED_Off(4);
					LED_Off(5);
					GLCD_SetBackColor(White);
					GLCD_SetTextColor(Blue);
				GLCD_DisplayString(10, 0, 1, " Galerie des Memes  ");
				showGalery();
				GLCD_Clear  (White);
				}
				break;
			case 2:
				if (get_button() ==  KBD_SELECT){
					LED_On(2);
					LED_On(3);
					LED_Off(0);
					LED_Off(1);
					LED_Off(4);
					LED_Off(5);
					//showAudio();
					break;
				}
				break;
			case 3:
				if (get_button() ==  KBD_SELECT){
					LED_On(4);
					LED_On(5);
					LED_Off(0);
					LED_Off(1);
					LED_Off(2);
					LED_Off(3);
					GLCD_Clear  (White);
					GLCD_SetBackColor(White);
					GLCD_SetTextColor(Blue);
				GLCD_DisplayString(1, 0, 1, "     Les Games  ");
				GLCD_DisplayString(3, 0, 1, "> When Pika signals,");
				GLCD_DisplayString(4, 0, 1, "raise that flag!");
				GLCD_DisplayString(5, 0, 1, "> Response has");
				GLCD_DisplayString(6, 0, 1, "to be faster ");
				GLCD_DisplayString(7, 0, 1, "each round.");
					delay(30000000);//exactly 1s
				GLCD_DisplayString(8, 0, 1, "   -----3-----    ");
					delay(30000000);//exactly 1s
				GLCD_DisplayString(8, 0, 1, "    ----2----  ");
					delay(30000000);//exactly 1s
				GLCD_DisplayString(8, 0, 1, "      --1--  ");
				playGame1();
				GLCD_Clear  (White);
				}
				break;
		}
	}
		}





}
