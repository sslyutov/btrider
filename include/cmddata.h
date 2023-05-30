/*!\brief database describing commands relations with other components of the application
 * \file cmddata.h
 * \date May 26, 2023
 * \author Sergey Slyutov
 */

#ifndef _CMDDATA_H

#define _CMDDATA_H

#include <functional>

#include "cmdfunctional.h"

const std::string cmd_ListDevices	= "list_devices";
const std::string cmd_ListRadios	= "list_radios";
const std::string cmd_SelectDevices = "select_devices";
const std::string cmd_removeDevice	= "remove_device";

const std::map<std::string, const std::function<void()>> commands =
{
	 {cmd_ListDevices,		list_bt_devices}
	,{cmd_ListRadios,		list_bt_radios}
	,{cmd_SelectDevices,	add_bth_device}
	,{cmd_removeDevice,		remove_device}
};


#endif // _CMDDATA_H