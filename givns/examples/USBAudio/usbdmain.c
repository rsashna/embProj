/*----------------------------------------------------------------------------
 * Name:    usbmain.c
 * Purpose: USB Audio Class Demo
 * Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"
//#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
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
extern  void SystemClockUpdate(void);
extern uint32_t SystemFrequency;
uint8_t  Mute;                                 /* Mute State */
uint32_t Volume;                               /* Volume Level */

////////////////////START GAME AND GALLERY FUNCTIONS

//GAME GLOBALS
int movePi=120;
int ranum;
int i=0;
int raFlag = 0;
int endFlag = 100;
int cvs.height = 210;
int cvs.width = 240;

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

int checkCol(){
  //returns 1 if collission occurs
  if((bY+ball.height)>=(cvs.height-ball.height+5) && (bX>=(pikaX-ball.height+5)) && (bX<=pikaX+pika.height-15))
  return 1;
  else {
    return 0;
  }
}

function nextLvl(){
  score++;
  bX=int bX=(rand() % (3 - (cvs.width-ball.height) + 1) + 5);
  bY=0;
  gravity+=5;
}

void playGame2(){
  int gravity = 1.5;
  int bY=0;
  int bX=(rand() % (3 - (cvs.width-ball.height) + 1) + 5);
  int pikaX=120;
  int pikaY=150;
  int counter=100;
  int score=0;
  int ball.height=30;
  int pika.height=60;
  GLCD_Clear  (Black);
  GLCD_DisplayString(0, 0, 1, "Les Games N.2 ");
  while(get_button() !=  KBD_DOWN){
      // redraw background, pika and the ball

          GLCD_Clear  (Black);
          GLCD_Bitmap (  pikaX,   pikaY, 60,  60, smD); //x then y
          GLCD_Bitmap (  bX,   bY, 30,  30, pball); //x then y
          delay(300000);
          GLCD_DisplayString(0, 0, 1, "SCORE: ", score);//

            if(checkCol()==1){
              //SHOW YOU LOST
              GLCD_SetBackColor(White);
              GLCD_SetTextColor(Blue);
              GLCD_DisplayString(1, 0, 1, "CAUGHT!      ");
              GLCD_DisplayString(2, 0, 1, "-END OF GAME-      ");
              GLCD_DisplayString(3, 0, 1, "Final Score: ", score);
              delay(30000000);
              endFlag=100; //reset difficulty for future replay
              return;
            }else if((bY+ball.height)==cvs.height){
              nextLvl();
            }
            if((get_button() ==  KBD_RIGHT) && pikaX!=230){
              pikaX+=5;
            }else if((get_button() ==  KBD_LEFT) && pikaX!=0){
            pikaX-=5;
            }
            bY += gravity;
      }
		GLCD_Clear  (White); //down pressed
    //return;
}
////////////////END OF GAME 2

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
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
	}
	if (selector==1 && inc=='p'){
	selector=2;//aud
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, "~L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
}
	if (selector==2 && inc=='p'){
	selector=3;//game
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, "~Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
	}
	if (selector==3 && inc=='p'){
	selector=4;//game 2
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, "~Les Games N. 2        ");
	}
  if (selector==4 && inc=='p'){
	selector=4;//game
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, "~Les Games N. 2        ");
	}
	if (selector==0 && inc=='m'){
	selector=0;
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
	}
	if (selector==1 && inc=='m'){
	selector=1;
	GLCD_DisplayString(5, 0, 1, "~Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
	}
	if (selector==2 && inc=='m'){
	selector=1;
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, "~L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
	}
	if (selector==3 && inc=='m'){
	selector=2;
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, "~L'Audio               ");
	GLCD_DisplayString(7, 0, 1, " Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
	}
  if (selector==4 && inc=='m'){
	selector=3;
	GLCD_DisplayString(5, 0, 1, " Galerie des Memes     ");
  GLCD_DisplayString(6, 0, 1, " L'Audio               ");
	GLCD_DisplayString(7, 0, 1, "~Les Games N. 1        ");
	GLCD_DisplayString(8, 0, 1, " Les Games N. 2        ");
	}

	}



/////////////////////START AUDIO FUNCTIONS
#if USB_DMA
uint32_t *InfoBuf = (uint32_t *)(DMA_BUF_ADR);
short *DataBuf = (short *)(DMA_BUF_ADR + 4*P_C);
#else
uint32_t InfoBuf[P_C];
short DataBuf[B_S];                         /* Data Buffer */
#endif

uint16_t  DataOut;                              /* Data Out Index */
uint16_t  DataIn;                               /* Data In Index */

uint8_t   DataRun;                              /* Data Stream Run State */
uint16_t  PotVal;                               /* Potenciometer Value */
uint32_t  VUM;                                  /* VU Meter */
uint32_t  Tick;                                 /* Time Tick */


/*
 * Get Potenciometer Value
 */

void get_potval (void) {
  uint32_t val;

  LPC_ADC->CR |= 0x01000000;              /* Start A/D Conversion */
  do {
    val = LPC_ADC->GDR;                   /* Read A/D Data Register */
  } while ((val & 0x80000000) == 0);      /* Wait for end of A/D Conversion */
  LPC_ADC->CR &= ~0x01000000;             /* Stop A/D Conversion */
  PotVal = ((val >> 8) & 0xF8) +          /* Extract Potenciometer Value */
           ((val >> 7) & 0x08);
}


/*
 * Timer Counter 0 Interrupt Service Routine
 *   executed each 31.25us (32kHz frequency)
 */

