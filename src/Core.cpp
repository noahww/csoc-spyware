#include "Core.h"

using namespace std;

main() {
    while ( 1 ) {
        future<char *> keys = async(logKey);
        char * file_name = keys.get();
    }
}