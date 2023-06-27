#include "led.h"

#include "keyboard.h"

void Delay(int iValueDelay){
    int iLoopCounter ;
    for(iLoopCounter = iValueDelay*1.1999E4 ; iLoopCounter > 0 ; iLoopCounter--) ;
}
	enum LedState{STEP_STOP, STEP_RIGHT, STEP_LEFT};
	enum LedState eLedState = STEP_STOP;
int main(){
	
	
  KeyboardInit();
    LedInit();  
	
			while(1){
			switch(eLedState){
				case STEP_LEFT:
					if(eKeyboardRead() == BUTTON_1){
						eLedState = STEP_STOP;
					} 
					else
					{
					LedStepLeft();
				eLedState = STEP_LEFT;
					}
				
				break;
				case STEP_STOP:
					if(eKeyboardRead() == BUTTON_2){
						eLedState = STEP_RIGHT;
					}
					if(eKeyboardRead() == BUTTON_0){
						eLedState = STEP_LEFT;
					}
					break;
				case STEP_RIGHT:
					if(eKeyboardRead() == BUTTON_1){
						eLedState = STEP_STOP;
					} 
					else
					{
					LedStepRight();
				eLedState = STEP_RIGHT;
					}
					break;
}
Delay(100);
}
}
