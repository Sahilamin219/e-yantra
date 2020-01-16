//The following code enable the sensors and controls
//Don't change this file

#include "CB_Task_1_Predef.h"

simxInt ID = 0;
simxUChar detection_state = 0;
simxUChar* lineSensorOutput = new simxUChar[7]();
simxFloat detected_point[3] = { 0,0,0 };
unsigned long color_sensor_pulse_count = 0;
simxInt dir_left = 0, dir_right = 0, vis_error, prox_error, place_handle = -3;
simxInt* res = new simxInt[2]();
simxInt* res_left = new simxInt[2]();
simxInt* res_right = new simxInt[2]();
simxInt* res_middle = new simxInt[2](), * leftJoint = new simxInt[1](), * rightJoint = new simxInt[1](),  * lineSensor = new simxInt[1](), * leftLineSensor = new simxInt[1](), * middleLineSensor = new simxInt[1](), * rightLineSensor = new simxInt[1](), * eBot = new simxInt[1](), * proxSensor = new simxInt[1]();
simxFloat linear_velocity_left = 0, linear_velocity_right = 0;

void getObjectHandles(void)
{
	simxGetObjectHandle(ID, "LeftJoint", leftJoint, simx_opmode_oneshot_wait);

	simxGetObjectHandle(ID, "RightJoint", rightJoint, simx_opmode_oneshot_wait);
	simxGetObjectHandle(ID, "LeftLineSensor", leftLineSensor, simx_opmode_oneshot_wait);
	printf("%d\n", *leftLineSensor);
	simxGetObjectHandle(ID, "RightLineSensor", rightLineSensor, simx_opmode_oneshot_wait);
	printf("%d\n", *rightLineSensor);
	simxGetObjectHandle(ID, "MiddleLineSensor", middleLineSensor, simx_opmode_oneshot_wait);
	printf("%d\n", *middleLineSensor);
	simxGetObjectHandle(ID, "LineSensor", lineSensor, simx_opmode_oneshot_wait);
	simxGetObjectHandle(ID, "eBot", eBot, simx_opmode_oneshot_wait);
	simxGetObjectHandle(ID, "ProximitySensorFront", proxSensor, simx_opmode_oneshot_wait);
//	simxGetObjectHandle(ID, "ProximitySensorRight", proxSensor, simx_opmode_oneshot_wait);
//	simxGetObjectHandle(ID, "ProximitySensorLeft", proxSensor, simx_opmode_oneshot_wait);
}

void setJointVelocities(void)
{
	simxSetJointTargetVelocity(ID, *rightJoint, linear_velocity_right, simx_opmode_oneshot);
	simxSetJointTargetVelocity(ID, *leftJoint, linear_velocity_left, simx_opmode_oneshot);
}

void forward(void)
{
	dir_left = dir_right = 1;
	linear_velocity_left = linear_velocity_right = LIN_MAX;
}

void back(void)
{
	dir_left = dir_right = -1;
	linear_velocity_left = linear_velocity_right = LIN_MAX;
}

void soft_right(void)
{
	dir_left = 1;
	dir_right = 0;
	linear_velocity_left = LIN_MAX;
	linear_velocity_right = 0;
}

void right(void)
{
	dir_left = 1;
	dir_right = -1;
	linear_velocity_left = LIN_MAX;
	linear_velocity_right = -LIN_MAX;
}

void soft_left(void)
{
	dir_left = 0;
	dir_right = 1;
	linear_velocity_left = 0;
	linear_velocity_right = LIN_MAX;
}

void left(void)
{
	dir_left = -1;
	dir_right = 1;
	linear_velocity_left = -LIN_MAX;
	linear_velocity_right = LIN_MAX;
}

void stop(void)
{
	dir_left = 0;
	dir_right = 0;
	linear_velocity_left = 0;
	linear_velocity_right = 0;
}

void velocity(int left_motor_velocity, int right_motor_velocity)
{
	if (left_motor_velocity > 255)
		left_motor_velocity = 255;
	else if (left_motor_velocity < 0)
		left_motor_velocity = 0;
	if (right_motor_velocity > 255)
		right_motor_velocity = 255;
	else if (right_motor_velocity < 0)
		right_motor_velocity = 0;

	linear_velocity_left = dir_left * LIN_MAX * left_motor_velocity / float(255.0);
	linear_velocity_right = dir_right * LIN_MAX * right_motor_velocity / float(255.0);


}


