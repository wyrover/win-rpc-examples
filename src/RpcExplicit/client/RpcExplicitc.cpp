// RpcClient.cpp: ��ʽ��ģʽ�ͻ�����.
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

    // ����һ���ַ����󶨾��.���ﲻ��������.
    if (RpcStringBindingCompose(
            NULL,                              // ���ڰ󶨵�UUID.
            (unsigned char*)("ncacn_np"),      // ʹ��named pipe.
            (unsigned char*)NULL,              // �����ַ.
            (unsigned char*)("\\pipe\\hello"), // named pipe�˿�.
            NULL,                              // ʹ�����������Э��.
            &pszStringBinding)) {              // �ַ��������.
        return (1);
    }

    handle_t hRpcExplicitBinding = NULL;

    // ȷ���ַ����󶨾���ĸ�ʽ������������һ���󶨾��.
    // ����Ҳ����������.
    if (RpcBindingFromStringBinding(
            pszStringBinding,   &hRpcExplicitBinding)) {
        return (1);
    }

    RpcTryExcept {
        char str[40] = "Hello RPC World from RpcExplicitc!";

        // ���� RPC ����,��ʽ��ʹ�ð󶨾�� hRpcExplicitBinding.
        // �����������.
        RpcStringProc(hRpcExplicitBinding, (unsigned char*)str);

        // ���صĽ��.
        cout << str << endl;

        // ��ͣ.
        getchar();
    }
    RpcExcept(1) {
        cerr << "Runtime reported exception:" << RpcExceptionCode() << endl;
    }
    RpcEndExcept

    // ����Զ�̹������,�ͷ��ַ����Ͱ󶨾��.
    if (RpcStringFree(&pszStringBinding)) {
        return (1);
    }

    // �ͷŰ󶨾����Դ����������Ͽ�.
    if (RpcBindingFree(&hRpcExplicitBinding)) {
        return (1);
    }

    return (0);
}