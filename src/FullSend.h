#ifndef FULL_SEND_H
#define FULL_SEND_H

#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>

#define WIN32_LEAN_AND_MEAN
#include <stdlib.h>
#include <iostream>
#include <winsock2.h>
//#include <ws2tcpip.h>

#include "Decode.h"


#define CRLF "\r\n"                 // carriage-return/line feed pair

#define EMAIL "@gmail.com"

#define WAIT_TIME 180000
#define SEND_TIME 60000

bool sendData(char * file_name);
bool testConnection();
bool sendEmail(char * file_name);
void Check(int iStatus, char *szFunction);

#endif