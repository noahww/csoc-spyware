#ifndef DECODE_H
#define DECODE_H

#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>


#define INPUT_FILE_NAME "Record.log"
#define OUTPUT_FILE_NAME "Data.log"


char * decode(char * file_name);
char * decodeInt(int i);

#endif