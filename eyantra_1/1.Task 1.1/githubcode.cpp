//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions
//my githubcode.cpp
//tried didn't worked
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
	int rs, cs, ls;
	//Doing ADC conversion
	ls = ADC_Conversion(1);
	cs = ADC_Conversion(2);
	rs = ADC_Conversion(3);
	printf("\n%d %d %d", ls, cs, rs);//call this function to print the array onto the screen
	int flag = 0; //reset the flag to 0
	while (1) {
		//check if robot's center white line sensor is on the white line
		if (cs == 0) {
			flag = 1;//set the flag to 0 so that further white line sensor comparision is disabled
			velocity(255, 255);//left and right motor is at same velocity
			forward();
		}
		//robot is drifting towards left side, increase velocity of the left wheel and decrease velocity of the right wheel
		if (ls == 0 && flag == 0) {
			flag = 1; //set the flag to 0 so that further white line sensor comparision is disabled
			velocity(100, 255);//increase left motor velocity & decrease  right motor velocity
		}
		//robot is drifting towards right side, decrease velocity of the left wheel and increase velocity of the right wheel
		if (rs == 0 && flag == 0) {
			flag = 1; //set the flag to 0 so that further white line sensor comparision is disabled
			velocity(255, 100);//decrease  left motor velocity & increase right motor velocity
		}
		if (ls != 0 && cs != 0 && rs != 0) {
			stop();
		}
		else
		{
			forward();
		}
		_delay_ms(250);
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

}


/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{
	// Write your task 1.1 Logic here
	forward_wls(100);
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