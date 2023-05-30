/*!\brief test resources of btrider application 
* \file textres.h
* \author Sergey Slyutov
* \date May 26, 2023
*/

#ifndef _TEXTRES_H

#define _TEXTRES_H

#include <windows.h>

#include <string>

#include <functional>

#include "cmdfunctional.h"

#include "bthdef.h"

#include <map>

#include "cmddata.h"

//const std::string cmd_ListRadios = "list_radios";
//const std::string cmd_ListDevices = "list_devices";
//const std::string cmd_SelectDevices = "select_devices";
//
//const std::map<std::string, std::function<void()>> commands =
//{
//	{cmd_ListRadios, list_bt_radios}
//	,{cmd_ListDevices, list_bt_devices}
//	,{cmd_SelectDevices, add_bth_device}
//};

const std::string welcomePrompt = "Bluetooth rider. 2023 (by Sergey Slyutov)\n\
obtain information and manipulate BT devices\n\
\tcommand:\n\n\
\t\t" + cmd_ListDevices + " - list of remote devices\n\
\t\t" + cmd_ListRadios + " - list of local radio\n\
\t\t" + cmd_SelectDevices + " - UI allow to pair a remote device\n\
\t\t" + cmd_removeDevice + " - remove paired remote device and clears cache\n\n\
\t example: btrider.exe select_devices\n";






std::map<short, std::string>& mapBluetoothManufactures();

//const std::string rootCommands = "select remote device\n";


#endif