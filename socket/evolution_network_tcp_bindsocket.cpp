#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

//----------------------------------------------------------
//
//          TCPBindSocket
//
//----------------------------------------------------------
//IUnknown
u32 TCPBindSocket::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT TCPBindSocket::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_ISocket))
    {
        *ppvObject = static_cast<ISocket *>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_ITCPBindSocket))
    {
        *ppvObject = static_cast<ITCPBindSocket *>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_TCPBindSocket))
    {
        *ppvObject = static_cast<TCPBindSocket *>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 TCPBindSocket::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

TCPBindSocket::TCPBindSocket(){

}

TCPBindSocket::~TCPBindSocket(){
    this->CloseSocket();
    EVOLUTION_RELEASE(this->mp_protocol);
}

NetworkResult::_RESULT TCPBindSocket::Create(IProtocol* protocol){
    protocol->AddRef();
    this->mp_protocol = protocol;
    this->m_socket = ::socket(protocol->GetAddrFamily(), SOCKET_TYPE::STREAM, 0);
    if ((s32)this->m_socket  < 0)
    {
        return NetworkResult::CONNECT_SOCKET_FAILED;
    }

    s32 ret = -1;
    EVOLUTION::NETWORK::ADDRESSFAMILY::_ADDRESSFAMILY af = protocol->GetAddrFamily();
    if (af == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET)
    {
        IProtocolINetv4* protocolv4;
        protocol->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_ProtocolINetv4, (void**)&protocolv4);
        struct sockaddr_in sock_in;
        memset(&sock_in, 0, sizeof(struct sockaddr_in));
        sock_in.sin_family = af;
        sock_in.sin_port = htons(protocolv4->GetPort());
        sock_in.sin_addr.S_un.S_addr = protocolv4->GetipAddr().Addr.u_addr;
        ret = ::bind(this->m_socket, (struct sockaddr *)&sock_in, sizeof(sockaddr_in));
        EVOLUTION_RELEASE(protocolv4);
    }
    else if (af = EVOLUTION::NETWORK::ADDRESSFAMILY::_INET6)
    {

    }

    //バインド
    if (ret < 0)
    {
        return NetworkResult::BIND_FAILED;
    }

    ret = ::listen(this->m_socket, 5);
    if (ret < 0)
    {
        return NetworkResult::BIND_FAILED;
    }
    return NetworkResult::RESULT_OK;
}

//ソケットを取得
EVOLUTION::NETWORK::SOCKET TCPBindSocket::GetSocket()const{
    return this->m_socket;
}

//ソケットをシャットダウンして終了させます。
void TCPBindSocket::CloseSocket(){
    ::closesocket(this->m_socket);
    this->m_socket = -1;
}

//ソケットを閉じます(オプション設定可)
void TCPBindSocket::ShutdownSocket(SHUTDOWN::_SHUTDOWN mode){
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
const IProtocol* TCPBindSocket::GetProtocol()const{
    return this->mp_protocol;
}
//ブロッキング設定をします。
void TCPBindSocket::SetBlockMode(bool flag){
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
bool TCPBindSocket::IsBlocking()const{
    return EVOLUTION_IS_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
}


//ソケットの待ち受け
NetworkResult::_RESULT TCPBindSocket::Accept(ISocket** socket)const{
    *socket = nullptr;
    struct sockaddr_in client;
    int len = sizeof(client);
    SOCKET _socket = accept(this->m_socket, (struct sockaddr *)&client, &len);
    if ((s32)_socket > 0)
    {
        IPADDR_V4 v4;
        v4.Addr.u_addr = client.sin_addr.S_un.S_addr;
        u16 port = ntohs(client.sin_port);
        ProtocolINetv4* protocol = NEW ProtocolINetv4();
        NetworkResult::_RESULT ret;
        ret =  protocol->Create(v4, port);
        if (EVOLUTION_FAILED(ret))
        {
            EVOLUTION_RELEASE(protocol);
            return NetworkResult::CREATE_FAILED;
        }
        Socket* sock = NEW Socket();
        ret = sock->Create(_socket, protocol, this->IsBlocking());
        if (EVOLUTION_FAILED(ret))
        {
            EVOLUTION_RELEASE(sock);
            return NetworkResult::CREATE_SOCKET_FAILED;
        }
        *socket = static_cast<ISocket*>(sock);
        EVOLUTION_RELEASE(protocol);
        return NetworkResult::RESULT_OK;
    }
    return NetworkResult::NONE_ACCEPT_SOCKET;
}

//送信
s32 TCPBindSocket::Send(const void* buffer, s32 buffer_size, const ISocket* socket)const{
    s32 ret = send(socket->GetSocket(), (char*)buffer, buffer_size, 0);
    return ret;
}

//受信
s32 TCPBindSocket::Receive(void* buffer, s32 buffer_size, const ISocket* socket)const{
    s32 ret = ::recv(socket->GetSocket(), (char*)buffer, buffer_size , 0);
    return ret;
}