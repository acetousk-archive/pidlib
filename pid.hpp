#pragma once
#include <unistd.h>

class Pid{
    public:

    /**
     * Constructor to initialize the kP, kI, and kD
     * 
     * /params double kPset
     *     This is multiplied by the error and then returned.
     */    
    Pid( double kPset );

    /**
     * Constructor to initialize the kP, kI, and kD
     * 
     * /params double kPset
     *      This is multiplied by the error and then added to below
     * /parmas double kDset
     *      This is multiplied by derivative and then added to above
     */
    Pid( double kPset, double kDset );

    /**
     * Constructor to initialize the kP, kI, and kD
     * 
     * /params double kPset
     *      This is multiplied by the error and then added to below
     * /params double kIset    
     *      This is multiplied by the integral then added to above
     * /parmas double kDset
     *      This is multiplied by derivative and then added to above
     */
    Pid( double kPset, double kIset, double kDset );

    /**
     * eRange defines the error's range of tolerance to avoid 
     * unnecessary while(true) loops. use this to set it
     * 
     * /params int eRangeIn
     */
    void eSetRange( int eRangeIn );

    /**
     * set this to the max feasible output of the pid controller
     * 
     * /params int MaxIIn
     */
    void setMaxI( int maxIIn );

    /**
     * This will calculate how pid works. If you don't know how
     * pid works and plan to impliment it then I'd suggest that 
     * you look at the pid pdf and python example in this directory.
     * 
     * /params double error
     *      This should be setpoint - sensor value
     * /return kP * Error + kI * Integral + kD * Derivative
     */
    double calculate( double error );

    private:
    double p;           //power = error
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
