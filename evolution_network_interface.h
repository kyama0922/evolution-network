#ifndef __EVOLUTION_NETWORK_INTERFACE_H_
#define __EVOLUTION_NETWORK_INTERFACE_H_

#include <evolution.h>

#if defined(WIN32) || defined(WIN64)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include "evolution_network_num.h"
#include "evolution_network_result.h"

namespace EVOLUTION{
    namespace NETWORK{

        //ソケット通信用プロトコルクラス
        class IProtocol : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IProtocol);
        public:
            //アドレスファミリーを取得します。
            virtual ADDRESSFAMILY::_ADDRESSFAMILY GetAddrFamily()const = 0;
        };

        //ソケット通信用プロトコルクラス
        class IProtocolINetv4 : public IProtocol{
            EVOLUTION_NOT_DESTRUCTOR(IProtocolINetv4);
        public:
            //IPアドレスを取得します。
            virtual const IPADDR_V4& GetipAddr()const = 0;
            //ポート番号を取得します。
            virtual u16 GetPort()const = 0;
        };

        //ソケット通信用プロトコルクラス
        class IProtocolINetv6 : public IProtocol{
            EVOLUTION_NOT_DESTRUCTOR(IProtocolINetv6);
        public:
            //IPアドレスを取得します。
            virtual const IPADDR_V6& GetipAddr()const = 0;
            //ポート番号を取得します。
            virtual u16 GetPort()const = 0;
        };

        //ソケット基底クラス
        class ISocket : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(ISocket);
        public:
            //ソケットを取得
            virtual EVOLUTION::NETWORK::SOCKET GetSocket()const = 0;
            //ソケットをシャットダウンして終了させます。
            virtual void CloseSocket() = 0;
            //ソケットを閉じます(オプション設定可)
            virtual void ShutdownSocket(SHUTDOWN::_SHUTDOWN mode) = 0;
            //プロトコル情報を取得します。
            virtual const IProtocol* GetProtocol()const = 0;
            //ブロッキング設定をします。
            virtual void SetBlockMode(bool flag) = 0;
            //ブロッキング状態を確認します。
            virtual bool IsBlocking()const = 0;
        };

        //
        class ITCPConnectSocket : public ISocket{
            EVOLUTION_NOT_DESTRUCTOR(ITCPConnectSocket);
        public:
            //ソケットを取得
            virtual CONNECT_ERROR::_CONNECT_ERROR Connect()const = 0;
            //送信
            virtual s32 Send(const void* buffer, s32 buffer_size)const = 0;
            //受信
            virtual s32 Receive(void* buffer, s32 buffer_size)const = 0;
        };

        //待ち受けソケット
        class ITCPBindSocket : public ISocket{
            EVOLUTION_NOT_DESTRUCTOR(ITCPBindSocket);
        public:
            //ソケットの待ち受け
            virtual NetworkResult::_RESULT Accept(ISocket** socket)const = 0;
            //送信
            virtual s32 Send(const void* buffer, s32 buffer_size, const ISocket* socket)const = 0;
            //受信
            virtual s32 Receive(void* buffer, s32 buffer_size, const ISocket* socket)const = 0;
        };

        //
        class IUDPTransceiverSocket : public ISocket{
            EVOLUTION_NOT_DESTRUCTOR(IUDPTransceiverSocket);
        public:
            //送信
            virtual s32 Send(const void* buffer, s32 buffer_size)const = 0;
            //受信
            virtual s32 Receive(void* buffer, s32 buffer_size)const = 0;
        };

        //
        class IUDPBindSocket : public ISocket{
            EVOLUTION_NOT_DESTRUCTOR(IUDPBindSocket);
        public:
            //送信
            virtual s32 Send(const void* buffer, s32 buffer_size, IProtocol* protocol)const = 0;
            //受信
            virtual s32 Receive(void* buffer, s32 buffer_size, IProtocol** protocol)const = 0;
        };

        //ネットワークインターフェイス作成クラス　
        class INetworkFactory : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(INetworkFactory);
        public:
            //プロトコルを作成します。
            virtual NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, const c8* host_name, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family = ADDRESSFAMILY::_INET) = 0;
            //プロトコルを作成します。
            virtual NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, IPADDR_V4 ip4, u16 port) = 0;
            //プロトコルを作成します。
            virtual NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, IPADDR_V6 ip6, u16 port) = 0;
            //コネクトソケットを作成します。
            virtual NetworkResult::_RESULT CreateTCPConnectSocket(ITCPConnectSocket** pp_connect_socket, IProtocol* protocol) = 0;
            //TCPバインドソケットを作成します。
            virtual NetworkResult::_RESULT CreateTCPBindSocket(ITCPBindSocket** pp_bind_socket, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family = ADDRESSFAMILY::_INET) = 0;
            //TCPバインドソケットを作成します。
            virtual NetworkResult::_RESULT CreateTCPBindSocket(ITCPBindSocket** pp_bind_socket, IProtocol* protocol) = 0;
            //コネクトソケットを作成します。
            virtual NetworkResult::_RESULT CreateUDPTransceiverSocket(IUDPTransceiverSocket** pp_udp_transceiver_socket, IProtocol* protocol) = 0;
            //UDPバインドソケットを作成します。
            virtual NetworkResult::_RESULT CreateUDPBindSocket(IUDPBindSocket** pp_udp_bind_socket, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family = ADDRESSFAMILY::_INET) = 0;
            //UDPバインドソケットを作成します。
            virtual NetworkResult::_RESULT CreateUDPBindSocket(IUDPBindSocket** pp_udp_bind_socket, IProtocol* protocol) = 0;
        };
    }

    namespace FUNCTION{
        //ネットワークファクトリーを作成します。
        extern EVOLUTION::RESULT CreateNetworkFactory(NETWORK::INetworkFactory** pp_network_factory);
        //ホスト名からIPv4アドレスを取得します。
        extern EVOLUTION::RESULT GetAddress(NETWORK::IPADDR_V4& out, const c8* hostname);
    }

    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {45C9B76C-089B-431d-9153-9FC5C3C0818E}
        static const EVOLUTION_IID IID_IProtocol =
        { 0x45c9b76c, 0x89b, 0x431d, { 0x91, 0x53, 0x9f, 0xc5, 0xc3, 0xc0, 0x81, 0x8e } };

        // {CE3D44E9-68F5-47cd-9346-009D48B981DA}
        static const EVOLUTION_IID IID_ISocket =
        { 0xce3d44e9, 0x68f5, 0x47cd, { 0x93, 0x46, 0x0, 0x9d, 0x48, 0xb9, 0x81, 0xda } };

        // {D00660AD-C17E-40d4-B8B0-9C93E314316D}
        static const EVOLUTION_IID IID_ITCPConnectSocket =
        { 0xd00660ad, 0xc17e, 0x40d4, { 0xb8, 0xb0, 0x9c, 0x93, 0xe3, 0x14, 0x31, 0x6d } };

        // {AC230D61-40D0-4177-B93A-041E064F029D}
        static const EVOLUTION_IID IID_ITCPBindSocket =
        { 0xac230d61, 0x40d0, 0x4177, { 0xb9, 0x3a, 0x4, 0x1e, 0x6, 0x4f, 0x2, 0x9d } };

        // {2EDA8C3C-C878-4ab9-9F0B-83BE72DDDDA5}
        static const EVOLUTION_IID IID_IUDPTransceiverSocket =
        { 0x2eda8c3c, 0xc878, 0x4ab9, { 0x9f, 0xb, 0x83, 0xbe, 0x72, 0xdd, 0xdd, 0xa5 } };

        // {93E54D82-4AE8-47f9-ABA0-04983C652EF0}
        static const EVOLUTION_IID IID_IUDPBindSocket =
        { 0x93e54d82, 0x4ae8, 0x47f9, { 0xab, 0xa0, 0x4, 0x98, 0x3c, 0x65, 0x2e, 0xf0 } };

        // {FC3110E9-9AAA-4b89-8BF8-B9B4E7CF1027}
        static const EVOLUTION_IID IID_INetworkFactory =
        { 0xfc3110e9, 0x9aaa, 0x4b89, { 0x8b, 0xf8, 0xb9, 0xb4, 0xe7, 0xcf, 0x10, 0x27 } };
    }
}


#endif //!__EVOLUTION_NETWORK_INTERFACE_H_