#include "led.h"
#include "timer_interrupts.h"
#include "keyboard.h"

void Automat (void)
{
	enum LedState{STEP_STOP, STEP_RIGHT, STEP_LEFT,};
	enum LedState eLedState = STEP_STOP;
	
	LedInit();
	KeyboardInit();

	while(1)
		{
			switch(eLedState)
			{
				case STEP_STOP:
					if(eKeyboardRead() == BUTTON_2)
						{
							eLedState = STEP_RIGHT;
						}
					else if(eKeyboardRead() == BUTTON_0)
						{
							eLedState = STEP_LEFT;
						}
					else
						{
							eLedState = STEP_STOP;
						}
					break;
				case STEP_LEFT:
					if(eKeyboardRead() == BUTTON_1)
						{
							eLedState = STEP_STOP;
						} 
					else
						{
							LedStepLeft();
							eLedState = STEP_LEFT;
						}
					break;
				case STEP_RIGHT:
					if(eKeyboardRead() == BUTTON_1)
						{
							eLedState = STEP_STOP;
						} 
					else
						{
							LedStepRight();
							eLedState = STEP_RIGHT;
						}
					break;
			}
		}	
}




int main ()
{
	unsigned int iMainLoopCtr;
 	Timer0Interrupts_Init(20, &Automat);
	LedInit();
	KeyboardInit();

	while(1)
	{
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}
}