void TIMER0_IRQHandler(void)
{
  long  val;
  uint32_t cnt;

  if (DataRun) {                            /* Data Stream is running */
    val = DataBuf[DataOut];                 /* Get Audio Sample */
    cnt = (DataIn - DataOut) & (B_S - 1);   /* Buffer Data Count */
    if (cnt == (B_S - P_C*P_S)) {           /* Too much Data in Buffer */
      DataOut++;                            /* Skip one Sample */
    }
    if (cnt > (P_C*P_S)) {                  /* Still enough Data in Buffer */
      DataOut++;                            /* Update Data Out Index */
    }
    DataOut &= B_S - 1;                     /* Adjust Buffer Out Index */
    if (val < 0) VUM -= val;                /* Accumulate Neg Value */
    else         VUM += val;                /* Accumulate Pos Value */
    val  *= Volume;                         /* Apply Volume Level */
    val >>= 16;                             /* Adjust Value */
    val  += 0x8000;                         /* Add Bias */
    val  &= 0xFFFF;                         /* Mask Value */
  } else {
    val = 0x8000;                           /* DAC Middle Point */
  }

  if (Mute) {
    val = 0x8000;                           /* DAC Middle Point */
  }

  LPC_DAC->CR = val & 0xFFC0;             /* Set Speaker Output */

  if ((Tick++ & 0x03FF) == 0) {             /* On every 1024th Tick */
    get_potval();                           /* Get Potenciometer Value */
    if (VolCur == 0x8000) {                 /* Check for Minimum Level */
      Volume = 0;                           /* No Sound */
    } else {
      Volume = VolCur * PotVal;             /* Chained Volume Level */
    }
    val = VUM >> 20;                        /* Scale Accumulated Value */
    VUM = 0;                                /* Clear VUM */
    if (val > 7) val = 7;                   /* Limit Value */
  }

  LPC_TIM0->IR = 1;                         /* Clear Interrupt Flag */
}

int mainAudio (void)
{
  volatile uint32_t pclkdiv, pclk;

  /* SystemClockUpdate() updates the SystemFrequency variable */
  SystemClockUpdate();

  LPC_PINCON->PINSEL1 &=~((0x03<<18)|(0x03<<20));
  /* P0.25, A0.0, function 01, P0.26 AOUT, function 10 */
  LPC_PINCON->PINSEL1 |= ((0x01<<18)|(0x02<<20));

  /* Enable CLOCK into ADC controller */
  LPC_SC->PCONP |= (1 << 12);

  LPC_ADC->CR = 0x00200E04;		/* ADC: 10-bit AIN2 @ 4MHz */
  LPC_DAC->CR = 0x00008000;		/* DAC Output set to Middle Point */

  /* By default, the PCLKSELx value is zero, thus, the PCLK for
  all the peripherals is 1/4 of the SystemFrequency. */
  /* Bit 2~3 is for TIMER0 */
  pclkdiv = (LPC_SC->PCLKSEL0 >> 2) & 0x03;
  switch ( pclkdiv )
  {
	case 0x00:
	default:
	  pclk = SystemFrequency/4;
	break;
	case 0x01:
	  pclk = SystemFrequency;
	break;
	case 0x02:
	  pclk = SystemFrequency/2;
	break;
	case 0x03:
	  pclk = SystemFrequency/8;
	break;
  }

  LPC_TIM0->MR0 = pclk/DATA_FREQ - 1;	/* TC0 Match Value 0 */
  LPC_TIM0->MCR = 3;					/* TCO Interrupt and Reset on MR0 */
  LPC_TIM0->TCR = 1;					/* TC0 Enable */
  NVIC_EnableIRQ(TIMER0_IRQn);

  USB_Init();				/* USB Initialization */
  USB_Connect(TRUE);		/* USB Connect */

  /********* The main Function is an endless loop ***********/
  while( 1 );
}

/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void) {                     /* Main Program                       */

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
					LED_Off(5);
					LED_Off(0);
					LED_Off(1);
					LED_Off(2);
					LED_Off(3);
					GLCD_Clear  (White);
					GLCD_SetBackColor(White);
					GLCD_SetTextColor(Blue);
				GLCD_DisplayString(1, 0, 1, "     Les Games 1 ");
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
        case 4:
  				if (get_button() ==  KBD_SELECT){
  					LED_On(5);
  					LED_Off(4);
  					LED_Off(0);
  					LED_Off(1);
  					LED_Off(2);
  					LED_Off(3);
  					GLCD_Clear  (White);
  					GLCD_SetBackColor(White);
  					GLCD_SetTextColor(Blue);
  				GLCD_DisplayString(1, 0, 1, "     Les Games 2  ");
  				GLCD_DisplayString(3, 0, 1, "> Avoid the pokeball");
  				GLCD_DisplayString(5, 0, 1, "> Response has");
  				GLCD_DisplayString(6, 0, 1, "to be faster ");
  				GLCD_DisplayString(7, 0, 1, "each round.");
  					delay(30000000);//exactly 1s
  				GLCD_DisplayString(8, 0, 1, "   -----3-----    ");
  					delay(30000000);//exactly 1s
  				GLCD_DisplayString(8, 0, 1, "    ----2----  ");
  					delay(30000000);//exactly 1s
  				GLCD_DisplayString(8, 0, 1, "      --1--  ");
  				playGame2();
  				GLCD_Clear  (White);
  				}
  				break;
		}
	}
		}





}

/******************************************************************************
**                            End Of File
******************************************************************************/
