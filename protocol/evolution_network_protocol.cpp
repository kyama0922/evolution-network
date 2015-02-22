#include "../evolution_network_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;


//IUnknown
u32 ProtocolINetv4::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT ProtocolINetv4::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IProtocol))
    {
        *ppvObject = static_cast<IProtocol *>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_ProtocolINetv4))
    {
        *ppvObject = static_cast<ProtocolINetv4 *>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 ProtocolINetv4::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

ProtocolINetv4::ProtocolINetv4(){

}

ProtocolINetv4::~ProtocolINetv4(){

}

NetworkResult::_RESULT ProtocolINetv4::Create(const c8* host_name, u16 port){
    if (EVOLUTION::FUNCTION::GetAddress(this->m_ip, host_name))
    {
        return NetworkResult::GET_IPADDR_FAILED;
    }
    this->m_port = port;
    return NetworkResult::RESULT_OK;
}

NetworkResult::_RESULT ProtocolINetv4::Create(IPADDR_V4 ip, u16 port){
    this->m_ip = ip;
    this->m_port = port;
    return NetworkResult::RESULT_OK;
}

//IPアドレスを取得します。
const IPADDR_V4& ProtocolINetv4::GetipAddr()const{
    return this->m_ip;
}

//ポート番号を取得します。
u16 ProtocolINetv4::GetPort()const{
    return this->m_port;
}

//アドレスファミリーを取得します。
ADDRESSFAMILY::_ADDRESSFAMILY ProtocolINetv4::GetAddrFamily()const{
    return ADDRESSFAMILY::_INET;
}