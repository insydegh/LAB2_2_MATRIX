//
// Created by fokus on 18.04.2021.
//

#ifndef MAT_COMPLEX_H
#define MAT_COMPLEX_H

#endif //MAT_COMPLEX_H
#include <math.h>
#include <iomanip>

class complex {
private:
    float realPart;
    float imagPart;

public:
    //Constructor
    complex(float realPart = float(), float imagPart = float()): realPart(realPart), imagPart(imagPart) {}

    float real() const {
        return this->realPart;
    }

    float imag() const {
        return this->imagPart;
    }

    complex operator+(float val) const {
        return complex(this->realPart + val, this->imagPart);
    }

    complex operator-(float val) const {
        return complex(this->realPart - val, this->imagPart);
    }

    complex operator+(const complex& val) const {
        return complex(this->realPart + val.realPart, this->imagPart + val.imagPart);
    }

    complex operator-(const complex& val) const {
        return complex(this->realPart - val.realPart, this->imagPart - val.imagPart);
    }

    void operator+=(const complex& val) {
        this->realPart += val.real();
        this->imagPart += val.imag();
    }

    //Multiplying on float number
    complex operator*(float val) const {
        return complex(this->realPart * val, this->imagPart * val);
    }

    //Multiplying on complex number
    complex operator*(complex val) const {
        return complex(this->real() * val.real() - this->imag() * val.imag(), this->real() * val.imag() + this->imag() * val.real());
    }

    bool operator==(const complex& val) const {
        return this->realPart == val.real() && this->imagPart == val.imag();
    }

    bool operator!=(const complex& val) const {
        return !this->operator==(val);
    }

    int Sign(float im) {
        if (im<0) {return -1;}
        if (im>1) {return 1;}
        return 0;
    }
//Square root of complex number
// if the number looks like a+i(b)
//root will look like c+i(d) where
//             ______________                  ____________________
//           /   _______                     /   ________
// с = -   /  -/ a^2+b^2 +a    d= sgn(b)   /  -/ a^2+b^2  -a
//      \/        2                     \/          2
//
    complex sqrt_complex()  {
        float re = this->realPart;
        float im = this->imagPart;
        re = ::sqrt((::sqrt(re*re+im*im)+re)/2);
        im = float(Sign(im))*(::sqrt((::sqrt(re*re+im*im)-re)/2));
        return complex(re, im);

    }
//Print complex number in form like a+i(b)
    void print() const {

        cout<< this->realPart<<"+i("<<this->imagPart<<")"<<setw(9);
    }

};

