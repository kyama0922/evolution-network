#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

//IUnknown
u32 TCPConnectSocket::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT TCPConnectSocket::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_ISocket))
    {
        *ppvObject = static_cast<ISocket *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_ITCPConnectSocket))
    {
        *ppvObject = static_cast<ITCPConnectSocket *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_TCPConnectSocket))
    {
        *ppvObject = static_cast<TCPConnectSocket *>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 TCPConnectSocket::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

TCPConnectSocket::TCPConnectSocket() :m_socket(-1), mp_protocol(nullptr){

}

TCPConnectSocket::~TCPConnectSocket(){
    EVOLUTION_RELEASE(this->mp_protocol);
}

NetworkResult::_RESULT TCPConnectSocket::Create(IProtocol* protocol){
    protocol->AddRef();
    this->mp_protocol = protocol;

    this->m_socket = ::socket(this->mp_protocol->GetAddrFamily(), SOCKET_TYPE::STREAM, 0);
    if ((s32)this->m_socket  < 0)
    {
        return NetworkResult::CONNECT_SOCKET_FAILED;
    }
    return NetworkResult::RESULT_OK;
}

//ソケットを取得
EVOLUTION::NETWORK::SOCKET TCPConnectSocket::GetSocket()const{
    return this->m_socket;
}

//ソケットをシャットダウンして終了させます。
void TCPConnectSocket::CloseSocket(){
    ::closesocket(this->m_socket);
}

//ソケットを閉じます(オプション設定可)
void TCPConnectSocket::ShutdownSocket(SHUTDOWN::_SHUTDOWN mode){
    switch (mode)
    {
    case EVOLUTION::NETWORK::SHUTDOWN::RECEIVE:
        ::shutdown(this->m_socket, SD_RECEIVE);
        break;
    case EVOLUTION::NETWORK::SHUTDOWN::SEND:
        ::shutdown(this->m_socket, SD_SEND);
        break;
    case EVOLUTION::NETWORK::SHUTDOWN::BOTH:
        ::shutdown(this->m_socket, SD_BOTH);
        break;
    }
}

//プロトコル情報を取得します。
const IProtocol* TCPConnectSocket::GetProtocol()const{
    return this->mp_protocol;
}
//ブロッキング設定をします。
void TCPConnectSocket::SetBlockMode(bool flag){
    u_long val;
    if (flag)
    {
        val = 0;
        ioctlsocket(this->m_socket, FIONBIO, &val);
        EVOLUTION_ENABLE_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
        return;
    }
    val = 1;
    ioctlsocket(this->m_socket, FIONBIO, &val);
    EVOLUTION_DISABLED_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
}
//ブロッキング状態を確認します。
bool TCPConnectSocket::IsBlocking()const{
    return EVOLUTION_IS_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
}

//ソケットを取得
CONNECT_ERROR::_CONNECT_ERROR TCPConnectSocket::Connect()const{
    ADDRESSFAMILY::_ADDRESSFAMILY af = this->mp_protocol->GetAddrFamily();
    s32 ret = -1;
    if (af == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET)
    {
        IProtocolINetv4* protocolv4;
        this->mp_protocol->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_ProtocolINetv4, (void**)&protocolv4);
        struct sockaddr_in sock_in;
        memset(&sock_in, 0, sizeof(struct sockaddr_in));
        sock_in.sin_family = af;
        sock_in.sin_port = htons(protocolv4->GetPort());
        sock_in.sin_addr.S_un.S_addr = protocolv4->GetipAddr().Addr.u_addr;
        EVOLUTION_RELEASE(protocolv4);
        ret = ::connect(this->m_socket, (struct sockaddr *)&sock_in, sizeof(struct sockaddr));
    }
    else if (af = EVOLUTION::NETWORK::ADDRESSFAMILY::_INET6)
    {

    }

    return (CONNECT_ERROR::_CONNECT_ERROR)ret;
}

//送信
s32 TCPConnectSocket::Send(const void* buffer, s32 buffer_size)const{
    s32 ret = send(this->m_socket, (char*)buffer, buffer_size, 0);
    return ret;
}

//受信
s32 TCPConnectSocket::Receive(void* buffer, s32 buffer_size)const{
    s32 ret = ::recv(this->m_socket, (char*)buffer, buffer_size, 0);
    return ret;
}