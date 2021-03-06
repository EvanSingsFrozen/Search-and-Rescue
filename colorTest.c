#pragma config(Sensor, S1,     color,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     button,         sensorEV3_Touch)
#pragma config(Motor,  motorB,          left,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          right,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          colorMotor,    tmotorEV3_Medium, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*colors:
0= none
1= black
2= blue
3= green
4= yellow
5= red
6= white
7= brown*/
//mode 1 = lineFollow
//mode 2 = grab
int mode = 1;
int speed = -20;
int count = 0;
void grab()
{
	while(mode == 2)
	{
		if(SensorValue(color) == 4)
		{
			count = 1;
			resetMotorEncoder(colorMotor);
			while(getMotorEncoder(colorMotor) < 90 && count == 1 && getMotorEncoder(colorMotor) > -90)
			{
				motor[colorMotor] = speed;
			}
			if(getMotorEncoder(colorMotor) >= 90 || getMotorEncoder(colorMotor) <= -90)
			{
				motor[colorMotor] = 0;
				speed = -speed;
				resetMotorEncoder(colorMotor);
				count = 0;
				mode = 1;
			}
		}
	}
}
task main()
{
	while(true)
	{
		displayBigTextLine(5, "Color: %d",SensorValue(color));
		while(getTimerValue(timer1)<=1500 && SensorValue(color) == 2)
		{
			clearTimer(timer2);
			motor[left] = 10;
			motor[right] = 40;
		}
		while(getTimerValue(timer1)>=1501 && SensorValue(color) == 2)
		{
			clearTimer(timer2);
			motor[left] = 40;
			motor[right] = 10;
		}
		while(SensorValue(color) == 5 && getTimerValue(timer2)<=1500)
		{
			clearTimer(timer1);
			motor[left] = 40;
			motor[right] = 5;
		}
		while(SensorValue(color) == 5 && getTimerValue(timer2)>=1501)
		{
			clearTimer(timer1);
			motor[left] = 5;
			motor[right] = 40;
		}
		if(SensorValue(color) == 1)
		{
			mode = 2;
		}
		/*while(mode == 2)
		{
			while(SensorValue(color) == 0)
			{
				motor[left] = 40;
				motor[right] = 40;
			}
		  if(SensorValue(color) == 4)
			{
				motor[left] = 40;
				motor[right] = 40;
				wait1Msec(100);
				while(SensorValue(color) == 4)
				{
					motor[left] = 0;
					motor[right] = 0;
					grab();
			  }
		  }
		}*/
	}
}
