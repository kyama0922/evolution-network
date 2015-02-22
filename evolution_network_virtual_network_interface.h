#ifndef __EVOLUTION_NETWORK_RPC_INTERFACE_H_
#define __EVOLUTION_NETWORK_RPC_INTERFACE_H_

#include "evolution_network_interface.h"

namespace EVOLUTION{
    namespace NETWORK{
        namespace  VIRTUALNETWORK{

            struct VNResult{
                enum _RESULT{
                    //----------------------------成功----------------------------
                    RESULT_OK = 0x00000000,//成功

                    //----------------------------失敗----------------------------
                    UNKNOWN_FAILED = 0x80000000, //失敗
                };

            };

            //
            class IVNBrainServer : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IVNBrainServer);
            public:
            };


            //
            class IVNServer : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IVNServer);
            public:

            };

            //
            class IVNClient : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IVNClient);
            public:

            };

            //
            class IVNFactory : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IVNFactory);
            public:
                void CreateVNBrainServer(IVNBrainServer** pp_brain_server, u16 tcp_port, u16 udp_port);
            };

        }
    }
    namespace FUNCTION{
        extern NETWORK::VIRTUALNETWORK::VNResult::_RESULT CreateVNFactory(NETWORK::VIRTUALNETWORK::IVNFactory** pp_vnfactory);
    }

    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{

        // {70F0EEF6-B173-4E0C-9C4D-D4131C866838}
        //static const EVOLUTION_IID IID_IRPCProtocol =
        //{ 0x70f0eef6, 0xb173, 0x4e0c, { 0x9c, 0x4d, 0xd4, 0x13, 0x1c, 0x86, 0x68, 0x38 } };

        // {C74C1B94-8940-4343-AF8B-8EC1A23C4F79}
        static const EVOLUTION_IID IID_IVNBrainServer =
        { 0xc74c1b94, 0x8940, 0x4343, { 0xaf, 0x8b, 0x8e, 0xc1, 0xa2, 0x3c, 0x4f, 0x79 } };


        // {FE28C378-2D0C-4B24-BBF1-C31D631CD8F3}
        static const EVOLUTION_IID IID_IVNServer =
        { 0xfe28c378, 0x2d0c, 0x4b24, { 0xbb, 0xf1, 0xc3, 0x1d, 0x63, 0x1c, 0xd8, 0xf3 } };


        // {38156147-6F6F-4948-BB07-98045D66FEA9}
        static const EVOLUTION_IID IID_IVNClient =
        { 0x38156147, 0x6f6f, 0x4948, { 0xbb, 0x7, 0x98, 0x4, 0x5d, 0x66, 0xfe, 0xa9 } };


        // {7310C9BE-7C99-4FE5-8AA2-B9E85708A23C}
        static const EVOLUTION_IID IID_IVNFactory =
        { 0x7310c9be, 0x7c99, 0x4fe5, { 0x8a, 0xa2, 0xb9, 0xe8, 0x57, 0x8, 0xa2, 0x3c } };

    }
}


#endif //!__EVOLUTION_NETWORK_RPC_INTERFACE_H_