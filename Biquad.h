/**
 * \class Biquad
 * \brief A biquad filter with variable Filter Type, Q, fc, Gain
 *
 * \file Biquad.h
 *
 *
 * \link https://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
 *
 * \author Henrik von Coler modified by Marquis Fields and Malte Schneider
 *
 * \date  2019/10/04
 *
 */

#ifndef Biquad_h
#define Biquad_h

enum {
    bq_type_lowpass = 0,
    bq_type_highpass,
    bq_type_bandpass,
    bq_type_notch,
    bq_type_peak,
    bq_type_lowshelf,
    bq_type_highshelf
};

class Biquad {
public:
    Biquad();
    Biquad(int type, double Fc, double Q, double peakGainDB);
    ~Biquad();

    ///
    /// \brief
    /// sets the filter type
    void setType(int type);

    ///
    /// \brief
    /// sets the filter quality
    void setQ(double Q);

    ///
    /// \brief
    /// sets the cutoff frequency
    void setFc(double Fc);

    ///
    /// \brief
    /// sets the cutoff frequency in relation to the sample rate
    void setFc(double Fc, int fs);

    ///
    /// \brief
    /// sets the resonance gain value
    void setPeakGain(double peakGainDB);

    ///
    /// \brief
    /// sets member variables necessary for calculation of the filter coefficients
    void setBiquad(int type, double Fc, double Q, double peakGain);
    
    /// 
    /// \brief filters input signal
    /// \param in is input sample
    /// \return filtered output
    float process(float in);

    /// 
    /// \brief peakGain
    /// resonance gain of the biquad filter
    double peakGain;
    
protected:

    ///
    /// \brief
    /// calculates filter coefficients from class member variables
    void calcBiquad(void);

    ///
    /// \brief
    /// represents the filter type
    int type;
    
    /// 
    /// \brief
    /// represents the filter coefficient a0
    double a0;

    /// 
    /// \brief
    /// represents the filter coefficient a1
    double a1;

    /// 
    /// \brief
    /// represents the filter coefficient a2
    double a2;

    /// 
    /// \brief
    /// represents the filter coefficient b1
    double b1;

    /// 
    /// \brief
    /// represents the filter coefficient b2
    double b2;

    /// 
    /// \brief
    /// represents filter cutoff frequency
    double Fc;

    /// 
    /// \brief
    /// represents filter Q
    double Q;

    /// 
    /// \brief
    /// buffer for previous calculation
    double z1;

    /// 
    /// \brief
    /// buffer for previous calculation
    double z2;
};

inline float Biquad::process(float in) {
    double out = in * a0 + z1;
    z1 = in * a1 + z2 - b1 * out;
    z2 = in * a2 - b2 * out;
    return out;
}

#endif // Biquad_h
