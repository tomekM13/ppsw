#include <LPC21xx.H>
#include "timer.h"

#define CounterEnable (1<<0)
#define CounterReset (1<<1)
#define ResetMR0 (1<<1)
#define InterruptMR0 (1<<0)
#define InterruptFlagMR0 (1<<0)

void InitTimer0 (void)
{
	T0TCR = T0TCR | CounterEnable;
}

void WaitOnTimer0 (unsigned int uiTime)
{
	T0TCR = T0TCR | CounterReset;
	T0TCR = T0TCR & ~CounterReset;
	while ((uiTime*15)>= T0TC){}
	
}

void InitTimer0Match0(unsigned int uiDelayTime)
{
	T0TCR = T0TCR | CounterEnable;
	T0TCR = T0TCR | CounterReset;
	T0TCR = T0TCR & ~CounterReset;
	T0MR0 = uiDelayTime*15;
	T0MCR = T0MCR | ResetMR0 | InterruptMR0;
}

void WaitOnTimer0Match0(void)
{
	while ((T0IR & InterruptFlagMR0)==0){}				
	T0IR=InterruptFlagMR0;
}
