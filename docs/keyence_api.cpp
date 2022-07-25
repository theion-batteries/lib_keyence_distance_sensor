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
namespace keyence
{
  std::string IkeyenceBase::findCommand(std::string& command, std::map<std::string, std::string>& CommandMap)
  {
    for (auto it = CommandMap.begin(); it != CommandMap.end(); ++it)
    {
      if ((*it).first == command)
      {
        return (*it).second;
      }
    }
  }
} // namespace keyence
