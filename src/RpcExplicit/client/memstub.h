// memstub.h:�ڴ����/�ͷ�.
//
// Ϊ�������������ַ���,�� runtime ʹ���������������з���/�ͷ��㹻���ڴ�.
// RPC�ڴ���亯��.
void* __RPC_USER midl_user_allocate(size_t size)
{
    return malloc(size);
}

// RPC�ڴ������ͷź���.
void __RPC_USER midl_user_free(void* p)
{
    free(p);
}
