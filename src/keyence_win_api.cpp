#include "keyence_win_api.h"
namespace keyence
{
    keyenceWinRS232::keyenceWinRS232(const char* portName)
    {
        std::cout << "creating keyence rs232 to windows interface" << std::endl;
        COM_PORT = portName;
        SerObject = new SerialPort(portName);
    }
    keyenceWinRS232::~keyenceWinRS232()
    {
        delete SerObject;
    }
    //init the com with keyence
    void keyenceWinRS232::initKeyenceCom()
    {
        std::cout << "Is connected: " << SerObject->isConnected() << std::endl;
    }
    void keyenceWinRS232::sendCmd(const char* cmd) {
        SerObject->writeSerialPort(cmd, static_cast<std::string>(cmd).size());
    }

    //get a output value of single head: head number format is 01,02,03... but param is given as int 1,2,3...
    double keyenceWinRS232::getValueSingleOutputHead(int output_head_Nr)
    {
        int const buffer_len = DATA_LENGTH;
        const char* Zero = "0";
        std::string Response;
        const char* receivedString;
        double val = 0;
        // head specific parameters
        std::string Soutput_head_Nr = std::to_string(output_head_Nr);
        //write the get value command
        const char* command = "mesure_value_outputN";
        std::string cmd = static_cast<std::string>(findCommand(command, commands));
        if (output_head_Nr < 9) {
            Soutput_head_Nr = Zero + Soutput_head_Nr;
        }
        // cmd=MS,01
        cmd += Soutput_head_Nr;
        const char* cmdToSend = (cmd + cr).c_str();
        // send full cmd
        sendCmd(cmdToSend);

        if (SerObject->isConnected())
        {
            // get the response
            int hasData = SerObject->readSerialPort(receivedString, DATA_LENGTH);
            if (hasData)
            {
                Response = receivedString;
                if (Response.substr(0, 5) == cmd)
                {
                    std::cout << "full response: " + Response << std::endl;
                    Response.erase(0, 6); //remove default response
                    val = atof(Response.c_str());
                }
            }

        }
        // error checking
        if (val == 0xFFFF || val == 0xFFFFFFFF)
        {
            std::cout << "out of range value" << std::endl;
            return lastValue;
        }
        else
        {
            if (val == 0) { std::cout << "no value" << std::endl; return lastValue; }
            else {
                std::cout << "filtered response for head: " + Soutput_head_Nr + " equal to: " << val << std::endl;
                lastValue = val;
                return val;
            }
        }
    }
    //get output multiple heads in this format: "0-12" example: head 1,2 and 3 will be 111000000000
    double* keyenceWinRS232::getValueMultipleOutputHead(const char* HeadsArray)
    {
        int NumOfOutputs = 0;
        std::string Response;
        const char* DATA;
        //write the get value command
        if (NumOfOutputs < 1)
        {
            for (auto& element : static_cast<std::string>(HeadsArray))
            {
                if (element == '1')
                {
                    NumOfOutputs++;
                }
            }
        }
        double Values[3];
        const char* valuesHolder = "";
        int ValuesCounter = 0;
        std::cout << "number of heads" << std::endl;
        std::cout << NumOfOutputs << std::endl;
        const char* command = "mesure_value_multipleN";
        std::string cmd = findCommand(command, commands);
        //cmd:MM,010010000000
        cmd += HeadsArray;
        std::cout << "command sent:" << std::endl;
        std::cout << cmd << std::endl;
        sendCmd((cmd + cr).c_str());
        if (SerObject->isConnected())
        {
            // Read data from rs232 port
            int hasData = SerObject->readSerialPort(DATA, DATA_LENGTH);
            // Response: MM,010010000000,value[,value,value]: 
            Response = DATA;
            Response.replace(cmd.size(), Response.size(), "");
            std::cout << Response << std::endl;
            // iterate response and extract values
            for (int i = 0; i < Response.length();i++)
            {// ,val1,val2,val3,val4,val5
                if (Response[i] == ',')
                {
                    valuesHolder = Response.substr(i + 1, Response.at( i + 1)).c_str();
                    std::cout << "value holder got" << std::endl;
                    std::cout << valuesHolder << std::endl;
                    Values[ValuesCounter] = atof(static_cast<std::string>(valuesHolder).c_str());
                    ValuesCounter++;
                    valuesHolder = "";
                }
                if (ValuesCounter == NumOfOutputs) break;
            }
            for (int i = 0; i < NumOfOutputs; i++)
            {
                std::cout << "extracted values" << std::endl;
                std::cout << *(Values + i) << std::endl;
            }
            return Values;
        }
    }
    // get output all
    double* keyenceWinRS232::getValueOutputHeadAll()
    {
        std::string Response;
        const char* valuesHolder = "";
        int ValuesCounter = 0;
        std::string cmd;
        const char* command = "mesure_value_All";
        const char* receivedString;
        cmd = findCommand(command, commands);
        // speed purpose we skip any loop
        //cmd = "MA";
        sendCmd((cmd + cr).c_str());
        if (SerObject->isConnected())
        {
            // Read data from rs232 port
            int hasData = SerObject->readSerialPort(receivedString, DATA_LENGTH);
            // MA,value[,value,value]: 
            if (hasData)
            {
                Response.replace(cmd.size(), Response.size(), ""); //remove default response
                std::cout << Response << std::endl;
            }

            double Values[NUM_OUTPUT_HEADS];
            // try to gte rid of any loop that slow down the main loop
            // as we know that we use three heads, we can just add the index
            int first_occurance = Response.find_first_of(',', 0);
            int second_occurance = Response.find_first_of(',', first_occurance + 1);
            int third_occurance = Response.find_first_of(',', second_occurance + 1);
            Values[0] = atof(Response.substr(first_occurance + 1, second_occurance + 1).c_str());
            Values[1] = atof(Response.substr(second_occurance + 1, third_occurance + 1).c_str());
            Values[2] = atof(Response.substr(third_occurance + 1, Response.length()).c_str());
            return Values;
        }
    }

    // set general mode
    void keyenceWinRS232::setGeneralMode()
    {
        //write the get value command
        const char* command = "set_general_mode";
        const char* cmd = findCommand(command, commands);
        const char* Response;
        const char* receivedString;
        sendCmd(cmd + cr);
        if (SerObject->isConnected())
        {
            // Read data from rs232 port
            int hasData = SerObject->readSerialPort(receivedString, DATA_LENGTH);
            std::cout << receivedString << std::endl;
        }
    }
    // set communication mode
    void keyenceWinRS232::setCommunicationMode()
    {
        //write the get value command
        const char* receivedString;
        const char* command = "set_communication_mode";
        const char* cmd = findCommand(command, commands);
        sendCmd(cmd + cr);
        if (SerObject->isConnected())
        {
            // Read data from rs232 port
            int hasData = SerObject->readSerialPort(receivedString, DATA_LENGTH);
            std::cout << receivedString << std::endl;
        }

        }
} // namespace name
