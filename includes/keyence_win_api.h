#include "keyence_rs232_api.h"

#pragma once

namespace keyence
{
    class keyenceWinRS232: public IkeyenceRS232
    {
    public:
        void initKeyenceCom() override;
        //get a output value of single head: return double
        double getValueSingleOutputHead(int output_head_Nr) override;
        //get output multiple heads: return array of doubles
        double* getValueMultipleOutputHead(string HeadsArray) override;
        // get output all: return array of doubles
        double* getValueOutputHeadAll() override;
        // set general mode
        void setGeneralMode() override;
        // set communication mode
        void setCommunicationMode() override;

    };
} // namespace name
