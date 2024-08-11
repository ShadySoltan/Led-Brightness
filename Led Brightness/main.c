#include "tm4c123gh6pm.h"

void PORTF_Init()
{
    // Turn on Clock
    SYSCTL_RCGCGPIO_R = 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
}

void PORTF_LEDs_Init(void) //Initialize lEDs as GPIO
{
    // Configure the Board LEDs
    PORTF_Init();
    // Turn off Alternate Function
    GPIO_PORTF_AFSEL_R &= 0xF1;
    // Turn off Analog Mode
    GPIO_PORTF_AMSEL_R &= 0xF1;
    // Configure all three pins as output
    GPIO_PORTF_DIR_R |= 0x0E;
    // Choose GPIO mode for the three pins
    GPIO_PORTF_PCTL_R &= 0xFFFF000F;
    // Enable pins
    GPIO_PORTF_DEN_R |= 0x0E;
    // Turn off pins
    GPIO_PORTF_DATA_R &= 0xF1;
}

int main(void)
{
    PORTF_LEDs_Init();
	while(1)
	{
	    GPIO_PORTF_DATA_R |= 0xF8;
	}
}
