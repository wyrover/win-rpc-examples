// RpcClient.cpp: ��ʽ��ģʽ�������.
//
#include <iostream>
#include "RpcExplicit_h.h"
#include "Rpcexplicit_s.c"
#include "memstub.h"

#pragma comment(lib,"rpcns4.lib")
#pragma comment(lib,"rpcrt4.lib")

using namespace std;


void RpcStringProc(handle_t hBinding, unsigned char * pszString)
{
    cout << pszString << endl;
    strcpy((char*)pszString, "Calling RpcExplicits Successful!");
}


int main()
{
    // ʹ����˵����ϵ�Э�����Զ���̵���.
    if (RpcServerUseProtseqEp(
            (unsigned char*)("ncacn_np"),      // ʹ��named pipe.
            RPC_C_PROTSEQ_MAX_REQS_DEFAULT,    // ��ѹ���г���.
            (unsigned char*)("\\pipe\\hello"), // named pipe�˿�.
            NULL)) {                           // �ް�ȫ����.
        return (1);
    }

    // ע��RpcExplicit�ӿ�.
    if (RpcServerRegisterIf(
            RpcExplicit_v1_0_s_ifspec,      // ����ע��Ľӿ�.
            NULL,                           // ʹ��MIDL ������ڵ�����.
            NULL)) {                        // ʹ��MIDL ������ڵ�����.
        return (1);
    }

    // ��ʼ������ע��ӿڵ�Զ�̹��̵���.
    // �˵����ڵ���RpcMgmtStopServerListening ǰ������.
    if (RpcServerListen(
            1,                              // ��С�߳���Ŀ.
            RPC_C_LISTEN_MAX_CALLS_DEFAULT, // ����߳���Ŀ.
            FALSE)) {                       // ��ʼ����.
        return (1);
    }

    return (0);
}
