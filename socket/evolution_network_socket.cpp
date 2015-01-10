#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

//IUnknown
u32 Socket::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT Socket::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IProtocol))
    {
        *ppvObject = static_cast<IProtocol *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_Protocol))
    {
        *ppvObject = static_cast<Protocol *>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 Socket::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

Socket::Socket() :m_socket(-1){

}

Socket::~Socket(){

}

NetworkResult::_RESULT Socket::Create(IProtocol* protocol){
    SOCKET_DESC desc;
    protocol->GetDesc(&desc);

}

//ソケットを取得
SOCKET Socket::GetSocket()const{

}

//ソケットをシャットダウンして終了させます。
void Socket::CloseSocket(){

}

//ソケットを閉じます(オプション設定可)
void Socket::ShutdownSocket(SHUTDOWN::_SHUTDOWN mode){

}

//プロトコル情報を取得します。
const IProtocol* Socket::GetProtocol()const{

}

//ブロッキング設定をします。
void Socket::SetBlockMode(BLOCKINGMODE::_BLOCKINGMODE mode){

}

//ブロッキング状態を確認します。
bool Socket::IsBlocking(){

}