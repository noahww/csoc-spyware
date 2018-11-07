#ifndef FULL_SEND_H
#define FULL_SEND_H


#undef _WINSOCKAPI_
#define _WINSOCKAPI_
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>

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