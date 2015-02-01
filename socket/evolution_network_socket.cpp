#include "../evolution_network_implement.h"
 
using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

//----------------------------------------------------------
//
//          Socket
//
//----------------------------------------------------------
//IUnknown

u32 Socket::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT Socket::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown *> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_ISocket)) {
        *ppvObject = static_cast<ISocket *> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_Socket)) {
        *ppvObject = static_cast<Socket *> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }
    return _RESULT::S_ok;
}

u32 Socket::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

Socket::Socket() {

}

Socket::~Socket() {
    EVOLUTION_RELEASE(this->mp_protocol);
}

NetworkResult::_RESULT Socket::Create(EVOLUTION::NETWORK::SOCKET sock, IProtocol* protocol, bool block_bode) {
    this->m_socket = sock;
    protocol->AddRef();
    this->mp_protocol = protocol;
    this->SetBlockMode(block_bode);

    return NetworkResult::RESULT_OK;
}

//ソケットを取得

EVOLUTION::NETWORK::SOCKET Socket::GetSocket()const {
    return this->m_socket;
}

//ソケットをシャットダウンして終了させます。

void Socket::CloseSocket() {
    ::close(this->m_socket);
}

//ソケットを閉じます(オプション設定可)

void Socket::ShutdownSocket(SHUTDOWN::_SHUTDOWN mode) {
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

const IProtocol* Socket::GetProtocol()const {
    return this->mp_protocol;
}
//ブロッキング設定をします。

void Socket::SetBlockMode(bool flag) {
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

bool Socket::IsBlocking()const {
    return EVOLUTION_IS_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
}
