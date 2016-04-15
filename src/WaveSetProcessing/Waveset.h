#ifndef WAVESET_H
#define WAVESET_H

#include "WsMedatData.h"

class Waveset
{
public:
    Waveset();
    virtual ~Waveset(){}

    /**
     * @brief Length of the Waveset in samples.
     * @return
     */
    virtual int getLength()=0; // TODO remove an replace by AudioPiece getLen

    /**
     * @brief Get the Metadata of the Waveset.
     * @return
     */
    virtual WsMedatData getMetaData()=0;

};

#endif // WAVESET_H
