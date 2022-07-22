#include "keyence_api.h"
#pragma once
namespace keyence
{
    class IkeyenceRS232 : public IkeyenceBase
    {
    public:
        virtual void initKeyenceCom()=0 ;
        //get a output value of single head: return double
        virtual double getValueSingleOutputHead(int output_head_Nr) =0;
        //get output multiple heads: return array of doubles
        virtual double* getValueMultipleOutputHead(string HeadsArray) =0;
        // get output all: return array of doubles
        virtual double* getValueOutputHeadAll() =0;
        // set general mode
        virtual void setGeneralMode() =0;
        // set communication mode
        virtual void setCommunicationMode() =0;
    };
} // namespace name

