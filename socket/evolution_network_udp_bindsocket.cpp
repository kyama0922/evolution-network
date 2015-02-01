#include <unistd.h>

#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

//IUnknown

u32 UDPBindSocket::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT UDPBindSocket::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown *> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_ISocket)) {
        *ppvObject = static_cast<ISocket *> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUDPBindSocket)) {
        *ppvObject = static_cast<IUDPBindSocket *> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_UDPBindSocket)) {
        *ppvObject = static_cast<UDPBindSocket *> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }
    return _RESULT::S_ok;
}

u32 UDPBindSocket::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

UDPBindSocket::UDPBindSocket() : mp_protocol(nullptr), mp_factory(nullptr) {

}

UDPBindSocket::~UDPBindSocket() {
    this->CloseSocket();
    EVOLUTION_RELEASE(this->mp_protocol);
    EVOLUTION_RELEASE(this->mp_factory);
}

NetworkResult::_RESULT UDPBindSocket::Create(INetworkFactory* factory, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family) {
    factory->AddRef();
    this->mp_factory = factory;


    this->m_socket = ::socket(addr_family, SOCKET_TYPE::DGRAM, 0);
    if ((s32)this->m_socket < 0) {
        return NetworkResult::CONNECT_SOCKET_FAILED;
    }

    s32 ret = -1;
    if (addr_family == ADDRESSFAMILY::_INET) {
        IProtocolINetv4* protocolv4;

        IPADDR_V4 v4;
        v4.Addr.u_addr = 0x00000000;
        this->mp_factory->CreateProtocol((IProtocol**) & protocolv4, v4, port);

        struct sockaddr_in sock_in;
        memset(&sock_in, 0, sizeof (struct sockaddr_in));
        sock_in.sin_family = ADDRESSFAMILY::_INET;
        sock_in.sin_port = htons(protocolv4->GetPort());
        sock_in.sin_addr.s_addr = protocolv4->GetipAddr().Addr.u_addr;
        ret = ::bind(this->m_socket, (struct sockaddr *) &sock_in, sizeof (sockaddr_in));
        this->mp_protocol = protocolv4;
    } else if (addr_family == ADDRESSFAMILY::_INET6) {
        IPADDR_V6 v6;
        v6.Addr.u_addr_ll[0] = 0;
        v6.Addr.u_addr_ll[1] = 0;
        this->mp_factory->CreateProtocol(&this->mp_protocol, v6, port);
    } else {
        return NetworkResult::CREATE_PROTOCOL_FAILED;
    }

    //バインド
    if (ret < 0) {
        return NetworkResult::BIND_FAILED;
    }

    return NetworkResult::RESULT_OK;
}

NetworkResult::_RESULT UDPBindSocket::Create(INetworkFactory* factory, IProtocol* protocol) {
    factory->AddRef();
    this->mp_factory = factory;

    protocol->AddRef();
    this->mp_protocol = protocol;
    this->m_socket = ::socket(protocol->GetAddrFamily(), SOCKET_TYPE::DGRAM, 0);
    if ((s32)this->m_socket < 0) {
        return NetworkResult::CONNECT_SOCKET_FAILED;
    }

    s32 ret = -1;
    EVOLUTION::NETWORK::ADDRESSFAMILY::_ADDRESSFAMILY af = protocol->GetAddrFamily();
    if (af == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET) {
        IProtocolINetv4* protocolv4;
        protocol->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_ProtocolINetv4, (void**) &protocolv4);
        struct sockaddr_in sock_in;
        memset(&sock_in, 0, sizeof (struct sockaddr_in));
        sock_in.sin_family = af;
        sock_in.sin_port = htons(protocolv4->GetPort());
        sock_in.sin_addr.s_addr = protocolv4->GetipAddr().Addr.u_addr;
        ret = ::bind(this->m_socket, (struct sockaddr *) &sock_in, sizeof (sockaddr_in));
        EVOLUTION_RELEASE(protocolv4);
    } else if (af = EVOLUTION::NETWORK::ADDRESSFAMILY::_INET6) {

    }

    //バインド
    if (ret < 0) {
        return NetworkResult::BIND_FAILED;
    }

    return NetworkResult::RESULT_OK;
}

//ソケットを取得

