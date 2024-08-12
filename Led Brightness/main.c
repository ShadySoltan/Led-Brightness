#include "tm4c123gh6pm.h"

//Configure PWM module 1 channel 6 for the blue led pin PF2
void PWM1_CH6_PF2(void)
{
    //Enable PWm1 module clock
    SYSCTL_RCGCPWM_R |= (1<<1);

    //Enable Clock for PORTF
    SYSCTL_RCGCGPIO_R |= (1<<5);
    while((SYSCTL_PRGPIO_R & 0x20) == 0);

    //Use SystemClock for PWM 16MHz
    SYSCTL_RCC_R &= ~(1<<20);

    //Select Alternate function for PF2
    GPIO_PORTF_AFSEL_R |= (1<<2);

    //Select PWM mode for PF2
    GPIO_PORTF_PCTL_R = 0x00000500;

    //Enable the pin
    GPIO_PORTF_DEN_R |= (1<<2);

    //Disable the PWM channel 6 before configuration
    PWM1_3_CTL_R &= ~(1<<0);

    //Select DownCount mode
    PWM1_3_CTL_R &= ~(1<<1);

    //Configure the load value to be 1600 meaning that the frequency will be 10KHz
    PWM1_3_LOAD_R = 1600;

    //Set the DutyCycle
    PWM1_3_CMPA_R = 0;

    //When the PWM timer starts counting from 1600 it drives the PF2 to high
    PWM1_3_GENA_R |= (1<<2) | (1<<3);

    //When the counter reaches the compartorA it will drive the pin to low
    PWM1_3_GENA_R &= ~(1<<6);
    PWM1_3_GENA_R |= (1<<7); //Writing the value of 0x2 to bits 6 and 7

    //Enable the PWM block 3
    PWM1_3_CTL_R |= (1<<0);

    //Enable PWM channel 6 output
    PWM1_ENABLE_R |= (1<<6);
}

void delay(long d)
{
    while(d--);
}


void APP1(void) //Turning the blue led off and on in a smooth way by varying brightness
{
    uint16 i;
    PWM1_CH6_PF2();
    while (1)
    {
        for(i = 0; i < 1600; i++)
        {
            PWM1_3_CMPA_R = i;
            delay(1000);
        }

        delay(1000000);

        for(i = 1600; i > 0; i--)
        {
            PWM1_3_CMPA_R = i;
            delay(1000);
        }

        delay(1000000);
    }
}


void main(void)
{
    APP1();
}
