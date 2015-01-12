#include "../evolution_network_implement.h"
#include <WinSock2.h>
#pragma comment(lib ,"Ws2_32.lib" )

using namespace EVOLUTION;
using namespace EVOLUTION::NETWORK;

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateNetworkFactory(NETWORK::INetworkFactory** pp_network_factory){
    static struct WIN_FACTORY{
        EVOLUTION::NETWORK::NetworkFactory* p_factory;
        WSADATA wsaData;
        s32 startup_err;
        WIN_FACTORY() : p_factory(nullptr)
        {
            // winsock2の初期化
            startup_err = WSAStartup(MAKEWORD(2, 0), &wsaData);
        }

        ~WIN_FACTORY(){
            p_factory->Release();
            // winsock2の終了処理
            WSACleanup();
        }
    }_f;
    *pp_network_factory = nullptr;
    if (_f.p_factory == nullptr)
    {
        _f.p_factory = new NetworkFactory();
        if (_f.p_factory == nullptr)
        {
            return EVOLUTION::_RESULT::E_unknown;
        }
        if (EVOLUTION_FAILED(_f.p_factory->Create()))
        {
            EVOLUTION_RELEASE(_f.p_factory);
            return EVOLUTION::_RESULT::E_unknown;
        }
    }

    _f.p_factory->AddRef();
    *pp_network_factory = _f.p_factory;

    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::GetAddress(NETWORK::IPADDR_V4& out, const c8* hostname){
    out.Addr.u_addr = inet_addr((const char*)hostname);
    if (out.Addr.u_addr == 0xFFFFFFFF){
        struct hostent *host;

        host = gethostbyname((const char*)hostname);
        if (host == NULL) {
            if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
            }
            out.Addr.u_addr = 0xFFFFFFFF;
            return EVOLUTION::_RESULT::E_unknown;
        }
        out.Addr.u_addr = *(u32 *)host->h_addr_list[0];
    }
    return EVOLUTION::_RESULT::S_ok;
}