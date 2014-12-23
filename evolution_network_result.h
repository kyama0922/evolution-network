#ifndef __EVOLUTION_NETWORK_RESULT_H__
#define __EVOLUTION_NETWORK_RESULT_H__


namespace EVOLUTION{
    namespace NETWORK{

        struct NetworkResult{
            enum _RESULT{
                //----------------------------成功----------------------------
                RESULT_OK = 0x00000000,//成功

                //----------------------------失敗----------------------------
                UNKNOWN_FAILED = 0x80000000, //失敗
                NONE_INSTANCE,               //インスタンスがありません
                CREATE_FAILED,               //作成に失敗
                GET_IPADDR_FAILED,           //IPアドレスの取得に失敗
            };

        };
    }
}

#endif // !__EVOLUTION_NETWORK_RESULT_H__