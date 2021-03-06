//
//  PID_Yo.cpp
//  PID_Yo
//
//  Created by Yosub Lee on 7/15/14.
//  Copyright (c) 2014 Yosub Lee. All rights reserved.
//  Updated Modified by Peter Quan
// 
//  Base source from 
//  http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/
//

#include "PID_Yo.h"

PID::PID()
{
	setPoint(0);
	m_input     = 0;
	m_output    = 0;
	m_setpoint  = 0;
	m_iTerm    = 0;
	m_lastInput = 0;
	m_sampleTime = 1000;   
	m_sampleTimeSec = 0;	//(800hz), but since we are using the filter, it drops down to 300Hz
	m_ratio = 0;
	m_outMin = 0;
	m_outMax = 0;
	kp = 1;
	ki = 0.1;
	kd = 0.1;
}

PID::~PID(){}

void PID::setPoint(double point)
{
	m_setpoint = point;
	cout << "new SetPoint: " << m_setpoint << endl;
}

/*
void PID::setGains(double kp, double ki, double kd)
{
	this->kp = kp;
	this->ki = ki;
	this->kd = kd;
	std::cout << "P: " << this->kp << " I: " << this->ki << " D:" << this->kd << std::endl;
	std::cout << "Initialized \n";
	initialized = true;
}
*/
double PID::getPoint() {
	return m_setpoint;
}

double PID::getP() {
	return p;
}

double PID::getI() {
	return i;
}

double PID::getD() {
	return d;
}

void PID::setTunings(double kp2, double ki2, double kd2){
	//Record
	p = kp2;
	i = ki2;
	d = kd2;

	m_sampleTimeSec = m_sampleTime / 1000;
	kp = kp2;
	ki = ki2 * m_sampleTimeSec;
	kd = kd2 / m_sampleTimeSec;
}

void PID::setSampleTime(double newSampleTime){
	if(newSampleTime > 0){
		m_ratio = newSampleTime / m_sampleTime;
		ki *= m_ratio;
		kd /= m_ratio;
		m_sampleTime = newSampleTime;
	}
}

void PID::setOutputLimits(double min, double max){
	if(min > max) 
		return;
	
	m_outMin = min;
	m_outMax = max;
	
	if(m_output > m_outMax)
		m_output = m_outMax;
	
	else if(m_output < m_outMin)
		m_output = m_outMin;
	
	if(m_iTerm > m_outMax)
		m_iTerm = m_outMax;
	
	else if(m_iTerm < m_outMin)
		m_iTerm = m_outMin;
}
/*
double PID::compute(double input)
{
	if ( initialized ) {
		m_input = input;
		
		// Sample Time
		m_now = chrono::high_resolution_clock::now();
		
		float timeDiff=(chrono::duration_cast<chrono::microseconds>(m_now-m_lastTime).count())/100000.0;
		
		if(timeDiff >= m_sampleTime){
			// Compute all the working error variables
			double error = m_setpoint - m_input;
			m_iTerm += (ki * error);
			if(m_iTerm > m_outMax)
				m_iTerm = m_outMax;
			else if(m_iTerm < m_outMin)
				m_iTerm = m_outMin;
			double dInput = (m_input - m_lastInput);
			// Compute PID Output
			m_output = kp * error + ki * m_iTerm - kd * dInput;
			if(m_output > m_outMax)
				m_output = m_outMax;
			else if(m_output < m_outMin)
				m_output = m_outMin; 
			// Remember some variables for next time
			m_lastInput = m_input;
			m_lastTime = m_now;
			//}
			
			return m_output;
		}
		else {
			return 0;
		}
	}
}
*/

double PID::compute(double input)
{
	m_input = input;
		
	// Compute all the working error variables
	double error = m_setpoint - m_input;
	m_iTerm += (ki * error);
	if(m_iTerm > m_outMax)
		m_iTerm = m_outMax;
	else if(m_iTerm < m_outMin)
		m_iTerm = m_outMin;
	double dInput = (m_input - m_lastInput);
	// Compute PID Output
	m_output = kp * error + ki * m_iTerm - kd * dInput;
	if(m_output > m_outMax)
		m_output = m_outMax;
	else if(m_output < m_outMin)
		m_output = m_outMin; 
	// Remember some variables for next time
	m_lastInput = m_input;
	return m_output;
}
