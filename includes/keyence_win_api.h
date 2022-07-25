#include "keyence_rs232_api.h"
#include "SerialPort.hpp"
#include <stdlib.h>

#pragma once

namespace keyence
{
    class keyenceWinRS232: public IkeyenceRS232
    {
    public:
        explicit keyenceWinRS232(const char *portName);
        virtual ~keyenceWinRS232();
        void initKeyenceCom() override;
        //get a output value of single head: return double
        double getValueSingleOutputHead(int output_head_Nr) override;
        //get output multiple heads: return array of doubles
        double* getValueMultipleOutputHead(const char* HeadsArray) override;
        // get output all: return array of doubles
        double* getValueOutputHeadAll() override;
        // set general mode
        void setGeneralMode() override;
        // set communication mode
        void setCommunicationMode() override;
        // send cmd
        void sendCmd(const char* cmd) override;
    private:
    SerialPort* SerObject;
    const char* COM_PORT;
    const int DATA_LENGTH =255;
    };
} // namespace name

