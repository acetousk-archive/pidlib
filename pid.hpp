/**
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#pragma once
#include <unistd.h>
#include <cmath>

class Pid{
    public:

    /**
     * Constructor to initialize the kP, kI, and kD
     * 
     * /params double ikP
     *     This is multiplied by the error and then returned.
     */    
    Pid( const double );

    /**
     * Constructor to initialize the kP, kI, and kD
     * 
     * /params double ikP
     *      This is multiplied by the error and then added to below
     * /parmas double ikD
     *      This is multiplied by derivative and then added to above
     */
    Pid( const double, const double);

    /**
     * Constructor to initialize the kP, kI, and kD
     * 
     * /params double ikP
     *      This is multiplied by the error and then added to below
     * /params double ikI    
     *      This is multiplied by the integral then added to above
     * /parmas double ikD
     *      This is multiplied by derivative and then added to above
     */
    Pid( const double, const double, const double );

    /**
     * eRange defines the error's range of tolerance to avoid 
     * unnecessary while(true) loops. use this to set it
     * 
     * /params int eRangeIn
     */
    void eSetRange( const int );

    /**
     * set this to the max feasible output of the pid controller
     * 
     * /params int iMaxI
     */
    void setMaxI( const int );

    /**
     * This will calculate how pid works. If you don't know how
     * pid works and plan to impliment it then I'd suggest that 
     * you look at the pid pdf and python example in this directory.
     * 
     * /params double ierror
     *      This should be setpoint - sensor value
     * /return kP * Error + kI * Integral + kD * Derivative
     */
    double calculate( const double );

    private:
    double error;           //input from method calculate
    int eRange = 1;     //error range of tolerance
    double kP;

    double i;           //integral
    int maxI = 100;     //max feasible output power
    double kI;

    double eLast = 0;   //last error
    double d;           //derivative
    double kD;

    unsigned int dT = 15;
};
