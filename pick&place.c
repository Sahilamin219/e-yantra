#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#define F_CPU 14745600
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "magic.h"
#include "LCD.h"
#include "graph.h"


void servo1_pin_config (void){
	DDRB = DDRB | 0x20; //making PORTB 5 pin output
	PORTB = PORTB | 0x20; //setting PORTB 5 pin to logic 1
}
void servo2_pin_config (void)
{
	DDRB = DDRB | 0x40; //making PORTB 6 pin output
	PORTB = PORTB | 0x40; //setting PORTB 6 pin to logic 1
}
void timer1_init(void)
{
	TCCR1B = 0x00; //stop
	TCNT1H = 0xFC; //Counter high value to which OCR1xH value is to be compared with
	TCNT1L = 0x01; //Counter low value to which OCR1xH value is to be compared with
	OCR1AH = 0x03; //Output compare Register high value for servo 1
	OCR1AL = 0xFF; //Output Compare Register low Value For servo 1
	OCR1BH = 0x03; //Output compare Register high value for servo 2
	OCR1BL = 0xFF; //Output Compare Register low Value For servo 2
	ICR1H = 0x03;
	ICR1L = 0xFF;
	TCCR1A = 0xAB;
	//COM1A1=1, COM1A0=0; COM1B1=1, COM1B0=0; COM1C1=1 COM1C0=0
	//For Overriding normal port functionality to OCRnA outputs. WGM11=1, WGM10=1. Along With //WGM12 in TCCR1B for Selecting FAST PWM Mode
	TCCR1C = 0x00;
	TCCR1B = 0x0C; //WGM12=1; CS12=1, CS11=0, CS10=0 (Prescaler=256)
}
//Function to rotate Servo 1 by a specified angle in the multiples of 1.86 degrees
void servo_1(unsigned char degrees){
	float PositionPanServo = 0;
	PositionPanServo = ((float)degrees / 1.86) + 35.0;
	OCR1AH = 0x00;
	OCR1AL = (unsigned char) PositionPanServo;
}
void servo_2(unsigned char degrees){
	float PositionTiltServo = 0;
	PositionTiltServo = ((float)degrees / 1.86) + 35.0;
	OCR1BH = 0x00;
	OCR1BL = (unsigned char) PositionTiltServo;
}
void init_devices(void){
	cli();   //Clears the global interrupts
	_initLcd();
	_initMotor();
	_initAdc();
	servo1_pin_config();
	servo2_pin_config();
	timer1_init();
	left_encoder_pin_config();    //left encoder pin config
	right_encoder_pin_config();   //right encoder pin config
	timer5_init();
	left_position_encoder_interrupt_init();
	right_position_encoder_interrupt_init();
	sei();   //Enables the global interrupts
}

