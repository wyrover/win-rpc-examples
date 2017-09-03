// RpcClient.cpp: 显式绑定模式服务程序.
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
    // 使用与端点相结合的协议接收远过程调用.
    if (RpcServerUseProtseqEp(
            (unsigned char*)("ncacn_np"),      // 使用named pipe.
            RPC_C_PROTSEQ_MAX_REQS_DEFAULT,    // 积压对列长度.
            (unsigned char*)("\\pipe\\hello"), // named pipe端口.
            NULL)) {                           // 无安全防护.
        return (1);
    }

    // 注册RpcExplicit接口.
    if (RpcServerRegisterIf(
            RpcExplicit_v1_0_s_ifspec,      // 用于注册的接口.
            NULL,                           // 使用MIDL 产生入口点向量.
            NULL)) {                        // 使用MIDL 产生入口点向量.
        return (1);
    }

    // 开始侦听对注册接口的远程过程调用.
    // 此调用在调用RpcMgmtStopServerListening 前不返回.
    if (RpcServerListen(
            1,                              // 最小线程数目.
            RPC_C_LISTEN_MAX_CALLS_DEFAULT, // 最大线程数目.
            FALSE)) {                       // 开始侦听.
        return (1);
    }

    return (0);
}
