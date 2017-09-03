// RpcClient.cpp: 显式绑定模式客户程序.
//
#include <iostream>
#include <stdio.h>
#include "RpcExplicit_h.h"
#include "RpcExplicit_c.c"
#include "memstub.h"

#pragma comment(lib,"rpcns4.lib")
#pragma comment(lib,"rpcrt4.lib")

using namespace std;

int main()
{
    unsigned char* pszStringBinding = NULL;

    // 创建一个字符串绑定句柄.这里不进行连接.
    if (RpcStringBindingCompose(
            NULL,                              // 用于绑定的UUID.
            (unsigned char*)("ncacn_np"),      // 使用named pipe.
            (unsigned char*)NULL,              // 网络地址.
            (unsigned char*)("\\pipe\\hello"), // named pipe端口.
            NULL,                              // 使用依赖网络的协议.
            &pszStringBinding)) {              // 字符串绑定输出.
        return (1);
    }

    handle_t hRpcExplicitBinding = NULL;

    // 确认字符串绑定句柄的格式并把它传换成一个绑定句柄.
    // 这里也不进行连接.
    if (RpcBindingFromStringBinding(
            pszStringBinding,   &hRpcExplicitBinding)) {
        return (1);
    }

    RpcTryExcept {
        char str[40] = "Hello RPC World from RpcExplicitc!";

        // 调用 RPC 函数,显式地使用绑定句柄 hRpcExplicitBinding.
        // 这里进行连接.
        RpcStringProc(hRpcExplicitBinding, (unsigned char*)str);

        // 返回的结果.
        cout << str << endl;

        // 暂停.
        getchar();
    }
    RpcExcept(1) {
        cerr << "Runtime reported exception:" << RpcExceptionCode() << endl;
    }
    RpcEndExcept

    // 调用远程过程完成,释放字符串和绑定句柄.
    if (RpcStringFree(&pszStringBinding)) {
        return (1);
    }

    // 释放绑定句柄资源并与服务程序断开.
    if (RpcBindingFree(&hRpcExplicitBinding)) {
        return (1);
    }

    return (0);
}