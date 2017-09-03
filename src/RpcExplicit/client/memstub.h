// memstub.h:内存分配/释放.
//
// 为了向服务程序发送字符串,此 runtime 使用这两个函数进行分配/释放足够的内存.
// RPC内存分配函数.
void* __RPC_USER midl_user_allocate(size_t size)
{
    return malloc(size);
}

// RPC内存分配的释放函数.
void __RPC_USER midl_user_free(void* p)
{
    free(p);
}
