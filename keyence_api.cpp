/**
   @file keyence_api.cpp
   @author sami dhiab (sami@theion.de)
   @brief keyence sensors APIs
   @version 0.1
   @date 2022-04-06

   @copyright Copyright (c) 2022

*/
#include "keyence_api.h"

//keyence base class 
//define keyence static variables
int IkeyenceBase::HeadsCount = 0;
std::vector<int> IkeyenceBase::NumUsedHeads;
int IkeyenceBase::HeadsArray[12];
double* IkeyenceBase::LookUpValues = new double[IkeyenceBase::HeadsCount]{ 0 };

// list heads availble
void IkeyenceBase::listHeads()
{
  transformArrayToVector(HeadsArray, NumUsedHeads);
  NumUsedHeads.resize(HeadsCount);
  //SERIAL_HANDLER.println("listing heads in vector container");
    // For loop using iterators
  if (!NumUsedHeads.empty())
  {
    for (std::vector<int>::iterator it = NumUsedHeads.begin(); it != NumUsedHeads.end(); it++)
    {
#ifdef _DEBUG_
      SERIAL_HANDLER.println("next head number:");
      SERIAL_HANDLER.println(*it);
#endif
    }
  }
  else SERIAL_HANDLER.println("empty heads container");
}
//commands section
// helper method to retrieve commands from map
string IkeyenceBase::findCommand(string& command, std::map<string, string>& CommandMap)
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

// if the SERIAL_HANDLER handler is changed dynamicly
void IkeyenceRS232::setSERIAL_HANDLERHandler(HardwareSERIAL_HANDLER& serHandler)
{
  this->SERIAL_HANDLERHandler = &serHandler;
}
// if baudrate is changed dynamicly
void IkeyenceRS232::setSERIAL_HANDLERBaudrate(unsigned long baud)
{
  this->baudrate = baud;
}

//init the com with keyence
void IkeyenceRS232::initKeyenceCom()
{
  SERIAL_HANDLERHandler->begin(baudrate);
}

