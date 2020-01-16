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
{	
	unsigned char ls = 1, cs = 1, rs = 1, fs = 1;	//intializing variables to get srnsor reading
	int flag = 0;	//a new variable to detect condition to call isBotOnNode variable
	int node_count = 0;	//variable to count number of nodes on the path provided
	int isBotOnNode = 0; // varible to detect is bot on linne or not 
	while (1) {
		//takinng input from sensors
		ls = ADC_Conversion(1);
		cs = ADC_Conversion(2);
		rs = ADC_Conversion(3);
		//condition to move forward
		if ((ls == 0 && rs == 0 && cs == 255)) {
			forward();
			if (flag == 1) { isBotOnNode = 0; }
		}
		//condition to move soft left slightly
		else if (ls == 255 && rs == 0 && cs == 255) {
			soft_left();
			printf("soft left1");
			if (flag == 1) { isBotOnNode = 0; }

		}
		//condition to move soft left .
		else if (ls == 255 && rs == 0 && cs == 0) {
			soft_left();
			if (flag == 1) { isBotOnNode = 0; }
			printf("soft left2");
		}
		//condition to move soft right slightly
		else if (ls == 0 && rs == 255 && cs == 255) {
			soft_right();
			if (flag == 1) { isBotOnNode = 0; }
			printf("soft right1");

		}
		//condition to move soft right
		else if (ls == 0 && rs == 255 && cs == 0) {
			soft_right();
			if (flag == 1) { isBotOnNode = 0; }
			printf("soft right2");
		}
		//condition to detect wether bot is on node or not
		else if (ls == 255 && rs == 255 && cs == 255) {
			isBotOnNode = 1;
		}
		////condition to detect wether bot on wrong track or not
		else if (ls == 0 && rs == 0 && cs == 0) {
			flag = 0;
			isBotOnNode = 0;
		}
		//condition to detect count number of nodes
		if (isBotOnNode == 1 && flag == 0) { node_count++; flag = 1; }
		printf("\n%d %d %d %d", ls, cs, rs, node_count);
		if (node_count == node) { stop(); break; }
		_delay_ms(10);
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
void left_turn_wls(void) {
	unsigned char ls = 1, cs = 1, rs = 1, fs = 1;
	while (1) {
		//command to move left
		left();
		//takinng input from sensors
		velocity(100, 255);
		ls = ADC_Conversion(1);
		cs = ADC_Conversion(2);
		rs = ADC_Conversion(3);
		if (ls == 0 && cs == 255 && rs == 0) { break; }
		_delay_ms(10);
	}
}
/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void) {
	unsigned char ls = 1, cs = 1, rs = 1, fs = 1;
	while (1) {
		right();
		velocity(255, 100);
		//takinng input from sensors
		ls = ADC_Conversion(1);
		cs = ADC_Conversion(2);
		rs = ADC_Conversion(3);
		if (ls == 0 && cs == 255 && rs == 0) { break; }
		_delay_ms(10);
	}
}
/*
*
* Function Name: whiteLine
* Input: void
* Output: void
* Logic: Uses white line sensors to go forward
* Example Call: whiteLine(); //Goes forward on white line
*
*/
void whiteLine() {
	unsigned char ls = 1, cs = 1, rs = 1, fs = 1;
	while (1) {
		//takinng input from sensors
		ls = ADC_Conversion(1);
		cs = ADC_Conversion(2);
		rs = ADC_Conversion(3);
		if ((ls == 255 && rs == 255 && cs == 0)) {
			forward();
		}
		else if (ls == 0 && rs == 255 && cs == 255) {
			soft_left();
		}
		else if (ls == 255 && rs == 0 && cs == 255) {
			soft_right();
		}
		else if (ls == 0 && rs == 0 && cs == 255) {
			break;
		}
		_delay_ms(1);
	}
}
/*
*
* Function Name: zigZag
* Input: void
* Output: void
* Logic:
* Example Call: zigZag(); //
*
*/
void zigZag() {
	unsigned char ls = 1, cs = 1, rs = 1, fs = 1;
	while (1) {
		//takinng input from sensors
		ls = ADC_Conversion(1);
		cs = ADC_Conversion(2);
		rs = ADC_Conversion(3);
		if ((ls == 0 && rs == 0 && cs == 255)) {
			forward();
		}
		else if (ls == 255 && rs == 0 && cs == 255) {
			soft_left();
			printf("soft left1");
		}
		else if (ls == 255 && rs == 0 && cs == 0) {
			soft_left();
			printf("soft left2");
		}
		else if (ls == 0 && rs == 255 && cs == 255) {
			soft_right();
			printf("soft right1");
		}
		else if (ls == 0 && rs == 255 && cs == 0) {
			soft_right();
			printf("soft right2");
		}
		else if (ls == 255 && rs == 255 && cs == 255) {
			break;
		}
		_delay_ms(10);
	}
}
/*
*
* Function Name: final_destination()
* Input: void
* Output: void
* Logic:
* Example Call: final_destination(); //
*
*/
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
	forward_wls(1);
	right_turn_wls();
	forward_wls(2);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	stop();  


}

/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void) {
	forward_wls(1);
	right_turn_wls();
	forward_wls(4);
	left_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);


	right_turn_wls();
	zigZag();
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);


	right_turn_wls();
	forward_wls(1);
	whiteLine();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	_delay_ms(600000);
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