/*!\brief commands functionals implementation
 * \file cmdfunctional.h
 * \date May 26, 2023
 * \author Sergey Slyutov
 */

#ifndef _CMDFUNCTIONAL_H

#define _CMDFUNCTIONAL_H

#include <windows.h>

#include <string>

#include <list>

//#include <bluetoothleapis.h>
//
#include <bluetoothapis.h>

#include <vector>

//
//#include <windows.devices.bluetooth.h>

std::string SystemTimeToString(const SYSTEMTIME& sysTime);

std::string ByteArrayToAddressString(const uint8_t* addressBytes, size_t length);

std::vector<BLUETOOTH_DEVICE_INFO_STRUCT> list_bt_devices();

std::vector<BLUETOOTH_RADIO_INFO> list_bt_radios();

// add/pair bluetooth device 
void add_bth_device();

// unpair bluetooth device
void remove_device();

#endif //_CMDFUNCTIONAL_H

