#include "led.h"

#include "keyboard.h"

void Delay(int iValueDelay){
    int iLoopCounter ;
    for(iLoopCounter = iValueDelay*1.1999E4 ; iLoopCounter > 0 ; iLoopCounter--) ;
}
	enum LedState{STEP_STOP, STEP_RIGHT};
	enum LedState eLedState = STEP_STOP;
int main(){
	unsigned char ucStepCounter = 0;
	
  KeyboardInit();
    LedInit();  
	
			while(1){
			switch(eLedState){
				/*case STEP_LEFT:
					LedStepLeft();
				eLedState = STEP_LEFT;
				ucStepCounter++;
				if(ucStepCounter == 3){
				eLedState = STEP_RIGHT;
					ucStepCounter = 0;
					}
				break;*/
				case STEP_STOP:
					if(eKeyboardRead() == BUTTON_0){
						eLedState = STEP_RIGHT;
					}
					break;
				case STEP_RIGHT:
					LedStepRight();
				eLedState = STEP_RIGHT;
				ucStepCounter++;
				if(ucStepCounter == 3){
				eLedState = STEP_STOP;
					ucStepCounter = 0;
				}
					break;
}
Delay(250);
}
}
