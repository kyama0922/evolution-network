#ifndef __EVOLUTION_NETWORK_INTERFACE_H_
#define __EVOLUTION_NETWORK_INTERFACE_H_

#include <evolution.h>

#include "evolution_network_num.h"
#include "evolution_network_result.h"

namespace EVOLUTION{
    namespace NETWORK{

        //ソケット通信用プロトコルクラス
        class IProtocol : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(IProtocol);
        public:
            //プロトコルを取得します。
            virtual void GetDesc(SOCKET_DESC* desc)const = 0;
            //IPアドレスを取得します。
            virtual const IPADDR& GetipAddr()const = 0;
            //ポート番号を取得します。
            virtual u16 GetPort()const = 0;
            //アドレスファミリーを取得します。
            virtual ADDRESSFAMILY::_ADDRESSFAMILY GetAddrFamily()const = 0;
        };

        //ソケット基底クラス
        class ISocket : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(ISocket);
        public:
            //ソケットを取得
            virtual SOCKET GetSocket()const = 0;
            //ソケットをシャットダウンして終了させます。
            virtual void CloseSocket() = 0;
            //ソケットを閉じます(オプション設定可)
            virtual void ShutdownSocket(SHUTDOWN::_SHUTDOWN mode) = 0;
            //プロトコル情報を取得します。
            virtual const IProtocol* GetProtocol()const = 0;
            //ブロッキング設定をします。
            virtual void SetBlockMode(BLOCKINGMODE::_BLOCKINGMODE mode) = 0;
            //ブロッキング状態を確認します。
            virtual bool IsBlocking() = 0;
        };

        //待ち受けソケット
        class IListenerSocket : public ISocket{
            EVOLUTION_NOT_DESTRUCTOR(IListenerSocket);
        public:
            //ソケットの待ち受け
            virtual NetworkResult::_RESULT Accept(ISocket** socket);
        };

        //ネットワークインターフェイス作成クラス　
        class INetworkFactory : public IUnknown{
            EVOLUTION_NOT_DESTRUCTOR(INetworkFactory);
        public:
            //プロトコルを作成します。
            virtual NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, const c8* host_name, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family = ADDRESSFAMILY::_INET) = 0;
            //プロトコルを作成します。
            virtual NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, IPADDR ip, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family = ADDRESSFAMILY::_INET) = 0;
            //プロトコルを作成します。
            virtual NetworkResult::_RESULT CreateProtocol(IProtocol** pp_protocol, const SOCKET_DESC& desc) = 0;
            //ソケットを作成します。
            virtual NetworkResult::_RESULT CreateSocket(ISocket** pp_socket, IProtocol* protocol) = 0;
            //リスナーソケットを作成します。
            virtual NetworkResult::_RESULT CreateListenerSocket(IListenerSocket** pp_listener_socket, IProtocol* protocol) = 0;
        };
    }

    namespace FUNCTION{
        //ネットワークファクトリーを作成します。
        extern EVOLUTION::RESULT CreateNetworkFactory(NETWORK::INetworkFactory** pp_network_factory);
        //ホスト名からIPアドレスを取得します。
        extern EVOLUTION::RESULT GetAddress(NETWORK::IPADDR& out, const c8* hostname);
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

        // {AC230D61-40D0-4177-B93A-041E064F029D}
        static const EVOLUTION_IID IID_IListenerSocket =
        { 0xac230d61, 0x40d0, 0x4177, { 0xb9, 0x3a, 0x4, 0x1e, 0x6, 0x4f, 0x2, 0x9d } };

        // {FC3110E9-9AAA-4b89-8BF8-B9B4E7CF1027}
        static const EVOLUTION_IID IID_INetworkFactory =
        { 0xfc3110e9, 0x9aaa, 0x4b89, { 0x8b, 0xf8, 0xb9, 0xb4, 0xe7, 0xcf, 0x10, 0x27 } };
    }
}


#endif //!__EVOLUTION_NETWORK_INTERFACE_H_