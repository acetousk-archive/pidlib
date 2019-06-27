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

#include "pid.hpp"

Pid::Pid( double kPset ){
    kP = kPset;
    kI = 0;
    kD = 0;
}

Pid::Pid( double kPset, double kDset ){
    kP = kPset;
    kI = 0;
    kD = kDset;
}

Pid::Pid( double kPset, double kIset, double kDset ){
    kP = kPset;
    kI = kIset;
    kD = kDset;    
}

void Pid::eSetRange( int eRangeIn ){
    eRange = eRangeIn;
}

void Pid::setMaxI( int maxIIn ){
    maxI = maxIIn;
}

double Pid::calculate( double error ){
    p = error;
    //all for proportional

    i += error; //area under curve      //TODO: see pdf 3.1
    if( std::abs(error) <= eRange ){
        error = 0; //pid loops can continue forever... until now
    }
    if( std::abs(i) > maxI ){
        i = maxI;       //if i's positive
        if( i < 0 ){
            i *= -1;    //if i's negative
        }
    }
    //all for integral

    d = error - eLast;
    eLast = error;
    //all for derivative

    usleep(dT); //uncomment if you run unix based
    //sleep(dT); //uncomment if you run evil windows
    //gotta delay

    return((             
        ( kP * p ) +    /*  p   p  */
        ( kI * i ) +    /*    i    */
        ( kD * d )      /*  \ddd/  */
    ));
    //done (as if you didnt already know)
}
