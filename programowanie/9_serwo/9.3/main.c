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

enum ServoState {CALLIB, IDLE, IN_PROGRESS};
struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
}; struct Servo sServo;

void ServoCallib(void)
{
	sServo.eState = CALLIB;
	while(eReadDetector()==INACTIVE){};
}

void ServoGoTo(unsigned int uiPosition)
{
	sServo.eState = IN_PROGRESS;
	sServo.uiDesiredPosition = uiPosition;
}



void Automat (void)
{
	switch(sServo.eState)
			{
				case CALLIB:
					if(eReadDetector()==INACTIVE)
						{
							LedStepRight();
						}
					else
						{
							sServo.eState = IDLE;
							sServo.uiCurrentPosition = 0;
							sServo.uiDesiredPosition = 0;
						}
					  break;		
				case IDLE:
					if(sServo.uiCurrentPosition != sServo.uiDesiredPosition)
						{
				      sServo.eState = IN_PROGRESS;
			      }
					else
						{
							sServo.eState = IDLE;
						}
						break;	
				case IN_PROGRESS:
					if(sServo.uiCurrentPosition > sServo.uiDesiredPosition)
						{
							LedStepLeft();
							sServo.uiCurrentPosition--;
							sServo.eState = IN_PROGRESS;
						}
					else if(sServo.uiCurrentPosition < sServo.uiDesiredPosition)
						{
							sServo.eState = IN_PROGRESS;
							sServo.uiCurrentPosition++;
							LedStepRight();
						}
					else
						{
							sServo.eState = IDLE;
						}
						break;
			}
}	

void ServoInit(unsigned int uiServoFrequency)
{
	Timer0Interrupts_Init(1000000/uiServoFrequency, &Automat);
	LedInit();
	DetectorInit();
	ServoCallib();
}





int main ()
{
	ServoInit(50);
	KeyboardInit();
	while(1)
	{
	 	switch(eKeyboardRead())
		{
			case BUTTON_0:
				ServoCallib();
				break;			
			case BUTTON_1:
				ServoGoTo(12);
				break;
			case BUTTON_2:
				ServoGoTo(24);
				break;
			case BUTTON_3:
				ServoGoTo(36);
			break;
			case RELASED:
				break;
			default:{}
	 }
 }
}
