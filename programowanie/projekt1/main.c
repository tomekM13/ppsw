#include <LPC21xx.H>
#define LED0_bm 0x10000
#define LED3_bm 0x80000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define BUT0_bm 0x10
#define BUT1_bm 0x20
#define BUT2_bm 0x40
#define BUT3_bm 0x80



void LedInit(){
    IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm; // dir ma byc na 1 
    IO1SET = (LED0_bm);
}
void KeyboardInit(){
	IO0DIR = IO0DIR &(~(BUT0_bm | BUT1_bm | BUT2_bm | BUT3_bm)); // dir ma byc na 0 
}
 
void LedOn(unsigned char ucLedIndeks){
            IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm ;  // gasi wszystkie diody 
        switch(ucLedIndeks){
			  case 0: 
					
            IO1SET = LED0_bm;
						break;
        case 1:
					
            IO1SET = LED1_bm;
            break;  
        case 2: 
						IO1SET = LED2_bm;
						break;
        case 3:
					
            IO1SET = LED3_bm;
						break;
				 default:
						break;
			}
            }

void Delay(int iValueDelay){
    int iLoopCounter ;
    for(iLoopCounter = iValueDelay*1.1999E4 ; iLoopCounter > 0 ; iLoopCounter--) ;
}
enum eButtonState{RELASED, BUTTON_0, BUTTON_1 ,BUTTON_2, BUTTON_3};

enum eButtonState eKeyboardRead(){
    if((~IO0PIN & BUT0_bm) == BUT0_bm){ //0x00000000 & 0x00000010 == 0x00000010
        return BUTTON_0;
    }else if((~IO0PIN & BUT1_bm) == BUT1_bm){ 
			return BUTTON_1;
		}else if((~IO0PIN & BUT2_bm) == BUT2_bm){
			return BUTTON_2;
		}else if((~IO0PIN & BUT3_bm) == BUT3_bm){
			return BUTTON_3;
		}else{
    return RELASED;
}
}

enum eStepDirection{LEFT,RIGHT};

void LedStep(enum eStepDirection StepDirection){
	static unsigned int siLedPosition; //zapamietuje jaka mial przypisana wartosc lokalnie  
	unsigned int uiSetDirection = StepDirection;
	
	if(uiSetDirection == RIGHT){
			siLedPosition--;
		}
		else if(uiSetDirection == LEFT){
			siLedPosition++;
		} 
		LedOn(siLedPosition % 4);
	}
void LedStepLeft(void){
	LedStep(LEFT);
}

void LedStepRight(void){
	LedStep(RIGHT);
}
	
int main(){
  KeyboardInit();
    LedInit();  
	
	while(1)
    {
		//Delay(100);
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
