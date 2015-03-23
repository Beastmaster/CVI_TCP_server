#include <ansi_c.h>		//CVI_headfile
#include <tcpsupp.h>	// CVI_headfile
#include <userint.h>	//CVI_headfile
#include <cvirte.h>		//CVI_headfile
#define SERVER_PORT 26845

int convHandle=0;

int CVICALLBACK ServerCall(unsigned int handle,int event, int error,void* callbackData)
{
    char ss[512];
    int rdSize=0;
    switch(event)
    {
        case TCP_CONNECT:    //��������
            convHandle=handle;
            printf("Connection %d established!\n",handle);
            break;
        case TCP_DISCONNECT:
            convHandle=0;    //�Ͽ�����
            printf("Connection %d disconnected!\n",handle);
            break;
        case TCP_DATAREADY:  //�յ�����
            if((rdSize=ServerTCPRead(convHandle,ss,512,2000))<0)
                printf("Acquire data failed!\n");
            else 
            {
                printf("Recv data:%s\n",ss);
                if(ServerTCPWrite(convHandle,"OK",3,2000)<0)
                    printf("Write OK failed.\n");
            }
            break;
    }
    return 0;
}

int main (int argc, char *argv[])
{
    if(RegisterTCPServer(SERVER_PORT,ServerCall,0)<0)
        return 0;
    else
        printf("Server Running!\n");
    RunUserInterface();       //��ֹ�������е��˴�֮���˳�
    UnregisterTCPServer(SERVER_PORT);
    return 0;
}
