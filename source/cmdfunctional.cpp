/*!\brief commands functionals implementation
 * \file cmdfunctional.cpp
 * \date May 26, 2023
 * \author Sergey Slyutov
 */

#include "cmdfunctional.h"

#include "textres.h"

#include "windows.h"

#include <bluetoothapis.h>

#include <iostream>

#include <string>

#include <iomanip>

#include <sstream>


std::string SystemTimeToString(const SYSTEMTIME& sysTime)
{
	std::ostringstream oss;

	oss << std::setfill('0');
	oss << std::setw(4) << sysTime.wYear << "-";
	oss << std::setw(2) << sysTime.wMonth << "-";
	oss << std::setw(2) << sysTime.wDay << " ";
	oss << std::setw(2) << sysTime.wHour << ":";
	oss << std::setw(2) << sysTime.wMinute << ":";
	oss << std::setw(2) << sysTime.wSecond;

	return oss.str();
}


std::string ByteArrayToAddressString(const uint8_t* addressBytes, size_t length) {
	std::ostringstream oss;
	for (size_t i = 0; i < length; i++) {
		if (i > 0) {
			oss << ":";
		}
		oss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(addressBytes[i]);
	}
	return oss.str();
}

std::vector<BLUETOOTH_DEVICE_INFO_STRUCT> list_bt_devices()
{
	std::vector<BLUETOOTH_DEVICE_INFO_STRUCT> retvec;

	BLUETOOTH_FIND_RADIO_PARAMS btradioparams;
	btradioparams.dwSize = sizeof(btradioparams);

	HANDLE hradio;
	
	HBLUETOOTH_RADIO_FIND hradiofind = BluetoothFindFirstRadio(&btradioparams, &hradio);
	
	if (hradiofind == NULL || hradio == NULL) {
		return retvec;
	}

	BLUETOOTH_DEVICE_SEARCH_PARAMS devsearch;
	devsearch.dwSize = sizeof(devsearch);
	devsearch.fIssueInquiry = true;
	devsearch.fReturnAuthenticated = true;
	devsearch.fReturnConnected = true;
	devsearch.fReturnRemembered = true;
	devsearch.fReturnUnknown = true;
	devsearch.cTimeoutMultiplier = 1;

	devsearch.hRadio = hradio;

	BLUETOOTH_DEVICE_INFO_STRUCT devinfo;
	devinfo.dwSize = sizeof(devinfo);

	HBLUETOOTH_DEVICE_FIND hdevfind = BluetoothFindFirstDevice(&devsearch, &devinfo);

	if (hdevfind == NULL) {
		CloseHandle(hradio);
		return retvec;
	}

	std::cout << "select\taddress\t\t\tname" << std::endl;

	int selindex = 0;
	

	while (hdevfind) {

		retvec.push_back(devinfo);
		

		std::cout << selindex;

		std::string straddr = ByteArrayToAddressString(devinfo.Address.rgBytes, sizeof(devinfo.Address.rgBytes));

		std::cout << "\t" << straddr;

		std::wcout << "\t" << devinfo.szName << std::endl;

		std::cout << "\t\tClassOfDevice - " << devinfo.ulClassofDevice << std::endl; //  Bluetooth "Class of Device"
		std::cout << "\t\tConnected     - " << devinfo.fConnected << std::endl;      //  Device connected/in use
		std::cout << "\t\tRemembered    - " << devinfo.fRemembered << std::endl;     //  Device remembered
		std::cout << "\t\tAuthenticated - " << devinfo.fAuthenticated << std::endl;  //  Device authenticated/paired/bonded
		std::cout << "\t\tLastSeen      - " << SystemTimeToString(devinfo.stLastSeen) << std::endl;      //  Last time the device was seen
		std::cout << "\t\tLastUsed      - " << SystemTimeToString(devinfo.stLastUsed) << std::endl;      //  Last time the device was used for other than RNR, inquiry, or SDP

		if (!BluetoothFindNextDevice(hdevfind, &devinfo))
			break;
		selindex++;
	}

	if(hdevfind)
		BluetoothFindDeviceClose(hdevfind);

	CloseHandle(hradio);

	BluetoothFindRadioClose(hradiofind);

	return retvec;
};

std::vector<BLUETOOTH_RADIO_INFO> list_bt_radios()
{
	std::vector<BLUETOOTH_RADIO_INFO> retlist;

	BLUETOOTH_FIND_RADIO_PARAMS btradioparams;
	btradioparams.dwSize = sizeof(btradioparams);

	HANDLE hRadio;
	HBLUETOOTH_RADIO_FIND hfind = BluetoothFindFirstRadio(&btradioparams, &hRadio);

	while (hfind) {

		BLUETOOTH_RADIO_INFO radioInfo;
		radioInfo.dwSize = sizeof(radioInfo);
		DWORD dwres = BluetoothGetRadioInfo(hRadio, &radioInfo);

		if (dwres == ERROR_SUCCESS) {


			retlist.push_back(radioInfo);

			std::string strBtAddr = ByteArrayToAddressString(radioInfo.address.rgBytes, sizeof(radioInfo.address.rgBytes));

			std::cout << "address: " << strBtAddr << std::endl;

			if (mapBluetoothManufactures().contains(radioInfo.manufacturer))
				std::cout << "manufacturer: " << mapBluetoothManufactures()[radioInfo.manufacturer] << std::endl;
			else
				std::cout << "manufacturer: " << "unknown" << std::endl;


			std::wcout << "name: " << radioInfo.szName << std::endl;

			std::cout << "connectable: ";
			if (BluetoothIsConnectable(hRadio))
				std::cout << "yes" << std::endl;
			else
				std::cout << "no" << std::endl;
		}

		CloseHandle(hRadio);
		if (hfind){
			if (!BluetoothFindNextRadio(hfind, &hRadio))
				break;
		}else{
			break;
		}
	}
	BluetoothFindRadioClose(hfind);

	return retlist;
};


void add_bth_device()
{
	BLUETOOTH_SELECT_DEVICE_PARAMS params;
	memset(&params, 0, sizeof(params));
	params.dwSize = sizeof(params);
	params.fAddNewDeviceWizard = true;
	params.fForceAuthentication = true;
	params.fShowAuthenticated = true;
	params.fShowRemembered = true;
	params.fShowUnknown = true;
	params.fSkipServicesPage = true;
	params.hwndParent = NULL;
	BLUETOOTH_DEVICE_INFO bthdevinfo;
	params.pDevices = &bthdevinfo;
	
	BluetoothSelectDevices(&params);

	BluetoothSelectDevicesFree(&params);

};

void remove_device()
{
	std::vector<BLUETOOTH_DEVICE_INFO_STRUCT> bth_devs = list_bt_devices();
	
	std::string strinput;

	std::cin >> strinput;

	int selected_index = std::stoi(strinput);

	if (bth_devs.size() > selected_index) {

		DWORD dwres = BluetoothRemoveDevice(&bth_devs[selected_index].Address);

		if (dwres == ERROR_SUCCESS) {
			std::cout << "remote device ";
			std::cout << ByteArrayToAddressString(bth_devs[selected_index].Address.rgBytes, sizeof(bth_devs[selected_index].Address.rgBytes));
			std::cout << " has been successfully removed" << std::endl;
		}else{
			std::cout << "remote device ";
			std::cout << ByteArrayToAddressString(bth_devs[selected_index].Address.rgBytes, sizeof(bth_devs[selected_index].Address.rgBytes));
			std::cout << " has not been removed" << std::endl;

		}
	}


	//DWORD BluetoothRemoveDevice(const BLUETOOTH_ADDRESS * pAddress);



}

