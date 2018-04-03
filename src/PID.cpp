#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	//Initializaing variables from function
	this->Kp = Kp ; 
	this->Ki = Ki ; 
	this->Kd = Kd ;
	//Defining the error variables 
	p_error = 0 ;
	i_error = 0 ; 
	d_error = 0 ;
	prev_error = 0 ; 
}

void PID::UpdateError(double cte) {
	// difference from previous error 
	d_error = cte - prev_error ; 
	//how far are we from centre of the road (error) 
	p_error = cte ; 
	//cumilative error 
	i_error += cte ; //should be around zero 
	// updating previous error 
	prev_error = p_error ; 
	
}

double PID::TotalError() {
	//s_err = -Kp*p_error - Ki*i_error - Kd * d_error ; 
	return -Kp*p_error - Ki*i_error - Kd * d_error ; 
}

