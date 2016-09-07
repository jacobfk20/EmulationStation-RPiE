#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// variables
std::string password;
std::string ssid;



int main(int argc, const char *argv[]){
	// Get ssid and password from arguments
	for (int i = 1; i < argc; i++){
		if(strcmp(argv[i], "--ssid") == 0){
			printf(argv[i + 1]);
			ssid = argv[i + 1];
		}

		if(strcmp(argv[i], "--password") == 0){
			password = argv[i + 1];
		}
	}

	// check and make sure ssid is valid
	if (ssid.length() < 1) return -1;

	// open wpa_supplicant
	std::ofstream wpaFile;
	wpaFile.open("/etc/wpa_supplicant/wpa_supplicant.conf", std::ofstream::app);

	if (wpaFile.is_open()){
		printf("\nOpened!");

		// Write new ssid and psk to file
		wpaFile << "\n";
		wpaFile << "# WIFIGUI SETUP \n";
		wpaFile << "network={\n";
		wpaFile << "     ssid=\"" << ssid << "\"\n";
		wpaFile << "     psk=\"" << password << "\"\n";
		wpaFile << "}\n";
		wpaFile << "# END SETUP";

		wpaFile.close();

		// Force wlan0 reset
		system("sudo ifup --force wlan0");

		return 1;
	}
	else{
		return -2;
	}
}
