/**
 * \class Biquad
 * \brief A biquad filter with variable Filter Type, Q, fc, Gain
 *
 * \file Biquad.cpp
 *
 *
 * \link https://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
 *
 * \author Henrik von Coler modified by Marquis Fields and Malte Schneider
 *
 * \date  2019/10/04
 *
 */

#include <math.h>
#include "Biquad.h"

Biquad::Biquad() {
    type     = bq_type_lowpass;
    a0       = 1.0;
    a1       = a2 = b1 = b2 = 0.;
    Fc       = 0.50;
    Q        = 0.707;
    peakGain = 6.0;
    z1 = z2  = 0.0;

}

Biquad::Biquad(int type, double Fc, double Q, double peakGainDB) {
    setBiquad(type, Fc, Q, peakGainDB);
    z1 = z2 = 0.0;
}

Biquad::~Biquad() {
}

void Biquad::setType(int type) {
    this->type = type;
    calcBiquad();
}

void Biquad::setQ(double Q) {
    this->Q = Q;
    calcBiquad();
}

void Biquad::setFc(double Fc) {
    this->Fc = Fc;
    calcBiquad();
}

void Biquad::setFc(double Fc, int fs) 
{
    this->Fc = Fc/fs;
    calcBiquad();
}

void Biquad::setPeakGain(double peakGainDB) {
    this->peakGain = peakGainDB;
    calcBiquad();
}
    
void Biquad::setBiquad(int type, double Fc, double Q, double peakGainDB) {
    this->type = type;
    this->Q = Q;
    this->Fc = Fc;
    setPeakGain(peakGainDB);
}

void Biquad::calcBiquad(void) {
    double norm;
    double V = pow(10, fabs(peakGain) / 20.0);
    double K = tan(M_PI * Fc);

    norm = 1 / (1 + K / Q + K * K);
    a0 = K * K * norm;
    a1 = 2 * a0;
    a2 = a0;
    b1 = 2 * (K * K - 1) * norm;
    b2 = (1 - K / Q + K * K) * norm;
    return;
}
