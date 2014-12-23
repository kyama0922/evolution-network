#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;


//IUnknown
u32 Protocol::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT Protocol::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
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

u32 Protocol::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

Protocol::Protocol(){

}

Protocol::~Protocol(){

}

NetworkResult::_RESULT Protocol::Create(const c8* host_name, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family){
    if (EVOLUTION::FUNCTION::GetAddress(this->m_desc.ip, host_name))
    {
        return NetworkResult::GET_IPADDR_FAILED;
    }
    this->m_desc.port = port;
    this->m_desc.addr_family = addr_family;
    return NetworkResult::RESULT_OK;
}

NetworkResult::_RESULT Protocol::Create(IPADDR ip, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family){
    this->m_desc.ip = ip;
    this->m_desc.port = port;
    this->m_desc.addr_family = addr_family;
    return NetworkResult::RESULT_OK;
}

NetworkResult::_RESULT Protocol::Create(const SOCKET_DESC& desc){
    this->m_desc.ip = desc.ip;
    this->m_desc.port = desc.port;
    this->m_desc.addr_family = desc.addr_family;
    return NetworkResult::RESULT_OK;
}

//プロトコルを取得します。
void Protocol::GetDesc(SOCKET_DESC* desc)const{
    desc->ip = this->m_desc.ip;
    desc->port = this->m_desc.port;
    desc->addr_family = this->m_desc.addr_family;
}

//IPアドレスを取得します。
const IPADDR& Protocol::GetipAddr()const{
    return this->m_desc.ip;
}

//ポート番号を取得します。
u16 Protocol::GetPort()const{
    return this->m_desc.port;
}

//アドレスファミリーを取得します。
ADDRESSFAMILY::_ADDRESSFAMILY Protocol::GetAddrFamily()const{
    return this->m_desc.addr_family;
}