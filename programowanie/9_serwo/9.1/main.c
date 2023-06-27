#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"
#include <LPC21xx.H>

#define DETECTOR_bm (1<<10)

void DetectorInit (void)
{
	IO0DIR = IO0DIR & (~DETECTOR_bm);
}

enum DetectorState {ACTIVE, INACTIVE};
enum DetectorState eReadDetector(void)
{
	if ((IO0PIN & DETECTOR_bm) == 0)
	 {
		 return ACTIVE;
	 }
	else
	 {
	 	 return INACTIVE;
	 }
}

void Automat (void)
{
	enum LedState{STEP_LEFT,STEP_RIGHT,STAY,Callib};
	static enum LedState eLedState = Callib;
	
	
	switch(eLedState)
			{
				case Callib:
					if (eReadDetector()==INACTIVE)
					  {
						  LedStepRight();
							
					  }
					else
						{
							eLedState = STAY;
						}
					  break;		
				case STAY:
					if (eKeyboardRead() == BUTTON_0)
						{
							eLedState = STEP_LEFT;
						}
					else if (eKeyboardRead() == BUTTON_2)
						{
							eLedState = STEP_RIGHT;
						}
					else 
						eLedState = STAY;
						break;	
				case STEP_RIGHT:
					if(eKeyboardRead() == BUTTON_1)
						{
							eLedState = STAY;
						}
					else
						eLedState = STEP_RIGHT;	
						LedStepRight();
						break;
				case STEP_LEFT:
					if(eKeyboardRead() == BUTTON_1)
						{
							eLedState = STAY;
						}
					else
						eLedState = STEP_LEFT;
						LedStepLeft();
						break;
			}
}		





int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(100000, &Automat);
	LedInit();
	KeyboardInit();
	DetectorInit();
	while(1)
	{
	 	iMainLoopCtr++;
	}
}
