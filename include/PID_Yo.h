//
//  PID_Yo.h
//  PID_Yo
//
//  Created by Yosub Lee on 7/15/14.
//  Copyright (c) 2014 Yosub Lee. All rights reserved.
//
 
#ifndef __PID_Yo__PID_Yo__
#define __PID_Yo__PID_Yo__
 
#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
 
using namespace std;
 
class PID {
public:
    PID();
    ~PID();
    void setPoint(double point);
//    void setGains(double kp, double ki, double kd);
    double compute(double input);
    void setTunings(double kp2, double ki2, double kd2);
    void setSampleTime(double newSampleTime);
    void setOutputLimits(double min, double max);
    double getP();
    double getI();
    double getD();
    double getPoint();
private:
    double m_input, m_output, m_setpoint;
    double m_iTerm, m_lastInput;
    double kp, ki, kd, p, i, d;
    double m_sampleTimeSec;
    double m_ratio;
    //bool initialized;   
    double m_sampleTime;	// AHRS sample time
    //chrono::time_point<std::chrono::high_resolution_clock> m_now, m_lastTime;
    double m_outMin, m_outMax;
};
 
#endif /* defined(__PID_Yo__PID_Yo__) */
