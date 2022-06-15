/**
   @file keyence_api.cpp
   @author sami dhiab (sami@theion.de)
   @brief keyence sensors APIs
   @version 0.1
   @date 2022-04-06

   @copyright Copyright (c) 2022

*/
#include "keyence_api.h"

//commands section
// helper method to retrieve commands from map
std::string IkeyenceBase::findCommand(string& command, std::map<std::string, std::string>& CommandMap)
{
  for (auto it = CommandMap.begin(); it != CommandMap.end(); ++it)
  {
    if ((*it).first == command)
    {
      return (*it).second;
    }
  }
}
/********** Keyence RS232 **********/
//init the com with keyence
void IkeyenceRS232::initKeyenceCom()
{
  SERIAL_HANDLER.BEGIN(KEYENCE_SERIAL_BAUDRATE);
}

//get a output value of single head: head number format is 01,02,03... but param is given as int 1,2,3...
double IkeyenceRS232::getValueSingleOutputHead(int output_head_Nr)
{
  static double last_time = 0;
  std::string Zero = "0";
  std::string Response;
  double val;
  // head specific parameters
  std::string Soutput_head_Nr = string(output_head_Nr);
  //write the get value command
  std::string command = "mesure_value_outputN";
  std::string cmd = findCommand(command, commands);
  if (output_head_Nr < 9) {
    Soutput_head_Nr = Zero + Soutput_head_Nr;
  }
  cmd += Soutput_head_Nr;
  // from hear comes magic  
  // if the buffer is not empty
  if (SERIAL_HANDLER->available() > 0)
  {
    // get it
    Response = SERIAL_HANDLER->readstringUntil('\r');
    //SERIAL_HANDLER.PRINT_NEW_LINE("buffer already full with: "+Response);
    if (Response.substring(0, 5) == cmd)
    {
      SERIAL_HANDLER.PRINT_NEW_LINE("full response: " + Response);
      Response.remove(0, 6); //remove default response
      val = Response.toDouble();
      SERIAL_HANDLER.PRINT_NEW_LINE("filtered response for head: " + Soutput_head_Nr + " equal to: " + Response + " double value: " + val);
      if (val > 0) return val;
    }
    SERIAL_HANDLER->flush();
  }
  SERIAL_HANDLER->PRINT(cmd + CR);
  // because the need of time between cmd and response
  if (millis() - last_time >= 200) //time to send/receive response from 1 head
  {
    if (SERIAL_HANDLER->available() > 0)
    {
      // Read data from rs232 port
      Response = SERIAL_HANDLER->readstringUntil('\r');
      // write the data to the other port
      //MS,OUT01,value CR: remove M->,: 9
      //SERIAL_HANDLER.PRINT_NEW_LINE("cmd: "+cmd+" Response: "+ Response.substring(0,5));
      if (Response.substring(0, 5) == cmd)
      {
        SERIAL_HANDLER.PRINT_NEW_LINE("full response: " + Response);
        Response.remove(0, 6); //remove default response
        val = Response.toDouble();
        SERIAL_HANDLER.PRINT_NEW_LINE("filtered response for head: " + Soutput_head_Nr + " equal to: " + Response + " double value: " + val);
        SERIAL_HANDLER->flush();
        last_time = millis();
        if (val > 0) return val;
      }
    }
  }
}
//get output multiple heads in this format: "0-12" example: head 1,2 and 3 will be 111000000000
double* IkeyenceRS232::getValueMultipleOutputHead(std::string HeadsArray)
{
  int NumOfOutputs = 0;
  //write the get value command
  if (NumOfOutputs < 1)
  {
    for (auto& element : HeadsArray)
    {
      if (element == '1')
      {
        NumOfOutputs++;
      }
    }
  }
  double* Values = new double[NumOfOutputs];
  //double Values[NumOfOutputs];
  std::string valuesHolder = "";
  int ValuesCounter = 0;
  SERIAL_HANDLER.PRINT_NEW_LINE("number of heads");
  SERIAL_HANDLER.PRINT_NEW_LINE(NumOfOutputs);
  std::string command = "mesure_value_multipleN";
  std::string cmd = findCommand(command, commands);
  //cmd:MM,010010000000
  cmd += string(HeadsArray);
  SERIAL_HANDLER.PRINT_NEW_LINE("command sent:");
  SERIAL_HANDLER.PRINT_NEW_LINE(cmd);
  SERIAL_HANDLER->PRINT_NEW_LINE(cmd);
  if (SERIAL_HANDLER->available() > 0)
  {
    // Read data from rs232 port
    std::string Response = SERIAL_HANDLER->readstringUntil('\r');
#ifdef DEBUG
    // write the data to the other port
    SERIAL_HANDLER.PRINT_NEW_LINE("response:");
    SERIAL_HANDLER.PRINT_NEW_LINE(Response);
#endif
    // Response: MM,010010000000,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    SERIAL_HANDLER.PRINT_NEW_LINE(Response);
    // iterate response and extract values

    for (int i = 0; i < Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if (Response[i] == ',')
      {
        valuesHolder = Response.substring(i + 1, Response.indexOf(',', i + 1));
        SERIAL_HANDLER.PRINT_NEW_LINE("value holder got");
        SERIAL_HANDLER.PRINT_NEW_LINE(valuesHolder);
        Values[ValuesCounter] = valuesHolder.toDouble();
        ValuesCounter++;
        valuesHolder = "";
      }
      if (ValuesCounter == NumOfOutputs) break;
    }
    for (int i = 0; i < NumOfOutputs; i++)
    {
      SERIAL_HANDLER.PRINT_NEW_LINE("extracted values");
      SERIAL_HANDLER.PRINT_NEW_LINE(*(Values + i));
    }
    return Values;
  }
}
// get output all
double* IkeyenceRS232::getValueOutputHeadAll()
{
  std::string Response;
  std::string valuesHolder = "";
  int ValuesCounter = 0;
  std::string cmd;
  std::string command = "mesure_value_All";
  //cmd = findCommand(command, commands);
  // speed purpose we skip any loop
  cmd = "MA";
  SERIAL_HANDLER->PRINT(cmd + CR);
  if (SERIAL_HANDLER->available() > 0)
  {
    // Read data from rs232 port
    Response = SERIAL_HANDLER->readstringUntil('\r');
    // MA,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    SERIAL_HANDLER.PRINT_NEW_LINE(Response);
    double* Values = new double[HeadsCount] {0}; //heap
    // iterate response and extract values
    /*for (int i = 0; i < Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if (Response[i] == ',')
      {
        valuesHolder = Response.substring(i + 1, Response.indexOf(',', i + 1));
        //SERIAL_HANDLER.PRINT("value holder got: ");
        //SERIAL_HANDLER.PRINT_NEW_LINE(valuesHolder.toDouble());
        Values[ValuesCounter] = valuesHolder.toDouble();
        ValuesCounter++;
        //SERIAL_HANDLER.PRINT("extracted values: ");
        //SERIAL_HANDLER.PRINT_NEW_LINE(*(Values + i));
      }
      if (ValuesCounter == HeadsCount) break;
    }*/
    // try to gte rid of any loop that slow down the main loop
    // as we know that we use three heads, we can just add the index
    int first_occurance=Response.indexOf(',', 0);
    int second_occurance=Response.indexOf(',', first_occurance+1);
    int third_occurance=Response.indexOf(',',second_occurance+1);
    Values[0] = Response.substring(first_occurance+1,second_occurance+1).toDouble();
    Values[1] = Response.substring(second_occurance+1,third_occurance+1).toDouble();
    Values[2] = Response.substring(third_occurance+1,Response.length()).toDouble();
    //SERIAL_HANDLER.PRINT_NEW_LINE(Values[0]);
    //SERIAL_HANDLER.PRINT_NEW_LINE(Values[1]);
    //SERIAL_HANDLER.PRINT_NEW_LINE(Values[2]);
    IkeyenceBase::LookUpValues = Values;
    delete[] Values;
    return IkeyenceBase::LookUpValues;
  }
}

