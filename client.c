#include <userint.h>
#include <ansi_c.h>
#include <tcpsupp.h>
#include <cvirte.h>

#define SERVER_PORT 26845  
#define HELLO_TEXT "Hello,I'm client."
int convHandle;

int CVICALLBACK ClientCallback(unsigned int handle,int event,int error,void* callbackData)
{
    char ss[512];
    int rdSize=512;
    switch(event)
    {
        case TCP_DATAREADY:    //�յ�����
            if((rdSize=ClientTCPRead(convHandle,ss,rdSize,2000))<0)
                printf("Acquire data failed!\n");
            else 
                printf("Recv data:%s",ss);
            break;
        case TCP_DISCONNECT:   //�Ͽ�����
            printf("Connection %d disconnected!\n",convHandle);
            break;
    }
    return 0;
}

int main (int argc, char *argv[])
{
    if(ConnectToTCPServer(&convHandle,SERVER_PORT,"127.0.0.1",ClientCallback,0,2000)<0)
        return 0;
    else
        printf("Connect to server success!\n");
    ClientTCPWrite(convHandle,HELLO_TEXT,strlen(HELLO_TEXT)+1,2000);
    printf("HELLO_TEXT has been sent.\n");
    RunUserInterface();       //��ֹ�������е��˴�֮���˳�
    DisconnectFromTCPServer(convHandle);
    return 0;
} 
