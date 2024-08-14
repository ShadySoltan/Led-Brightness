#include "tm4c123gh6pm.h"

void delay(long d)
{
    while(d--);
}

PWM1_CH567_INIT(void)
{
    //Enable PWM1 module clock
    SYSCTL_RCGCPWM_R |= (1<<1);

    //Enable Clock for PORTF
    SYSCTL_RCGCGPIO_R |= (1<<5);
    while((SYSCTL_PRGPIO_R & 0x20) == 0);

    //Use SystemClock for PWM 16MHz
    SYSCTL_RCC_R &= ~(1<<20);

    //Configure Three Pins PF1, PF2, and PF3 as PWM pins
    GPIO_PORTF_AFSEL_R |= (1<<1) | (1<<2) | (1<<3);
    GPIO_PORTF_PCTL_R = 0x00005550;
    GPIO_PORTF_DEN_R |= (1<<1) | (1<<2) | (1<<3);

    //Configure PWM Module1 Generators 2 and 3
    //Disable the PWM channels 5 6 7 before configuration
    PWM1_3_CTL_R &= ~(1<<0);
    PWM1_2_CTL_R &= ~(1<<0);
    //Select DownCount mode
    PWM1_3_CTL_R &= ~(1<<1);
    PWM1_2_CTL_R &= ~(1<<1);
    //Configure the load value to be 1600 meaning that the frequency will be 10KHz
    PWM1_3_LOAD_R = 1600;
    PWM1_2_LOAD_R = 1600;
    //Set the DutyCycle
    PWM1_3_CMPA_R = 0;
    PWM1_2_CMPA_R = 0;

    //When the PWM timer starts counting from 1600 it drives the PF1 PF2 PF3 to high
    PWM1_3_GENA_R |= (1<<2) | (1<<3);
    PWM1_3_GENB_R |= (1<<2) | (1<<3);
    PWM1_2_GENB_R |= (1<<2) | (1<<3);

    //When the counter reaches the compartorA it will drive the pins to low
    PWM1_3_GENA_R &= ~(1<<6);
    PWM1_3_GENA_R |= (1<<7);
    PWM1_3_GENB_R &= ~(1<<6);
    PWM1_3_GENB_R |= (1<<7);
    PWM1_2_GENB_R &= ~(1<<6);
    PWM1_2_GENB_R |= (1<<7);

    //Enable the two generators
    PWM1_2_CTL_R |= (1<<0);
    PWM1_3_CTL_R |= (1<<0);
}

void PWM_CH5_ON(void)
{
    PWM1_ENABLE_R |= (1<<5);
}

void PWM_CH5_OFF(void)
{
    PWM1_ENABLE_R &= ~(1<<5);
}


void PWM_CH6_ON(void)
{
    PWM1_ENABLE_R |= (1<<6);
}

void PWM_CH6_OFF(void)
{
    PWM1_ENABLE_R &= ~(1<<6);
}


void PWM_CH7_ON(void)
{
    PWM1_ENABLE_R |= (1<<7);
}

void PWM_CH7_OFF(void)
{
    PWM1_ENABLE_R &= ~(1<<7);
}

uint16 i;

void Run_Red(void)
{
    PWM_CH5_ON();
    for(i = 1600; i > 0; i--)
    {
        PWM1_2_CMPA_R = i;
        delay(1000);
    }


    delay(10000);
    for(i = 0; i < 1600; i++)
    {
        PWM1_2_CMPA_R = i;
        delay(1000);
    }
    PWM_CH5_OFF();
}

void Run_Green(void)
{
    PWM_CH7_ON();
    for(i = 1600; i > 0; i--)
    {
        PWM1_3_CMPA_R = i;
        delay(1000);
    }


    delay(10000);
    for(i = 0; i < 1600; i++)
    {
        PWM1_3_CMPA_R = i;
        delay(1000);
    }
    PWM_CH7_OFF();
}

void Run_Blue(void)
{
    PWM_CH6_ON();
    for(i = 1600; i > 0; i--)
    {
        PWM1_3_CMPA_R = i;
        delay(1000);
    }


    delay(10000);
    for(i = 0; i < 1600; i++)
    {
        PWM1_3_CMPA_R = i;
        delay(1000);
    }
    PWM_CH6_OFF();
}

void Run_MIX1(void)
{
    PWM_CH5_ON();
    PWM_CH6_ON();
    for(i = 1600; i > 0; i--)
    {
        PWM1_2_CMPA_R = i;
        PWM1_3_CMPA_R = i;
        delay(1000);
    }


    delay(10000);
    for(i = 0; i < 1600; i++)
    {
        PWM1_2_CMPA_R = i;
        PWM1_3_CMPA_R = i;
        delay(1000);
    }
    PWM_CH5_OFF();
    PWM_CH6_OFF();
}

void Run_MIX2(void)
{
    PWM_CH5_ON();
    PWM_CH7_ON();
    for(i = 1600; i > 0; i--)
    {
        PWM1_2_CMPA_R = i;
        PWM1_3_CMPA_R = i;
        delay(1000);
    }


    delay(10000);
    for(i = 0; i < 1600; i++)
    {
        PWM1_2_CMPA_R = i;
        PWM1_3_CMPA_R = i;
        delay(1000);
    }
    PWM_CH5_OFF();
    PWM_CH7_OFF();
}

void Run_MIX3(void)
{
    PWM_CH6_ON();
    PWM_CH7_ON();
    for(i = 1600; i > 0; i--)
    {
        PWM1_3_CMPA_R = i;
        delay(1000);
    }


    delay(10000);
    for(i = 0; i < 1600; i++)
    {
        PWM1_3_CMPA_R = i;
        delay(1000);
    }
    PWM_CH6_OFF();
    PWM_CH7_OFF();
}

void Run_MIX4(void)
{
    PWM_CH5_ON();
    PWM_CH6_ON();
    PWM_CH7_ON();
    for(i = 1600; i > 0; i--)
    {
        PWM1_2_CMPA_R = i;
        PWM1_3_CMPA_R = i;
        delay(1000);
    }


    delay(10000);
    for(i = 0; i < 1600; i++)
    {
        PWM1_2_CMPA_R = i;
        PWM1_3_CMPA_R = i;
        delay(1000);
    }
    PWM_CH5_OFF();
    PWM_CH6_OFF();
    PWM_CH7_OFF();
}

int main()
{
    PWM1_CH567_INIT();
    while(1)
    {
        Run_Red();
        Run_Blue();
        Run_Green();
        Run_MIX1();
        Run_MIX2();
        Run_MIX3();
        Run_MIX4();
    }
}

