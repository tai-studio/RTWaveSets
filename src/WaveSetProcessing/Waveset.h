#ifndef WAVESET_H
#define WAVESET_H


class Waveset
{
public:
    Waveset();
    virtual ~Waveset(){}

    /**
     * @brief Length of the WaveSet in samples.
     * @return
     */
    virtual int getLength()=0;

    /**
     * @brief get the value of the rms feature.
     * @return
     */
    virtual float getRMS()=0;

};

#endif // WAVESET_H