// set general mode
void IkeyenceRS232::setGeneralMode()
{
  //write the get value command
  std::string command = "set_general_mode";
  std::string cmd = findCommand(command, commands);
  SERIAL_HANDLER->PRINT(cmd + CR);
  if (SERIAL_HANDLER->available() > 0)
  {
    // Read data from rs232 port
    std::string Response = SERIAL_HANDLER->readstringUntil('\r');
#ifdef DEBUG_
    // write the data to the other port
    SERIAL_HANDLER.PRINT_NEW_LINE("response:");
    SERIAL_HANDLER.PRINT_NEW_LINE(Response);
#endif
  }
}
// set communication mode
void IkeyenceRS232::setCommunicationMode()
{

  //write the get value command
  std::string command = "set_communication_mode";
  std::string cmd = findCommand(command, commands);
  SERIAL_HANDLER->PRINT(cmd + CR);
  delay(100); //this delay is obligatory to clear buffer

  if (SERIAL_HANDLER->available() > 0)
  {
    // Read data from rs232 port
    std::string Response = SERIAL_HANDLER->readstringUntil('\r');
#ifdef DEBUG
    // write the data to the other port
    SERIAL_HANDLER.PRINT_NEW_LINE("response:");
    SERIAL_HANDLER.PRINT_NEW_LINE(Response);
#endif
  }
  SERIAL_HANDLER->write("");
  SERIAL_HANDLER->flush();
}

