#ifndef __EVOLUTION_NETWORK_RPC_INTERFACE_H_
#define __EVOLUTION_NETWORK_RPC_INTERFACE_H_

#include "evolution_network_interface.h"

namespace EVOLUTION{
    namespace NETWORK{

        //RPCID
        typedef u64 RPCID;

        //RPCレイアウト
        struct RPC_LAYOUT_TYPE{
            enum _TYPE{
                _BOOL,
                _SINT8,
                _SINT16,
                _SINT32,
                _SINT64,
                _UINT8,
                _UINT16,
                _UINT32,
                _UINT64,
                _F32,
                _F64,
                _SINT8_ARRAY,
                _SINT16_ARRAY,
                _SINT32_ARRAY,
                _SINT64_ARRAY,
                _UINT8_ARRAY,
                _UINT16_ARRAY,
                _UINT32_ARRAY,
                _UINT64_ARRAY,
                _F32_ARRAY,
                _F64_ARRAY,
                _ORDER,
            };
        };

        /*
        */
        struct RPC_LAYOUT{
            //RPCバッファのレイアウト
            RPC_LAYOUT_TYPE::_TYPE type;
            //配列指定し場合のみ有効
            s32 ArrayCount;
            //RPC_LAYOUT_TYPE::_ORDERのみ有効
            s32 order_size;
        };

        //
        class IRPCProtocol : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IRPCProtocol);
        public:
            virtual RPCID RpcID()const = 0;
            virtual u32 GetBufferSize()const = 0;
            virtual u32 GetLayoutCount() = 0;
            virtual const RPC_LAYOUT* GetLayout()const = 0;

            virtual void SetOrderBuffer(s32 index, u8* buffer, s32 len) = 0;
            virtual void SetBuffer(s32 index, u8* buffer, RPC_LAYOUT_TYPE::_TYPE type, s32 array_size = 0) = 0;

            virtual const void* GetOrderBuffer(s32 index, s32 len)const = 0;
            virtual const void* GetBuffer(s32 index, RPC_LAYOUT_TYPE::_TYPE type, s32 array_size = 0)const = 0;
        };


        //
        class ITCPRPCController : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(ITCPRPCController);
        public:
            virtual NetworkResult::_RESULT AddRPCProtocol(IRPCProtocol* rpc_protocol) = 0;
            virtual NetworkResult::_RESULT DelRPCProtocol(IRPCProtocol* rpc_protocol) = 0;
            virtual s32 ReceiveWaitCount() = 0;
            virtual void Receive(IRPCProtocol** rpc_protocol) = 0;
            virtual void Send(RPCID rpc_id) = 0;
            virtual void Execute() = 0;
        };

    }

    namespace FUNCTION{

    }

    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{

        // {70F0EEF6-B173-4E0C-9C4D-D4131C866838}
        static const EVOLUTION_IID IID_IRPCProtocol =
        { 0x70f0eef6, 0xb173, 0x4e0c, { 0x9c, 0x4d, 0xd4, 0x13, 0x1c, 0x86, 0x68, 0x38 } };


    }
}


#endif //!__EVOLUTION_NETWORK_RPC_INTERFACE_H_