int bd=3;
void go_to(int source, int dest,Graph* graph) {
	int i;
	int tmp_forward;
	int dir;
	//bd: bot direction;
	bfs* path=shortestPath(source,dest,graph);
	bfs* next_node;
	//	next_node=path->next;
	//	printf("%d",next_node->node);
	while(path->next!=NULL) {
		forward_mm(120);
		_delay_ms(100);
		next_node=path->next;
		if ((next_node->node - path->node) > 1) { dir = 1; }
		else if ((next_node->node - path->node) < -1) { dir = 3; }
		else if ((next_node->node - path->node) == 1) { dir = 4; }
		else if ((next_node->node - path->node) == -1) { dir = 2; }
		if ((dir - bd) >= 1) {
			if (((dir - bd) == 1)) { right_degrees(90); tmp_forward = 0; }
			else if ((dir - bd) == 3) { left_degrees(90); tmp_forward = 0; }
			else if ((dir - bd) == 2) { left_degrees(180); tmp_forward = 0; }
			bd = dir;
		}
		else if ((dir - bd) == 0) {
		}
		else {
			if ((dir - bd) == -3) { right_degrees(90); tmp_forward = 0; }
			else if ((dir - bd) == -1) { left_degrees(90); tmp_forward = 0; }
			else if ((dir - bd) == -2) { left_degrees(180); tmp_forward = 0; }
			bd = dir;
		}
		//cout << "forward_oneNode()-> (" << bd << ") ";
		//printf("forward_oneNode()->");
		forward_wls(1);
		path=path->next;
	}
}
void pick(){
	//back_mm(90);
	
	servo_2(70);
	_delay_ms(1000);
	servo_1(197);
	_delay_ms(1000);
	servo_2(0);
/*
	_delay_ms(500);
	servo_1(90);
	_delay_ms(1000);
	forward_wls(1);*/
}
void place(){
	servo_1(50);
	_delay_ms(1500);
	servo_2(50);
	_delay_ms(500);
	servo_1(90);
}
int main(){
	init_devices();
	char msg1[16];
	servo_1(197);
	servo_2(80);
	_delay_ms(1000);
	servo_2(45);
	_delay_ms(1000);
	servo_1(15);
	_delay_ms(1500);
	servo_1(9);
	_delay_ms(1000);
	servo_2(80);
	_delay_ms(500);
	servo_1(0);
	_delay_ms(500);
	servo_2(45);
_delay_ms(500);
	servo_1(90);
	_delay_ms(1000);
forward_mm(200);
_delay_ms(500);
left_degrees(60);
servo_1(197);

_delay_ms(1500);
servo_2(80);
_delay_ms(500);
servo_1(182);
_delay_ms(400);
servo_2(45);
_delay_ms(400);
servo_1(175);
right_degrees(60);
servo_1(197);
_delay_ms(500);
servo_2(80);
_delay_ms(700);
servo_1(175);
left_degrees(60);
_delay_ms(700);
servo_1(197);
_delay_ms(700);
servo_2(45);
_delay_ms(700);
servo_1(90);
right_degrees(60);
servo_1(15);
_delay_ms(500);
servo_2(80);
	//servo_2(50);

	/*
		int V = 35;
		Graph* graph = createGraph(V);
		addEdge(graph, 1, 2);
		addEdge(graph, 2, 3);
		addEdge(graph, 3, 8);
		addEdge(graph, 8, 12);
		addEdge(graph, 12, 18);
		addEdge(graph, 18, 22);
		addEdge(graph, 22, 29);
		addEdge(graph, 29, 33);
		addEdge(graph, 33,32);
		//addEdge(graph, 32, 31);
		addEdge(graph, 31,25);
		addEdge(graph, 25, 21);
		addEdge(graph, 21, 15);
		addEdge(graph, 15, 11);
		addEdge(graph, 11, 5);
		addEdge(graph, 5, 1);
		addEdge(graph, 8, 9);
		addEdge(graph, 8, 7);
		addEdge(graph, 12, 13);
		addEdge(graph, 18, 19);
		addEdge(graph, 18, 17);
		addEdge(graph, 22, 23);
		addEdge(graph, 29, 28);
		addEdge(graph, 29, 30);
		addEdge(graph, 32, 27);
		addEdge(graph, 25, 24);
		addEdge(graph, 25, 26);
		addEdge(graph, 21, 20);
		addEdge(graph, 15, 14);
		addEdge(graph, 15, 16);
		addEdge(graph, 11, 10);
		addEdge(graph, 5, 6);
		addEdge(graph, 5, 4);
		//addEdge(graph, 12, 11);
		//addEdge(graph, 22, 21);
		float x=50;
		int ls,rs,cs;
		char msg1[16];
		int speed=150;
		_delay_ms(520);

	int max_speed=200;
	servo_1(90);
	forward_wls(1);
	go_to(2,18,graph);
	pick();
	go_to(18,11,graph);
	place();
	*/
	///////////
/*
	forward_wls(1);
	pick();
	forward_wls(2);
	place();
	//wall_forward();
	wall_forward();
*/


/*

	while(1){
		int max_speed=100;
		int ls=ADC_Conversion(4);
		int rs=ADC_Conversion(5);
		if(ls<rs){
			velocity((max_speed-ls/4),max_speed);
		}else{
			velocity(max_speed,(max_speed-rs/4));
		}
		forward();
	}*/
/*
	forward_wls(1);
	back_mm(90);
	pick();
	forward_wls(2);
	place();*/

/*
	servo_1(197);
	_delay_ms(1500);
	servo_2(0);
	servo_1(5);
	_delay_ms(2000);
	servo_2(50);
	*/

/*

	//echo("fwd",1,1);
	forward_wls(1);
	
	forward_mm(120);
	_delay_ms(100);
	//echo("lft",1,1);
	left_degrees(90);
	
	//echo("fwd",1,1);
	forward_wls(1);
	forward_mm(120);
	_delay_ms(100);
	//echo("lft",1,1);
	left_degrees(90);
	//echo("fwd",1,1);
	forward_wls(5);
	_delay_ms(100);
	//echo("180",1,1);
	left_degrees(185);
	
	forward_wls(5);
	forward_mm(120);
	_delay_ms(100);
	right_degrees(90);
	
	forward_wls(1);
	forward_mm(120);
	_delay_ms(100);
	right_degrees(90);
	
	*/


//70-90
//155-180
//250-270
	//left_degrees(180);
	//forward_mm(100);
	



	/*while(1){
		int ls=ADC_Conversion(3);
		int rs=ADC_Conversion(1);
		int cs=ADC_Conversion(2);
		sprintf(msg1,"%d  %d  %d",ls,cs,rs);
		echo(msg1,1,1);
		_delay_ms(400);
		echo("                ",1,1);
	}
	while(1){
		int ls=ADC_Conversion(3);
		int rs=ADC_Conversion(1);
		int cs=ADC_Conversion(2);
		if(ls>rs){
			velocity((speed/ls)*rs*(0.75),speed);
			}else{
			velocity(speed,(0.75)*(speed/rs)*ls);
		}
		forward();
	}*/

}
