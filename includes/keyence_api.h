/**
   @file keyence_api.h
   @author sami dhiab (sami@theion.de)
   @brief keyence sensors APIs
   @version 0.1
   @date 2022-04-06

   @copyright Copyright (c) 2022

*/
#pragma once
#include <map>
#include <vector>
#include <string>

/*** layout pins ***/
/*
5V  ------> VCC
GND ------> GND
RX3 ------> RxOut
TX3 ------> TxIn
 */


#define LF '\n' //assume next line or Line Feed used
#define cr '\r' //assume carriage return is \r otherwise
 /***** rs232 basic device commands ****/
 /*
 * the commands must be sent to the device using CR as delimeter,
 * and the response must be received also with CR.
 * the controller (arduino) must send one command and wait for
 * the response to send next one.
 * General Mode: During measurement The measurement control commands are accepted.
 Commands such as writing/reading setting values are not accepted
 * Communication Mode: • When the command "Q" "0" "CR" is received, the mode changes to
 the communication mode, and the setting values are written/read.
 • The measurement stops during the communication mode.
 * command | description | Mode | response | ERROR
 --------------------------------------------------------------------------
 * Q0 CR | Changing to the communication mode  | communication |  same as command  | Err-51
 --------------------------------------------------------------------------
 * R0 CR | Changing to the general mode | general | same as command  | ERROR
 --------------------------------------------------------------------------
 * MS,01 CR | Measured value output (single) 01-12 | General | MS,OUT01,value CR | ERROR
 --------------------------------------------------------------------------
 --------------------------------------------------------------------------
 * MM,010010000000 CR | Measured value output (multiple) 01-12 ex here out2 and out5| General | MM,010010000000,value[,value,value] CR | ERROR
 --------------------------------------------------------------------------
 * MA CR | Measured value output (all) 01-12| General | MA,value[,value,value] CR | ERROR
 --------------------------------------------------------------------------
 * Timing Diagrams
 * t: time between receiving command and responding: process time
 * Mesrument/control PW: 100ms + number of heads x 100ms : if one head: 200ms if 3 heads 100ms +3*100=400ms
 * Mode Change to General: 600 ms + Number of head expansion units x 750 ms = 600+3*750 = 2850 ms
 * Error Code
 • 50: Command error
 • 51: Status error
 • 60: Command length error
 • 61: Parameter count error
 • 62: Parameter range error
 • 88: Timeout error
 • 99: Other error
 */
namespace keyence
{
   class IkeyenceBase
   {
   protected:
      // mesured Values Array
      double MesuredValues;
      // single value
      double lastValue = 0;
   public:
      // Array of Raw Commands
      const char* RawCommands[9] = { "Q0","R0","MS,","MS,01","MS,02","MS,03","MM,1110000000000","MM,","MA" };
      // map of command std::strings to raw commands +CR
      std::map<const char*, const char*> commands{
      {"set_communication_mode",RawCommands[0]},
      {"set_general_mode",RawCommands[1]},
      {"mesure_value_outputN",RawCommands[2]},
      {"mesure_value_output1",RawCommands[3]},
      {"mesure_value_output2",RawCommands[4]},
      {"mesure_value_output3",RawCommands[5]},
      {"mesure_value_multiple123",RawCommands[6]},
      {"mesure_value_multipleN",RawCommands[7]},
      {"mesure_value_All",RawCommands[8]},
      };
      // helper func to find commands
      const char* findCommand(const char* command, std::map<const char*, const char*>& CommandMap);
      //get a output value of single head
      virtual double getValueSingleOutputHead(int output_head_Nr) = 0;
      //get output multiple heads
      virtual double* getValueMultipleOutputHead(const char* HeadsArray) = 0;
      // get output all
      virtual double* getValueOutputHeadAll() = 0;
      // set general mode
      virtual void setGeneralMode() = 0;
      // set communication mode
      virtual void setCommunicationMode() = 0;
      // init communication
      virtual void initKeyenceCom() = 0;
      // send cmd to custom cmd
      virtual void sendCmd(const char* cmd)=0;
      // process received msg from sensor controll driver
      virtual double processResponse();
   };
} // namespace keyence


