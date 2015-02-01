#ifndef __EVOLUTION_NETWORK_IMPLEMENT_H_
#define __EVOLUTION_NETWORK_IMPLEMENT_H_

#include "evolution_network_interface.h"

#include <sys/socket.h>
#include <sys/socketvar.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <fcntl.h>

namespace EVOLUTION{
    namespace NETWORK{

        //ソケット通信用プロトコルクラス
        class ProtocolINetv4 : public IProtocolINetv4{
            EVOLUTION::InstanceCounter m_instance_counter;
            IPADDR_V4 m_ip;
            u16 m_port;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            ProtocolINetv4();
            ~ProtocolINetv4();

            NetworkResult::_RESULT Create(const c8* host_name, u16 port);
            NetworkResult::_RESULT Create(IPADDR_V4 ip, u16 port);

            //IPアドレスを取得します。
            const IPADDR_V4& GetipAddr()const;
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
            u32 m_flag;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            Socket();
            ~Socket();

            NetworkResult::_RESULT Create(EVOLUTION::NETWORK::SOCKET sock, IProtocol* protocol, bool block_bode);

            //ソケットを取得
            EVOLUTION::NETWORK::SOCKET GetSocket()const;
            //ソケットをシャットダウンして終了させます。
            void CloseSocket();
            //ソケットを閉じます(オプション設定可)
            void ShutdownSocket(SHUTDOWN::_SHUTDOWN mode);
            //プロトコル情報を取得します。
            const IProtocol* GetProtocol()const;
            //ブロッキング設定をします。
            void SetBlockMode(bool flag);
            //ブロッキング状態を確認します。
            bool IsBlocking()const;
        };


        //
        class TCPConnectSocket : public ITCPConnectSocket{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;
            IProtocol* mp_protocol;
            SOCKET m_socket;
            u32 m_flag;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            TCPConnectSocket();
            ~TCPConnectSocket();

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
            void SetBlockMode(bool flag);
            //ブロッキング状態を確認します。
            bool IsBlocking()const;
            //ソケットを取得
            CONNECT_ERROR::_CONNECT_ERROR Connect()const;
            //送信
            s32 Send(const void* buffer, s32 buffer_size)const;
            //受信
            s32 Receive(void* buffer, s32 buffer_size)const;
        };

        //待ち受けソケット
        class TCPBindSocket : public ITCPBindSocket{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;
            IProtocol* mp_protocol;
            SOCKET m_socket;
            u32 m_flag;
            INetworkFactory* factory;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            TCPBindSocket();
            ~TCPBindSocket();

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
            void SetBlockMode(bool flag);
            //ブロッキング状態を確認します。
            bool IsBlocking()const;
            //ソケットの待ち受け
            NetworkResult::_RESULT Accept(ISocket** socket)const;
            //送信
            s32 Send(const void* buffer, s32 buffer_size, const ISocket* socket)const;
            //受信
            s32 Receive(void* buffer, s32 buffer_size, const ISocket* socket)const;
        };

        //
        class UDPTransceiverSocket : public IUDPTransceiverSocket{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;
            IProtocol* mp_protocol;
            SOCKET m_socket;
            u32 m_flag;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            UDPTransceiverSocket();
            ~UDPTransceiverSocket();

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
            void SetBlockMode(bool flag);
            //ブロッキング状態を確認します。
            bool IsBlocking()const;
            //送信
            s32 Send(const void* buffer, s32 buffer_size)const;
            //受信
            s32 Receive(void* buffer, s32 buffer_size)const;
        };

        //
        class UDPBindSocket : public IUDPBindSocket{
        private:
            EVOLUTION::InstanceCounter m_instance_counter;
            IProtocol* mp_protocol;
            SOCKET m_socket;
            u32 m_flag;
            INetworkFactory* mp_factory;
        public:
            //IUnknown
            u32 AddRef();
            RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
            u32 Release();

            UDPBindSocket();
            ~UDPBindSocket();

            NetworkResult::_RESULT Create(INetworkFactory* factory, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family);
            NetworkResult::_RESULT Create(INetworkFactory* factory , IProtocol* protocol);

