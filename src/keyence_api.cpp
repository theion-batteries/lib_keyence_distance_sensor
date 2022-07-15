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
//init the com with keyence

void IkeyenceRS232::initKeyenceCom()
{
  KEYENCE_SERIAL_HANDLER.begin(KEYENCE_SERIAL_BAUDRATE);
}

void IkeyenceRS232::sendCmd(const string& cmd, Stream& streamPort)
{
  streamPort.println(cmd);
}

//get a output value of single head: head number format is 01,02,03... but param is given as int 1,2,3...
double IkeyenceRS232::getValueSingleOutputHead(int output_head_Nr)
{
  string Zero = "0";
  string Response;
  double val=0;
  // head specific parameters
  string Soutput_head_Nr = string(output_head_Nr);
  //write the get value command
  string command = "mesure_value_outputN";
  string cmd=findCommand(command, commands);
  if (output_head_Nr < 9) {
    Soutput_head_Nr = Zero + Soutput_head_Nr;
  }
  // cmd=MS,01
  cmd += Soutput_head_Nr;
  string cmdToSend=cmd+CR;
  sendCmd(cmdToSend,KEYENCE_SERIAL_HANDLER);
  if (KEYENCE_SERIAL_HANDLER.available() > 0)
  {
    // get the response
    Response = KEYENCE_SERIAL_HANDLER.readStringUntil('\r');
    if (Response.substring(0, 5) == cmd)
    {
      USB_SERIAL.println("full response: " + Response);
      Response.remove(0, 6); //remove default response
      val = Response.toDouble();
    }
  }
    if (val == 0xFFFF || val ==0xFFFFFFFF)
    {
      USB_SERIAL.println("out of range value");
      return lastValue;
    }
    else
    {
      if(val==0){USB_SERIAL.println("no value"); return lastValue;}
      else{
      USB_SERIAL.println("filtered response for head: " + Soutput_head_Nr + " equal to: " +val);
      lastValue = val;
      return val;
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
  double Values[NUM_OUTPUT_HEADS];
  string valuesHolder = "";
  int ValuesCounter = 0;
  USB_SERIAL.println("number of heads");
  USB_SERIAL.println(NumOfOutputs);
  string command = "mesure_value_multipleN";
  string cmd = findCommand(command, commands);
  //cmd:MM,010010000000
  cmd += string(HeadsArray);
  USB_SERIAL.println("command sent:");
  USB_SERIAL.println(cmd);
  USB_SERIAL.println(cmd);
  sendCmd(cmd,KEYENCE_SERIAL_HANDLER);
  if (KEYENCE_SERIAL_HANDLER.available() > 0)
  {
    // Read data from rs232 port
    string Response = KEYENCE_SERIAL_HANDLER.readStringUntil('\r');
    // Response: MM,010010000000,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    USB_SERIAL.println(Response);
    // iterate response and extract values
    for (int i = 0; i < Response.length();i++)
    {// ,val1,val2,val3,val4,val5
      if (Response[i] == ',')
      {
        valuesHolder = Response.substring(i + 1, Response.indexOf(',', i + 1));
        USB_SERIAL.println("value holder got");
        USB_SERIAL.println(valuesHolder);
        Values[ValuesCounter] = valuesHolder.toDouble();
        ValuesCounter++;
        valuesHolder = "";
      }
      if (ValuesCounter == NumOfOutputs) break;
    }
    for (int i = 0; i < NumOfOutputs; i++)
    {
      USB_SERIAL.println("extracted values");
      USB_SERIAL.println(*(Values + i));
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
  string cmd;
  string command = "mesure_value_All";
  cmd = findCommand(command, commands);
  // speed purpose we skip any loop
  //cmd = "MA";
  KEYENCE_SERIAL_HANDLER.print(cmd + CR);
  if (KEYENCE_SERIAL_HANDLER.available() > 0)
  {
    // Read data from rs232 port
    Response = KEYENCE_SERIAL_HANDLER.readStringUntil('\r');
    // MA,value[,value,value]: 
    Response.replace(cmd, ""); //remove default response
    USB_SERIAL.println(Response);
    double Values[NUM_OUTPUT_HEADS];
    // try to gte rid of any loop that slow down the main loop
    // as we know that we use three heads, we can just add the index
    int first_occurance=Response.indexOf(',', 0);
    int second_occurance=Response.indexOf(',', first_occurance+1);
    int third_occurance=Response.indexOf(',',second_occurance+1);
    Values[0] = Response.substring(first_occurance+1,second_occurance+1).toDouble();
    Values[1] = Response.substring(second_occurance+1,third_occurance+1).toDouble();
    Values[2] = Response.substring(third_occurance+1,Response.length()).toDouble();
    return Values;
  }
}

// set general mode
void IkeyenceRS232::setGeneralMode()
{
  //write the get value command
  string command = "set_general_mode";
  string cmd = findCommand(command, commands);
  KEYENCE_SERIAL_HANDLER.print(cmd + CR);
  if (KEYENCE_SERIAL_HANDLER.available() > 0)
  {
    // Read data from rs232 port
    string Response = KEYENCE_SERIAL_HANDLER.readStringUntil('\r');
#ifdef DEBUG_
    // write the data to the other port
    USB_SERIAL.println("response:");
    USB_SERIAL.println(Response);
#endif
  }
}
// set communication mode
void IkeyenceRS232::setCommunicationMode()
{

  //write the get value command
  string command = "set_communication_mode";
  string cmd = findCommand(command, commands);
  KEYENCE_SERIAL_HANDLER.print(cmd + CR);
  delay(100); //this delay is obligatory to clear buffer

  if (KEYENCE_SERIAL_HANDLER.available() > 0)
  {
    // Read data from rs232 port
    string Response = KEYENCE_SERIAL_HANDLER.readStringUntil('\r');
#ifdef DEBUG
    // write the data to the other port
    USB_SERIAL.println("response:");
    USB_SERIAL.println(Response);
#endif
  }
  KEYENCE_SERIAL_HANDLER.write("");
  KEYENCE_SERIAL_HANDLER.flush();
}