//get a output value of single head: head number format is 01,02,03... but param is given as int 1,2,3...
double IkeyenceRS232::getValueSingleOutputHead(int output_head_Nr)
{
  static double last_time = 0;
  string Zero = "0";
  string Response;
  double val;
  // head specific parameters
  string Soutput_head_Nr = string(output_head_Nr);
  //write the get value command
  //
  string command = "mesure_value_outputN";
  string cmd = findCommand(command, commands);
  if (output_head_Nr < 9) {
    Soutput_head_Nr = Zero + Soutput_head_Nr;
  }
  cmd += Soutput_head_Nr;
  // from hear comes magic  
  // if the buffer is not empty
  if (SERIAL_HANDLERHandler->available() > 0)
  {
    // get it
    Response = SERIAL_HANDLERHandler->readstringUntil('\r');
    //SERIAL_HANDLER.println("buffer already full with: "+Response);
    if (Response.substring(0, 5) == cmd)
    {
      SERIAL_HANDLER.println("full response: " + Response);
      Response.remove(0, 6); //remove default response
      val = Response.toDouble();
      SERIAL_HANDLER.println("filtered response for head: " + Soutput_head_Nr + " equal to: " + Response + " double value: " + val);
      if (val > 0) return val;
    }
    SERIAL_HANDLERHandler->flush();
  }
  SERIAL_HANDLERHandler->print(cmd + CR);
  //SERIAL_HANDLER.println("sending command: "+cmd);
  // because the need of time between cmd and response
  if (millis() - last_time >= 200) //time to send/receive response from 1 head
  {
    if (SERIAL_HANDLERHandler->available() > 0)
    {
      // Read data from rs232 port
      Response = SERIAL_HANDLERHandler->readstringUntil('\r');
      // write the data to the other port
      //MS,OUT01,value CR: remove M->,: 9
      //SERIAL_HANDLER.println("cmd: "+cmd+" Response: "+ Response.substring(0,5));
      if (Response.substring(0, 5) == cmd)
      {
        SERIAL_HANDLER.println("full response: " + Response);
        Response.remove(0, 6); //remove default response
        val = Response.toDouble();
        SERIAL_HANDLER.println("filtered response for head: " + Soutput_head_Nr + " equal to: " + Response + " double value: " + val);
        SERIAL_HANDLERHandler->flush();
        last_time = millis();
        if (val > 0) return val;
      }
    }
  }
}
//get output multiple heads in this format: "0-12" example: head 1,2 and 3 will be 111000000000
double* IkeyenceRS232::getValueMultipleOutputHead(string HeadsArray)
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
  string valuesHolder = "";
  int ValuesCounter = 0;
  SERIAL_HANDLER.println("number of heads");
  SERIAL_HANDLER.println(NumOfOutputs);
  string command = "mesure_value_multipleN";
  string cmd = findCommand(command, commands);
  //cmd:MM,010010000000
  cmd += string(HeadsArray);
  SERIAL_HANDLER.println("command sent:");
  SERIAL_HANDLER.println(cmd);
  SERIAL_HANDLERHandler->println(cmd);
  if (SERIAL_HANDLERHandler->available() > 0)
  {
    // Read data from rs232 port
    string Response = SERIAL_HANDLERHandler->readstringUntil('\r');
#ifdef DEBUG
    // write the data to the other port
    SERIAL_HANDLER.println("response:");
    SERIAL_HANDLER.println(Response);
#endif
    // Response: MM,010010000000,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    SERIAL_HANDLER.println(Response);
    // iterate response and extract values

    for (int i = 0; i < Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if (Response[i] == ',')
      {
        valuesHolder = Response.substring(i + 1, Response.indexOf(',', i + 1));
        SERIAL_HANDLER.println("value holder got");
        SERIAL_HANDLER.println(valuesHolder);
        Values[ValuesCounter] = valuesHolder.toDouble();
        ValuesCounter++;
        valuesHolder = "";
      }
      if (ValuesCounter == NumOfOutputs) break;
    }
    for (int i = 0; i < NumOfOutputs; i++)
    {
      SERIAL_HANDLER.println("extracted values");
      SERIAL_HANDLER.println(*(Values + i));
    }
    return Values;
  }
}
// get output all
double* IkeyenceRS232::getValueOutputHeadAll()
{
  string Response;
  string valuesHolder = "";
  int ValuesCounter = 0;
  //write the get value command
  string cmd;
  //SERIAL_HANDLER.print("number of heads: ");
  //SERIAL_HANDLER.println(HeadsCount);
  ////SERIAL_HANDLER.println("timer: "+string(timer_send_cmd));
  //SERIAL_HANDLER.print("timer: ");
  //SERIAL_HANDLER.println(timer_send_cmd);
  string command = "mesure_value_All";
  //cmd = findCommand(command, commands);
  // speed purpose we skip any loop
  cmd = "MA";
  SERIAL_HANDLERHandler->print(cmd + CR);
  //SERIAL_HANDLER.print("command sent: ");
  //SERIAL_HANDLER.println(cmd+CR);
  if (SERIAL_HANDLERHandler->available() > 0)
  {
    // Read data from rs232 port
    Response = SERIAL_HANDLERHandler->readstringUntil('\r');
    // MA,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    SERIAL_HANDLER.println(Response);
    double* Values = new double[HeadsCount] {0}; //heap
    // iterate response and extract values
    /*for (int i = 0; i < Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if (Response[i] == ',')
      {
        valuesHolder = Response.substring(i + 1, Response.indexOf(',', i + 1));
        //SERIAL_HANDLER.print("value holder got: ");
        //SERIAL_HANDLER.println(valuesHolder.toDouble());
        Values[ValuesCounter] = valuesHolder.toDouble();
        ValuesCounter++;
        //SERIAL_HANDLER.print("extracted values: ");
        //SERIAL_HANDLER.println(*(Values + i));
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
    //SERIAL_HANDLER.println(Values[0]);
    //SERIAL_HANDLER.println(Values[1]);
    //SERIAL_HANDLER.println(Values[2]);
    IkeyenceBase::LookUpValues = Values;
    delete[] Values;
    return IkeyenceBase::LookUpValues;
  }
}

// set general mode
void IkeyenceRS232::setGeneralMode()
{
  //write the get value command
  string command = "set_general_mode";
  string cmd = findCommand(command, commands);
  SERIAL_HANDLERHandler->print(cmd + CR);
  if (SERIAL_HANDLERHandler->available() > 0)
  {
    // Read data from rs232 port
    string Response = SERIAL_HANDLERHandler->readstringUntil('\r');
#ifdef DEBUG_
    // write the data to the other port
    SERIAL_HANDLER.println("response:");
    SERIAL_HANDLER.println(Response);
#endif
  }
}
// set communication mode
void IkeyenceRS232::setCommunicationMode()
{

  //write the get value command
  string command = "set_communication_mode";
  string cmd = findCommand(command, commands);
  SERIAL_HANDLERHandler->print(cmd + CR);
  delay(100); //this delay is obligatory to clear buffer

  if (SERIAL_HANDLERHandler->available() > 0)
  {
    // Read data from rs232 port
    string Response = SERIAL_HANDLERHandler->readstringUntil('\r');
#ifdef DEBUG
    // write the data to the other port
    SERIAL_HANDLER.println("response:");
    SERIAL_HANDLER.println(Response);
#endif
  }
  SERIAL_HANDLERHandler->write("");
  SERIAL_HANDLERHandler->flush();
}

