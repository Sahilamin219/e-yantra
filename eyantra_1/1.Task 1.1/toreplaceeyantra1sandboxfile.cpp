//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions

#include "CB_Task_1_Sandbox.h"

/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node)
	
{	//intialising values for updating sensor values
	unsigned char left_sensor=1, centre_sensor=1, right_sensor=1;
	//varibles to store values of sensores
	while (node>0) {
        node--;
		left_sensor = ADC_Conversion(1);
		centre_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		//re-assigning values for updating sensor values
		_delay_ms(20);
		printf("\n%d %d %d", left_sensor, centre_sensor, right_sensor);
		_delay_ms(20);
		//case 1
		//bot will move forward if left and right track color is not black and centre is black
		if (left_sensor == 0 && centre_sensor != 0 && right_sensor == 0) {
			printf("TEST1!");
			velocity(250, 250);
			forward();
		}
		//case 2
		//conditions specified for moving right
		if (left_sensor == 0 && centre_sensor == 0 && right_sensor != 0) {
			printf("TEST2!");
			right_turn_wls();
		}
		//case 3
		//conditions specified for moving left
		if (left_sensor != 0 && centre_sensor == 0 && right_sensor ==0) {
			printf("TEST3!");
			left_turn_wls();
		}
		//case 4
		if (left_sensor == 0 && centre_sensor != 0 && right_sensor != 0) {
			stop();
			printf("TEST4!");
	         	soft_right();
		}
		//case 5
		if (left_sensor != 0 && centre_sensor != 0 && right_sensor == 0) {
			stop();
			printf("TEST5!");
			//velocity(220, 250);
			soft_left();
			_delay_ms(25);
		}
		//case 7
		if (left_sensor == 0 && centre_sensor == 0 && right_sensor == 0) {
			stop();
			printf("yes");
			right_turn_wls();
			_delay_ms(5);
			forward();
			_delay_ms(1);
			right_turn_wls();
			_delay_ms(10);
			printf("test7!");
		}
		stop();
		_delay_ms(1);
	}
	if (node < 0) {
		printf("reached destination !");
		stop();
		exit;
	}
}
/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{
	//stop();
	left();
	//soft_left();
	//velocity(200, 250);
	//_delay_ms(250);
	//forward();
}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{	
	//stop();
	right();
	//soft_right();
	//velocity(250, 200);
	//_delay_ms(250);
	//forward();
}

/*
*
* Function Name: e_shape
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a e shape path on the arena
* Example Call: e_shape();
*/
void e_shape(void)
{
	forward_wls(6);
}
void task1.1(void){
    //write your task1.1 logic here
    node--;
		left_sensor = ADC_Conversion(1);
		centre_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		//re-assigning values for updating sensor values
		_delay_ms(20);
		printf("\n%d %d %d", left_sensor, centre_sensor, right_sensor);
		_delay_ms(20);
		//case 1
		//bot will move forward if left and right track color is not black and centre is black
		if (left_sensor == 0 && centre_sensor != 0 && right_sensor == 0) {
			printf("TEST1!");
			velocity(250, 250);
			forward();
		}
		//case 2
		//conditions specified for moving right
		if (left_sensor == 0 && centre_sensor == 0 && right_sensor != 0) {
			printf("TEST2!");
			right_turn_wls();
		}
		//case 3
		//conditions specified for moving left
		if (left_sensor != 0 && centre_sensor == 0 && right_sensor ==0) {
			printf("TEST3!");
			left_turn_wls();
		}
		//case 4
		if (left_sensor == 0 && centre_sensor != 0 && right_sensor != 0) {
			stop();
			printf("TEST4!");
	         	soft_right();
		}
		//case 5
		if (left_sensor != 0 && centre_sensor != 0 && right_sensor == 0) {
			stop();
			printf("TEST5!");
			//velocity(220, 250);
			soft_left();
			_delay_ms(25);
		}
        //case 6
		//itrating over number of node given
		if (left_sensor != 0 && centre_sensor != 0 && right_sensor != 0) {
			printf("TEST6!");
			stop();
			node--;
			printf("%d", node);
			if (node == 15) {
				printf("runnn5!");
				right_turn_wls();
				_delay_ms(50);
			}
			if (node == 14 && node == 13 && node == 12 && node == 11) {
				printf("runing4!");
				forward();
				_delay_ms(150);
			}
			if (node == 10 && node == 9) {
				printf("runing3!");
				left_turn_wls();
				_delay_ms(50);
			}
			if (node == 8 && node == 6 && node == 4 && node == 2) {
				printf("runing2!");
				right_turn_wls();
				_delay_ms(50);
			}
			if (node == 7 && node == 5 && node == 3 && node == 1) {
				printf("runing1!");
				left_turn_wls();
				_delay_ms(50);
			}
			forward();
			_delay_ms(150);
		}
		//case 7
		if (left_sensor == 0 && centre_sensor == 0 && right_sensor == 0) {
			stop();
			printf("yes");
			right_turn_wls();
			_delay_ms(5);
			forward();
			_delay_ms(1);
			right_turn_wls();
			_delay_ms(10);
			printf("test7!");
		}
		stop();
		_delay_ms(1);
}
/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{
	//write your task 1.2 logic here
}