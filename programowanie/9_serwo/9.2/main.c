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

void Automat (void)
{
	static enum ServoState eServoState = CALLIB;
	
	
	switch(eServoState)
			{
				case CALLIB:
					if(eReadDetector()==INACTIVE)
						{
							LedStepRight();
						}
					else
						{
							eServoState = IDLE;
							sServo.uiCurrentPosition = 0;
							sServo.uiDesiredPosition = 0;
						}
					  break;		
				case IDLE:
					if(sServo.uiCurrentPosition != sServo.uiDesiredPosition)
						{
				      eServoState = IN_PROGRESS;
			      }
					else
						{
							eServoState = IDLE;
						}
						break;	
				case IN_PROGRESS:
					if(sServo.uiCurrentPosition > sServo.uiDesiredPosition)
						{
							LedStepLeft();
							sServo.uiCurrentPosition--;
							eServoState = IN_PROGRESS;
						}
					else if(sServo.uiCurrentPosition < sServo.uiDesiredPosition)
						{
							eServoState = IN_PROGRESS;
							sServo.uiCurrentPosition++;
							LedStepRight();
						}
					else
						{
							eServoState = IDLE;
						}
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
