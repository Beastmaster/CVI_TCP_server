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
        case TCP_DATAREADY:    //收到数据
            if((rdSize=ClientTCPRead(convHandle,ss,rdSize,2000))<0)
                printf("Acquire data failed!\n");
            else 
                printf("Recv data:%s",ss);
            break;
        case TCP_DISCONNECT:   //断开连接
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
    RunUserInterface();       //防止程序运行到此处之后退出
    DisconnectFromTCPServer(convHandle);
    return 0;
} 
