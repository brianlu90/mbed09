#include "mbed.h"
#include "mbed_rpc.h"

/**
 *  This example program has been updated to use the RPC implementation in the new mbed libraries.
 *  This example demonstrates using RPC over serial
**/
RpcDigitalOut myled1(LED1,"myled1");
RpcDigitalOut myled2(LED2,"myled2");
RpcDigitalOut myled3(LED3,"myled3");
DigitalOut myLED3(LED3);
BufferedSerial pc(USBTX, USBRX);
void LEDBlink(Arguments *in, Reply *out);
RPCFunction rpcLED(&LEDBlink, "LEDBlink");
int x = 0;

int main() {
    //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class

    // receive commands, and send back the responses
    char buf[256], outbuf[256];

    FILE *devin = fdopen(&pc, "r");
    FILE *devout = fdopen(&pc, "w");
    char strings[30] = "/LEDBlink/run\n";

    strcpy(buf, strings);
    while(1) {
        RPC::call(buf, outbuf);
        printf("%s\r\n", outbuf);
        ThisThread::sleep_for(500ms);
    }
}

// Make sure the method takes in Arguments and Reply objects.
void LEDBlink (Arguments *in, Reply *out)   {
    //bool success = true;
    x++;

    // Have code here to call another RPC function to wake up specific led or close it.
    //char buffer[200], outbuf[256];
    char strings[20];
    /*int led = 3;
    if (x % 2) {
        sprintf(strings, "/myled%d/write %d", led, 1);
    } else {
        sprintf(strings, "/myled%d/write %d", led, 0);
    }
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED control.");
    }*/
    if (x % 2) {
        myLED3 = 0;
        sprintf(strings, "/myled%d/write %d", 3, 0);
    } else {
        myLED3 = 1;
        sprintf(strings, "/myled%d/write %d", 3, 1);
    }
    out->putData(strings);
}