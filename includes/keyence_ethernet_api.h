#include "keyence_api.h"
#pragma once

namespace keyence
{
    class IkeyenceEthernet :public IkeyenceBase
    {
    public:
        IkeyenceEthernet();
        virtual ~IkeyenceEthernet();
        virtual void initKeyenceCom()=0 ;
        //get a output value of single head: return double
        virtual double getValueSingleOutputHead(int output_head_Nr) =0;
        //get output multiple heads: return array of doubles
        virtual double* getValueMultipleOutputHead(const char* HeadsArray) =0;
        // get output all: return array of doubles
        virtual double* getValueOutputHeadAll() =0;
        // set general mode
        virtual void setGeneralMode() =0;
        // set communication mode
        virtual void setCommunicationMode() =0;
        // send cmd
        virtual void sendCmd(std::string& cmd) =0;

    };
} // namespace name

