#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

//IUnknown
u32 NetworkFactory::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT NetworkFactory::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_INetworkFactory))
    {
        *ppvObject = static_cast<INetworkFactory *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_NetworkFactory))
    {
        *ppvObject = static_cast<NetworkFactory *>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 NetworkFactory::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}


NetworkFactory::NetworkFactory(){

}

NetworkFactory::~NetworkFactory(){

}

NetworkResult::_RESULT NetworkFactory::Create(){
    return NetworkResult::RESULT_OK;
}

//プロトコルを作成します。
NetworkResult::_RESULT NetworkFactory::CreateProtocol(IProtocol** pp_protocol, const c8* host_name, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family){
    *pp_protocol = nullptr;
    Protocol* protocol = NEW Protocol;
    if (protocol == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = protocol->Create(host_name, port, addr_family);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(protocol);
        return ret;
    }
    *pp_protocol = protocol;
    return NetworkResult::RESULT_OK;
}

//プロトコルを作成します。
NetworkResult::_RESULT NetworkFactory::CreateProtocol(IProtocol** pp_protocol, IPADDR ip, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family){
    *pp_protocol = nullptr;
    Protocol* protocol = NEW Protocol;
    if (protocol == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = protocol->Create(ip, port, addr_family);
    if (EVOLUTION_FAILED(ret))
    {
        return ret;
    }
    *pp_protocol = protocol;
    return NetworkResult::RESULT_OK;
}

//プロトコルを作成します。
NetworkResult::_RESULT NetworkFactory::CreateProtocol(IProtocol** pp_protocol, const SOCKET_DESC& desc){
    *pp_protocol = nullptr;
    Protocol* protocol = NEW Protocol();
    if (protocol == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = protocol->Create(desc);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(protocol);
        return ret;
    }
    *pp_protocol = protocol;
    return NetworkResult::RESULT_OK;
}

//ソケットを作成します。
NetworkResult::_RESULT NetworkFactory::CreateSocket(ISocket** pp_socket, IProtocol* protocol){
    *pp_socket = nullptr;
    Socket* socket = NEW Socket();
    if (protocol == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = protocol->Create(desc);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(protocol);
        return ret;
    }
    *pp_socket = protocol;
    return NetworkResult::RESULT_OK;
    return NetworkResult::CREATE_FAILED;
}

NetworkResult::_RESULT NetworkFactory::CreateListenerSocket(IListenerSocket** pp_listener_socket, IProtocol* protocol){
    return NetworkResult::CREATE_FAILED;
}