            //ソケットを取得
            SOCKET GetSocket()const;
            //ソケットをシャットダウンして終了させます。
            void CloseSocket();
            //ソケットを閉じます(オプション設定可)
            void ShutdownSocket(SHUTDOWN::_SHUTDOWN mode);
            //プロトコル情報を取得します。
            const IProtocol* GetProtocol()const;
            //ブロッキング設定をします。
            void SetBlockMode(bool flag);
            //ブロッキング状態を確認します。
            bool IsBlocking()const;
            //送信
            s32 Send(const void* buffer, s32 buffer_size, IProtocol* protocol)const;
            //受信
            s32 Receive(void* buffer, s32 buffer_size, IProtocol** protocol)const;
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
            NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, IPADDR_V4 ip4, u16 port);
            //プロトコルを作成します。
            NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, IPADDR_V6 ip6, u16 port);
            //コネクトソケットを作成します。
            NetworkResult::_RESULT CreateTCPConnectSocket(ITCPConnectSocket** pp_connect_socket, IProtocol* protocol);
            //TCPバインドソケットを作成します。
            NetworkResult::_RESULT CreateTCPBindSocket(ITCPBindSocket** pp_bind_socket, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family);
            //TCPバインドソケットを作成します。
            NetworkResult::_RESULT CreateTCPBindSocket(ITCPBindSocket** pp_bind_socket, IProtocol* protocol);
            //コネクトソケットを作成します。
            NetworkResult::_RESULT CreateUDPTransceiverSocket(IUDPTransceiverSocket** pp_udp_transceiver_socket, IProtocol* protocol);
            //UDPバインドソケットを作成します。
            NetworkResult::_RESULT CreateUDPBindSocket(IUDPBindSocket** pp_udp_bind_socket, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family);
            //UDPバインドソケットを作成します。
            NetworkResult::_RESULT CreateUDPBindSocket(IUDPBindSocket** pp_udp_bind_socket, IProtocol* protocol);
        };
    }

    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {7C48C137-3C2C-4926-95EC-47C95F34037F}
        static const EVOLUTION_IID IID_ProtocolINetv4 =
        { 0x7c48c137, 0x3c2c, 0x4926, { 0x95, 0xec, 0x47, 0xc9, 0x5f, 0x34, 0x3, 0x7f } };

        // {E4F1E08D-C8E0-4da1-979F-9795A156D93E}
        static const EVOLUTION_IID IID_Socket =
        { 0xe4f1e08d, 0xc8e0, 0x4da1, { 0x97, 0x9f, 0x97, 0x95, 0xa1, 0x56, 0xd9, 0x3e } };

        // {255621F5-1CBA-426b-9B2C-729D2BB7747F}
        static const EVOLUTION_IID IID_TCPConnectSocket =
        { 0x255621f5, 0x1cba, 0x426b, { 0x9b, 0x2c, 0x72, 0x9d, 0x2b, 0xb7, 0x74, 0x7f } };

        // {01D9D503-0B9F-44b2-9278-C01DE36E305B}
        static const EVOLUTION_IID IID_TCPBindSocket =
        { 0x1d9d503, 0xb9f, 0x44b2, { 0x92, 0x78, 0xc0, 0x1d, 0xe3, 0x6e, 0x30, 0x5b } };

        // {1F3E5D23-E120-405b-88FC-DA5C74B41D1C}
        static const EVOLUTION_IID IID_UDPTransceiverSocket =
        { 0x1f3e5d23, 0xe120, 0x405b, { 0x88, 0xfc, 0xda, 0x5c, 0x74, 0xb4, 0x1d, 0x1c } };

        // {0F9E92A7-36F0-439d-9526-95182DDDC265}
        static const EVOLUTION_IID IID_UDPBindSocket =
        { 0xf9e92a7, 0x36f0, 0x439d, { 0x95, 0x26, 0x95, 0x18, 0x2d, 0xdd, 0xc2, 0x65 } };

        // {BCAB173F-7440-45b7-AAB6-CB85176C93F0}
        static const EVOLUTION_IID IID_NetworkFactory =
        { 0xbcab173f, 0x7440, 0x45b7, { 0xaa, 0xb6, 0xcb, 0x85, 0x17, 0x6c, 0x93, 0xf0 } };

    }
}


#endif //!__EVOLUTION_NETWORK_INTERFACE_H_