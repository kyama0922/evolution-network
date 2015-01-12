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
    //IpV4プロトコルの作成
    if (addr_family == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET)
    {
        ProtocolINetv4* protocolv4 = NEW ProtocolINetv4;
        if (protocolv4 == nullptr)
        {
            return NetworkResult::CREATE_FAILED;
        }
        NetworkResult::_RESULT ret = protocolv4->Create(host_name, port);
        if (EVOLUTION_FAILED(ret))
        {
            EVOLUTION_RELEASE(protocolv4);
            return ret;
        }
        *pp_protocol = protocolv4;
        return NetworkResult::RESULT_OK;
    }
    //IpV6プロトコルの作成
    else if (addr_family == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET)
    {
        return NetworkResult::CREATE_FAILED;
    }

    return NetworkResult::CREATE_FAILED;
}
//プロトコルを作成します。
NetworkResult::_RESULT NetworkFactory::CreateProtocol(IProtocol** pp_protocol, IPADDR_V4 ip4, u16 port){
    *pp_protocol = nullptr;
    ProtocolINetv4* protocolv4 = NEW ProtocolINetv4;
    if (protocolv4 == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = protocolv4->Create(ip4, port);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(protocolv4);
        return ret;
    }
    *pp_protocol = protocolv4;
    return NetworkResult::RESULT_OK;
}

//プロトコルを作成します。
NetworkResult::_RESULT NetworkFactory::CreateProtocol(IProtocol** pp_protocol, IPADDR_V6 ip6, u16 port){
    return NetworkResult::CREATE_FAILED;
}

//コネクトソケットを作成します。
NetworkResult::_RESULT NetworkFactory::CreateTCPConnectSocket(ITCPConnectSocket** pp_connect_socket, IProtocol* protocol){
    *pp_connect_socket = nullptr;
    NetworkResult::_RESULT ret = NetworkResult::RESULT_OK;
    TCPConnectSocket* connect_socket = NEW TCPConnectSocket();
    if (connect_socket == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }

    ret = connect_socket->Create(protocol);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(connect_socket);
        return NetworkResult::CREATE_FAILED;
    }
    *pp_connect_socket = connect_socket;
    return NetworkResult::RESULT_OK;
}
//TCPバインドソケットを作成します。
NetworkResult::_RESULT NetworkFactory::CreateTCPBindSocket(ITCPBindSocket** pp_bind_socket, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family){
    *pp_bind_socket = nullptr;
    TCPBindSocket* tcp_bindsocket = NEW TCPBindSocket();
    NetworkResult::_RESULT ret = NetworkResult::RESULT_OK;
    if (tcp_bindsocket == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }

    IProtocol* protocol = nullptr;
    if (addr_family == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET)
    {
        IPADDR_V4 ip_addr;
        ip_addr.Addr.u_addr = 0x00000000;
        ret = this->CreateProtocol(&protocol, ip_addr, port);
        if (EVOLUTION_FAILED(ret))
        {
            EVOLUTION_RELEASE(protocol);
            EVOLUTION_RELEASE(tcp_bindsocket);
            return ret;
        }
    }
    else if (addr_family == EVOLUTION::NETWORK::ADDRESSFAMILY::_INET6)
    {
        IPADDR_V6 ip_addr;
        ip_addr.Addr.u_addr_ll[0] = 0x0000000000000000;
        ip_addr.Addr.u_addr_ll[1] = 0x0000000000000000;
        ret = this->CreateProtocol(&protocol, ip_addr, port);
        if (EVOLUTION_FAILED(ret))
        {
            EVOLUTION_RELEASE(protocol);
            EVOLUTION_RELEASE(tcp_bindsocket);
            return ret;
        }
    }
    else
    {
        EVOLUTION_RELEASE(tcp_bindsocket);
        return NetworkResult::CREATE_FAILED;
    }
    ret = tcp_bindsocket->Create(protocol);
    EVOLUTION_RELEASE(protocol);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(tcp_bindsocket);
        return ret;
    }
    *pp_bind_socket = tcp_bindsocket;
    return NetworkResult::RESULT_OK;
}
//TCPバインドソケットを作成します。
NetworkResult::_RESULT NetworkFactory::CreateTCPBindSocket(ITCPBindSocket** pp_bind_socket, IProtocol* protocol){
    *pp_bind_socket = nullptr;
    TCPBindSocket* tcp_bindsocket = NEW TCPBindSocket();
    
    if (tcp_bindsocket == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = tcp_bindsocket->Create(protocol);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(tcp_bindsocket);
        return ret;
    }
    *pp_bind_socket = tcp_bindsocket;
    return NetworkResult::CREATE_FAILED;
}
//コネクトソケットを作成します。
NetworkResult::_RESULT NetworkFactory::CreateUDPTransceiverSocket(IUDPTransceiverSocket** pp_udp_transceiver_socket, IProtocol* protocol){
    *pp_udp_transceiver_socket = nullptr;
    UDPTransceiverSocket* udp_transceiversocket = NEW UDPTransceiverSocket();

    if (udp_transceiversocket == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = udp_transceiversocket->Create(protocol);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(udp_transceiversocket);
        return ret;
    }
    *pp_udp_transceiver_socket = udp_transceiversocket;
    return NetworkResult::RESULT_OK;
}
//UDPバインドソケットを作成します。
NetworkResult::_RESULT NetworkFactory::CreateUDPBindSocket(IUDPBindSocket** pp_udp_bind_socket, u16 port, ADDRESSFAMILY::_ADDRESSFAMILY addr_family){
    *pp_udp_bind_socket = nullptr;
    UDPBindSocket* udp_bindsocket = NEW UDPBindSocket();

    if (udp_bindsocket == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = udp_bindsocket->Create(this, port, addr_family);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(udp_bindsocket);
        return ret;
    }
    *pp_udp_bind_socket = udp_bindsocket;
    return NetworkResult::RESULT_OK;
}
//UDPバインドソケットを作成します。
NetworkResult::_RESULT NetworkFactory::CreateUDPBindSocket(IUDPBindSocket** pp_udp_bind_socket, IProtocol* protocol){
    *pp_udp_bind_socket = nullptr;
    UDPBindSocket* udp_bindsocket = NEW UDPBindSocket();

    if (udp_bindsocket == nullptr)
    {
        return NetworkResult::CREATE_FAILED;
    }
    NetworkResult::_RESULT ret = udp_bindsocket->Create(this, protocol);
    if (EVOLUTION_FAILED(ret))
    {
        EVOLUTION_RELEASE(udp_bindsocket);
        return ret;
    }
    *pp_udp_bind_socket = udp_bindsocket;
    return NetworkResult::RESULT_OK;
}