void getLineSensorData(void)
{
	//simxGetVisionSensorImage(ID, *leftLineSensor, res_left, &leftLineSensorOutput, 1, simx_opmode_buffer);
	//simxGetVisionSensorImage(ID, *middleLineSensor, res_middle, &middleLineSensorOutput, 1, simx_opmode_buffer);
	//simxGetVisionSensorImage(ID, *rightLineSensor, res_right, &rightLineSensorOutput, 1, simx_opmode_buffer);
	simxGetVisionSensorImage(ID, *lineSensor, res, &lineSensorOutput, 1, simx_opmode_buffer);
}

unsigned char getProxSensorDistance(void)
{
	unsigned char retval = 140;
	prox_error = simxReadProximitySensor(ID, *proxSensor, &detection_state, detected_point, NULL, NULL, simx_opmode_buffer);
	if (detection_state != 0)
	{
		detection_state = 0;
		retval = (unsigned char)(detected_point[2] * 1000);
	}
	else
		retval -= rand() % 40;
	return retval;
}




int initial(void)
{
	int portNb = 19997;
	int clientID = -1;
	simxFinish(-1);

	clientID = simxStart("127.0.0.1", portNb, true, true, 5000, 5);

	if (clientID > -1)
		printf("Connection Success ... \n");
	else
		printf("Connection Fail");

	return clientID;
}

int simulatorStart(int ID)
{
	printf("\n Please Enter Y to Start Simulation:		");
	char checkStartCmd = getchar();
	simxInt start = -1;
	if (checkStartCmd == 'Y' || checkStartCmd == 'y')
	{
		printf(" Starting ...");
		do
		{
			start = simxStartSimulation(ID, simx_opmode_oneshot_wait);
		} while (start != simx_return_ok);
	}
	return start;
}

void initVisionSensors(void)
{
	vis_error = simx_error_novalue_flag;
	/*do
		vis_error = simxGetVisionSensorImage(ID, *leftLineSensor, res_left, &leftLineSensorOutput, 1, simx_opmode_streaming);
	while (vis_error != simx_return_ok || vis_error == simx_error_novalue_flag);
	vis_error = simx_error_novalue_flag;
	do
		vis_error = simxGetVisionSensorImage(ID, *middleLineSensor, res_middle, &middleLineSensorOutput, 1, simx_opmode_streaming);
	while (vis_error != simx_return_ok || vis_error == simx_error_novalue_flag);
	vis_error = simx_error_novalue_flag;
	do
		vis_error = simxGetVisionSensorImage(ID, *rightLineSensor, res_right, &rightLineSensorOutput, 1, simx_opmode_streaming);
	while (vis_error != simx_return_ok || vis_error == simx_error_novalue_flag);
	vis_error = simx_error_novalue_flag;*/
	do
		vis_error = simxGetVisionSensorImage(ID, *lineSensor, res, &lineSensorOutput, 1, simx_opmode_streaming);
	while (vis_error != simx_return_ok || vis_error == simx_error_novalue_flag);
	for (int i = 0; i < VIS_SEN_INIT_VAL; i++)
	{
		getLineSensorData();

	}
	printf("Vision Sensors Initialized");
}

void initProxSensor(void)
{
	do
		prox_error = simxReadProximitySensor(ID, *proxSensor, NULL, NULL, NULL, NULL, simx_opmode_streaming);
	while (prox_error != simx_return_ok || prox_error == simx_error_novalue_flag);
}

void initSensors(void)
{
	initVisionSensors();
	initProxSensor();
}



unsigned char ADC_Conversion(unsigned char ch_no)
{
	if (ch_no == 1)//Left Line Sensor
		return ~(lineSensorOutput[LEFT_PIXEL]);
	else if (ch_no == 2)//Middle Line Sensor
		return ~(lineSensorOutput[MIDDLE_PIXEL]);
	else if (ch_no == 3)//Right Line Sensor
		return ~(lineSensorOutput[RIGHT_PIXEL]);
	else if (ch_no == FRONT_IR_ADC_CHANNEL) //Channel for Proximity sensor
		return getProxSensorDistance();
	return 13;
}


void _delay_ms(unsigned int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


void init(void)
{
	ID = initial();
	getObjectHandles();
	int check = simulatorStart(ID);
	initSensors();

}

void cleanUp(void)
{
	printf("That's it folks!");
	int check;
	velocity(0, 0);
	setJointVelocities();
	do
	{
		check = simxStopSimulation(ID, simx_opmode_oneshot_wait);
	} while (check != simx_return_ok);
	simxFinish(-1);
	ID = -1;
}

void threadCalls(void)
{
	while (ID != -1)
	{
		setJointVelocities();
		getLineSensorData();
	}

}

