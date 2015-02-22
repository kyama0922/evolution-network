#ifndef __EVOLUTION_NETWORK_RPC_INTERFACE_H_
#define __EVOLUTION_NETWORK_RPC_INTERFACE_H_

#include "evolution_network_interface.h"

namespace EVOLUTION{
    namespace NETWORK{

        typedef _GUID RPCID;

        //
        class IRPCProtocol : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IRPCProtocol);
        public:
            virtual RPCID RpcID() = 0;
            virtual u32 GetLayoutCount() = 0;
            virtual bool IsLittleEdian() = 0;
            virtual ptr_t LayoutPtr() = 0;
            virtual ptr_size_t GetLayoutSize() = 0;
            virtual void Receive(void* buffer, s32 buffer_size) = 0;
            virtual void Send(void* buffer, s32 buffer_size) = 0;
        };


        //
        class IRPCController : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IRPCController);
        public:
            virtual NetworkResult::_RESULT AddRPCProtocol(IRPCProtocol* rpc_protocol) = 0;
            virtual NetworkResult::_RESULT DelRPCProtocol(IRPCProtocol* rpc_protocol) = 0;
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