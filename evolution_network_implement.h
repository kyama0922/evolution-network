#ifndef __EVOLUTION_NETWORK_IMPLEMENT_H_
#define __EVOLUTION_NETWORK_IMPLEMENT_H_

#include <WinSock2.h>
#include "evolution_network_interface.h"

namespace EVOLUTION{
    namespace NETWORK{

        //ソケット通信用プロトコルクラス
        class Protocol : public IProtocol{
            EVOLUTION::InstanceCounter m_instance_counter;
            SOCKET_DESC m_desc;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            Protocol();
            ~Protocol();

            NetworkResult::_RESULT Create(const c8* host_name, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family);
            NetworkResult::_RESULT Create(IPADDR ip, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family);
            NetworkResult::_RESULT Create(const SOCKET_DESC& desc);

            //プロトコルを取得します。
            void GetDesc(SOCKET_DESC* desc)const;
            //IPアドレスを取得します。
            const IPADDR& GetipAddr()const;
            //ポート番号を取得します。
            u16 GetPort()const;
            //アドレスファミリーを取得します。
            ADDRESSFAMILY::_ADDRESSFAMILY GetAddrFamily()const;
        };

        //ソケット基底クラス
        class Socket : public ISocket{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;
            IProtocol* mp_protocol;
            SOCKET m_socket;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            Socket();
            ~Socket();

            NetworkResult::_RESULT Create(IProtocol* protocol);

            //ソケットを取得
            SOCKET GetSocket()const;
            //ソケットをシャットダウンして終了させます。
            void CloseSocket();
            //ソケットを閉じます(オプション設定可)
            void ShutdownSocket(SHUTDOWN::_SHUTDOWN mode);
            //プロトコル情報を取得します。
            const IProtocol* GetProtocol()const;
            //ブロッキング設定をします。
            void SetBlockMode(BLOCKINGMODE::_BLOCKINGMODE mode);
            //ブロッキング状態を確認します。
            bool IsBlocking();
        };

        //待ち受けソケット
        class ListenerSocket : public IListenerSocket{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;
            IProtocol* mp_protocol;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            ListenerSocket();
            ~ListenerSocket();

            NetworkResult::_RESULT Create(IProtocol* protocol);

            //ソケットを取得
            SOCKET GetSocket()const;
            //ソケットをシャットダウンして終了させます。
            void CloseSocket();
            //ソケットを閉じます(オプション設定可)
            void ShutdownSocket(SHUTDOWN::_SHUTDOWN mode);
            //プロトコル情報を取得します。
            const IProtocol* GetProtocol()const;
            //ブロッキング設定をします。
            void SetBlockMode(BLOCKINGMODE::_BLOCKINGMODE mode);
            //ブロッキング状態を確認します。
            bool IsBlocking();
            //ソケットの待ち受け
            NetworkResult::_RESULT Accept(ISocket** socket);
        };

        //ネットワークインターフェイス作成クラス　
        class NetworkFactory : public INetworkFactory{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            NetworkFactory();
            ~NetworkFactory();

            NetworkResult::_RESULT Create();

            //プロトコルを作成します。
            NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, const c8* host_name, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family);
            //プロトコルを作成します。
            NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, IPADDR ip, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family);
            //プロトコルを作成します。
            NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, const SOCKET_DESC& desc);
            //ソケットを作成します。
            NetworkResult::_RESULT CreateSocket(ISocket** pp_socket, IProtocol* protocol);
            //リスナーソケットを作成します。
            NetworkResult::_RESULT CreateListenerSocket(IListenerSocket** pp_listener_socket, IProtocol* protocol);
        };
    }

    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {7C48C137-3C2C-4926-95EC-47C95F34037F}
        static const EVOLUTION_IID IID_Protocol =
        { 0x7c48c137, 0x3c2c, 0x4926, { 0x95, 0xec, 0x47, 0xc9, 0x5f, 0x34, 0x3, 0x7f } };

        // {255621F5-1CBA-426b-9B2C-729D2BB7747F}
        static const EVOLUTION_IID IID_Socket =
        { 0x255621f5, 0x1cba, 0x426b, { 0x9b, 0x2c, 0x72, 0x9d, 0x2b, 0xb7, 0x74, 0x7f } };

        // {01D9D503-0B9F-44b2-9278-C01DE36E305B}
        static const EVOLUTION_IID IID_ListenerSocket =
        { 0x1d9d503, 0xb9f, 0x44b2, { 0x92, 0x78, 0xc0, 0x1d, 0xe3, 0x6e, 0x30, 0x5b } };

        // {BCAB173F-7440-45b7-AAB6-CB85176C93F0}
        static const EVOLUTION_IID IID_NetworkFactory =
        { 0xbcab173f, 0x7440, 0x45b7, { 0xaa, 0xb6, 0xcb, 0x85, 0x17, 0x6c, 0x93, 0xf0 } };

    }
}


#endif //!__EVOLUTION_NETWORK_INTERFACE_H_