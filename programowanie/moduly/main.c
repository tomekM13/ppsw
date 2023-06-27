#include "led.h"
#include "keyboard.h"

void Delay(int iValueDelay){
    int iLoopCounter ;
    for(iLoopCounter = iValueDelay*1.1999E4 ; iLoopCounter > 0 ; iLoopCounter--) ;
}
	
int main(){
  KeyboardInit();
    LedInit();  
	
	while(1)
    {
		
			switch(eKeyboardRead()){
				case BUTTON_1:
					LedStepLeft();
				break;
				case BUTTON_2:
					LedStepRight();
				break;
				default: ;
			
    
			}
			Delay(100);
    }
}
