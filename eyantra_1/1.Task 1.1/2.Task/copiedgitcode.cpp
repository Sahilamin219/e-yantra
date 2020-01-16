#include <intrins.h>
#include "p89v51rx2.H"
#include "lcd_array_disp.h"

//direction control bits

sbit LB=P1^0;  //LEFT BACK Pin
sbit LF=P1^1;  //LEFT FRONT Pin
sbit RF=P1^2;  //RIGHT FRONT Pin
sbit RB=P3^4;  //RIGHT BACK Pin

sbit buzzer=P2^7; //buzzer = 1; buzzer off, buzzer = 0; buzzer on,

sbit start_conv = P3^6;		 //P3^6 is connected to Start and ALE pin of ADC0808
sbit output_enable = P3^7;		 //P3^7 is connected to Output Enable Pin of ADC0808

unsigned char data_array[8];//initialize an array of 8 elements to display onto the LCD screen
unsigned char i=0;  //used in main function during ADC conversion 
unsigned char left_whiteline = 0;
unsigned char center_whiteline = 0;
unsigned char right_whiteline = 0;
unsigned char flag = 0; //used in white line following logic

/********************************************************************************
	Function: ADC_conversion(unsigned char ADC_channel_number)

	Description: This function performs ADC conversion of a channel number 
				 that is passed to it. The return value of this function contains 
 				 digital data of the selected channel.
		   
				 Analog Sensor Pin Mapping
  
            	 IN0-----> IR Proximity sensor 3 (left side)
				 IN1-----> Batt. Voltage
				 IN2-----> Front Sharp IR Range sensor
				 IN3-----> IR Proximity sensor 2 (center)
				 IN4-----> Left Whiteline
		 		 IN5-----> Center Whiteline
				 IN6-----> Right Whiteline
				 IN7-----> IR Proximity sensor 4 (right side)
********************************************************************************/
unsigned char ADC_conversion(unsigned char ADC_ch_no)
{
unsigned char ADC_data;

P0 = ADC_ch_no;		  // to select channel no. send address on P0

start_conv = 1; // ADC0808 will latch the address on L-H transition on the ALE pin
start_conv = 0;	// ADC0808 will start conversion on H-L transition on the start pin
delay_ms(2);	// conversion time for ADC0808

P0 =0xFF;	        // output enable and read
output_enable = 1;	//Enabling o/p of ADC0808 for to read the converted data
ADC_data = P0;		//storing adc_data
output_enable = 0;	//disabling ADC 0808 o/p
return ADC_data;	//returning adc_data
}

//Set left motor with velocity vel(compare value). 0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.
void left_motor_velocity(unsigned char vel)
{
CCAP0H=vel;
}

//Set right motor with velocity vel(compare value). 0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.
void right_motor_velocity(unsigned char vel)
{
CCAP1H=vel;
}

// motor direction control subroutines
void forward(void)
{
RF=1;
LF=1;
RB=0;
LB=0;
}

void stop(void)
{
RF=0;
LF=0;
RB=0;
LB=0;
}

//initialise programmable counter array module to generate pwm
//The CCAPnH register holds the reload value. CCAPnL register increments,and is loaded with this value everytime it overflows
//Thus the value in CCAPnH can be changed to change the motor velocity
void pca_init(void)
{
 CMOD=0x80;	   //80 sets PCA counter to run at Fosc/6; 
 CCON=0x40;	   //start PCA counter
 						
 CCAP0L=0x00;   
 CCAP0H=0xFF;  //Left motor duty cycle register
  
 CCAP1L=0x00;				  
 CCAP1H=0xFF;  //Right motor duty cycle register

 CCAPM0=0x42;  //enable PWM mode and ECOM bits for left motor
 CCAPM1=0x42;  //enable PWM mode and ECOM bits for right motor
}


void main()
{
 unsigned char i=0;
 output_enable = 0;
 start_conv = 0;    //de-assert all control signals to ADC
 
 buzzer = 1; //buzzer off
 lcd_init(); //Initialize LCD
 pca_init(); //Initialize PCA to genarate PWM

forward();
left_motor_velocity(0x4F);  //0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.			
right_motor_velocity(0x4F); //0x00 will give full (100% duty cycle) velocity, while 0xFF will give zero (0% duty cycle) velocity. Any value in between 0x00 and 0xFF will give intermediate velocity.


 while(1)
 {
  for(i=0;i<8;i++)	 //Doing ADC conversion
  {
  data_array[i] = ADC_conversion(i);
  }

  left_whiteline = data_array[4];   
  center_whiteline = data_array[5];
  right_whiteline = data_array[6];

  flag = 0; //reset the flag to 0

  //check if robot's center white line sensor is on the white line
  if(center_whiteline < 25)
  {
   flag = 1;  //set the flag to 0 so that further white line sensor comparision is disabled
   left_motor_velocity(0x4F);   //left and right motor is at same velocity
   right_motor_velocity(0x4F);
  }

  //robot is drifting towards left side, increase velocity of the left wheel and decrease velocity of the right wheel
  if ((left_whiteline > 25) && (flag == 0))
  {
   flag = 1;  //set the flag to 0 so that further white line sensor comparision is disabled
   left_motor_velocity(0x3F);	//increase left motor velocity 
   right_motor_velocity(0x5F);  //decrease  right motor velocity
  }

  //robot is drifting towards right side, decrease velocity of the left wheel and increase velocity of the right wheel
  if ((right_whiteline > 25) && (flag == 0))
  {
   flag = 1;  //set the flag to 0 so that further white line sensor comparision is disabled
   left_motor_velocity(0x5F);	//decrease  left motor velocity
   right_motor_velocity(0x3F);	//increase right motor velocity
  }

  if((left_whiteline > 25) && (center_whiteline > 25) && (right_whiteline > 25)) // no whiteline is detected, stop
  {
   stop();
  }
  else
  {
   forward();
  }
  
  lcdprint(data_array);//call this function to print the array onto the screen
  delay_ms(250);
 }
}