EVOLUTION::NETWORK::SOCKET UDPBindSocket::GetSocket()const {
    return this->m_socket;
}

//ソケットをシャットダウンして終了させます。

void UDPBindSocket::CloseSocket() {
    ::close(this->m_socket);
    this->m_socket = -1;
}

//ソケットを閉じます(オプション設定可)

void UDPBindSocket::ShutdownSocket(SHUTDOWN::_SHUTDOWN mode) {
    switch (mode) {
        case EVOLUTION::NETWORK::SHUTDOWN::RECEIVE:
            ::shutdown(this->m_socket, SHUT_RD);
            break;
        case EVOLUTION::NETWORK::SHUTDOWN::SEND:
            ::shutdown(this->m_socket, SHUT_WR);
            break;
        case EVOLUTION::NETWORK::SHUTDOWN::BOTH:
            ::shutdown(this->m_socket, SHUT_RDWR);
            break;
    }
}

//プロトコル情報を取得します。

const IProtocol* UDPBindSocket::GetProtocol()const {
    return this->mp_protocol;
}

//ブロッキング設定をします。

void UDPBindSocket::SetBlockMode(bool flag) {
    s32 option = ::fcntl(this->m_socket, F_GETFL, 0);
    if (flag) {
        EVOLUTION_ENABLE_STATE(option, O_NONBLOCK);
        ::fcntl(this->m_socket, F_SETFL, option);
        EVOLUTION_ENABLE_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
        return;
    }
    EVOLUTION_DISABLED_STATE(option, O_NONBLOCK);
    ::fcntl(this->m_socket, F_SETFL, option);
    EVOLUTION_DISABLED_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
}

//ブロッキング状態を確認します。

bool UDPBindSocket::IsBlocking()const {
    return EVOLUTION_IS_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
}


//送信

s32 UDPBindSocket::Send(const void* buffer, s32 buffer_size, IProtocol* protocol)const {
    EVOLUTION::NETWORK::ADDRESSFAMILY::_ADDRESSFAMILY af = protocol->GetAddrFamily();
    s32 ret = -1;
    if (af == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET) {
        IProtocolINetv4* protocolv4;
        protocol->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_ProtocolINetv4, (void**) &protocolv4);
        struct sockaddr_in sock_in;
        memset(&sock_in, 0, sizeof (struct sockaddr_in));
        sock_in.sin_family = af;
        sock_in.sin_port = htons(protocolv4->GetPort());
        sock_in.sin_addr.s_addr = protocolv4->GetipAddr().Addr.u_addr;

        ret = ::sendto(this->m_socket, (const char*) buffer, buffer_size, 0, (struct sockaddr*) &sock_in, sizeof (sock_in));
    } else if (af = EVOLUTION::NETWORK::ADDRESSFAMILY::_INET6) {

    }
    return ret;
}

//受信

s32 UDPBindSocket::Receive(void* buffer, s32 buffer_size, IProtocol** protocol)const {
    //src_addrで初期化されたサイズ指定
    socklen_t sock_len = (this->mp_protocol->GetAddrFamily() == ADDRESSFAMILY::_INET) ? sizeof (struct sockaddr_in) : /* sizeof(struct sockaddr_in)*/-1;
    struct sockaddr _sockaddr;
    s32 ret = (s32)recvfrom(this->m_socket,  buffer, buffer_size, 0, &_sockaddr, &sock_len);


    //errorチェック
    if (ret < 0) {
        return ret;
    }
    if (protocol == nullptr) {
        return ret;
    }        //IpV4チェック
    else if (sock_len == sizeof (struct sockaddr_in)) {
        struct sockaddr_in* _sockaddr_in = (struct sockaddr_in*) &_sockaddr;
        IPADDR_V4 v4;
        v4.Addr.u_addr = _sockaddr_in->sin_addr.s_addr;
        NetworkResult::_RESULT result = this->mp_factory->CreateProtocol(protocol, v4, (u16) ntohs(_sockaddr_in->sin_port));
        if (EVOLUTION_FAILED(result)) {
            return result;
        }
        return ret;
    }        //IpV6チェック
    else if (false) {

    }        //それ以外を破棄
    else {
        ret = -1;
    }

    return ret;
}