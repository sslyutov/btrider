/*!\ research project for blutooth libraries on Windows 
* \file main.cpp
* \author Sergey Slyutov
* \date May 26, 2023
*/

#include <iostream>

#include "textres.h"

#include "cmddata.h"

#include <bluetoothapis.h>

int main(int argc, char* argv[])
{
	std::cout << welcomePrompt;

	if (argc == 2) {

		for (auto cmdDescr : commands) {

			if (cmdDescr.first.compare(argv[1]) == 0) {

				cmdDescr.second(); // call the handle of the command

			}
		}
	}

	return 0;
}