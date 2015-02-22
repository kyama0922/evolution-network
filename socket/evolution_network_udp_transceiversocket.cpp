#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

//IUnknown
u32 UDPTransceiverSocket::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT UDPTransceiverSocket::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
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
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUDPTransceiverSocket))
    {
        *ppvObject = static_cast<IUDPTransceiverSocket *>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_UDPTransceiverSocket))
    {
        *ppvObject = static_cast<UDPTransceiverSocket *>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 UDPTransceiverSocket::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}


UDPTransceiverSocket::UDPTransceiverSocket():mp_protocol(nullptr){

}
UDPTransceiverSocket::~UDPTransceiverSocket(){
    this->CloseSocket();
    EVOLUTION_RELEASE(this->mp_protocol);
}

NetworkResult::_RESULT UDPTransceiverSocket::Create(IProtocol* protocol){
    protocol->AddRef();
    this->mp_protocol = protocol;

    this->m_socket = ::socket(this->mp_protocol->GetAddrFamily(), SOCKET_TYPE::DGRAM, 0);
    if ((s32)this->m_socket  < 0)
    {
        return NetworkResult::CONNECT_SOCKET_FAILED;
    }
    return NetworkResult::RESULT_OK;
}

//ソケットを取得
EVOLUTION::NETWORK::SOCKET UDPTransceiverSocket::GetSocket()const{
    return this->m_socket;
}

//ソケットをシャットダウンして終了させます。
void UDPTransceiverSocket::CloseSocket(){
    ::closesocket(this->m_socket);
}

//ソケットを閉じます(オプション設定可)
void UDPTransceiverSocket::ShutdownSocket(SHUTDOWN::_SHUTDOWN mode){
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
const IProtocol* UDPTransceiverSocket::GetProtocol()const{
    return this->mp_protocol;
}

//ブロッキング設定をします。
void UDPTransceiverSocket::SetBlockMode(bool flag){
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
bool UDPTransceiverSocket::IsBlocking()const{
    return EVOLUTION_IS_STATE(this->m_flag, BLOCKINGMODE::BLOCK);
}


//送信
s32 UDPTransceiverSocket::Send(const void* buffer, s32 buffer_size)const{
    EVOLUTION::NETWORK::ADDRESSFAMILY::_ADDRESSFAMILY af = this->mp_protocol->GetAddrFamily();
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

        ret = ::sendto(this->m_socket, (const char*)buffer, buffer_size, 0, (struct sockaddr*)&sock_in, sizeof(sock_in));
    }
    else if (af = EVOLUTION::NETWORK::ADDRESSFAMILY::_INET6)
    {

    }
    return ret;
}

//受信
s32 UDPTransceiverSocket::Receive(void* buffer, s32 buffer_size)const{
    //src_addrで初期化されたサイズ指定
    //s32 sock_len = (this->mp_protocol->GetAddrFamily() == ADDRESSFAMILY::_INET) ? sizeof(struct sockaddr_in) :/* sizeof(struct sockaddr_in)*/-1;
    //struct sockaddr _sockaddr;
    s32 ret = recvfrom(this->m_socket, (char*)buffer, buffer_size, 0, nullptr, nullptr);
    return ret;
}