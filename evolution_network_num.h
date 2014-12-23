#ifndef __EVOLUTION_NETWORK_NUM_H_
#define __EVOLUTION_NETWORK_NUM_H_

#include <evolution.h>

namespace EVOLUTION{
    namespace NETWORK{

        /*
        _UNSPEC = 0, // unspecified
        _UNIX = 1, // local to host (pipes, portals)
        _INET = 2, // internetwork: UDP, TCP, etc.
        _IMPLINK = 3, // arpanet imp addresses
        _PUP = 4, // pup protocols: e.g. BSP
        _CHAOS = 5, // mit CHAOS protocols
        _NS = 6, // XEROX NS protocols
        _IPX = _NS, // IPX protocols: IPX, SPX, etc.
        _ISO = 7, // ISO protocols
        _OSI = _ISO, // OSI is ISO
        _ECMA = 8, // european computer manufacturers
        _DATAKIT = 9, // datakit protocols
        _CCITT = 10, // CCITT protocols, X.25 etc
        _SNA = 11, // IBM SNA
        _DECnet = 12, // DECnet
        _DLI = 13, // Direct data link interface
        _LAT = 14, // LAT
        _HYLINK = 15, // NSC Hyperchannel
        _APPLETALK = 16, // AppleTalk
        _NETBIOS = 17, // NetBios-style addresses
        _VOICEVIEW = 18, // VoiceView
        _FIREFOX = 19, // Protocols from Firefox
        _UNKNOWN1 = 20, // Somebody is using this!
        _BAN = 21, // Banyan
        _ATM = 22, // Native ATM Services
        _INET6 = 23, // Internetwork Version 6
        _CLUSTER = 24, // Microsoft Wolfpack
        _12844 = 25, // IEEE 1284.4 WG AF
        _IRDA = 26, // IrDA
        _NETDES = 28, // Network Designers OSI & gateway
        */
        struct ADDRESSFAMILY {
            enum _ADDRESSFAMILY {
                _UNSPEC = 0, // unspecified
                _UNIX = 1, // local to host (pipes, portals)
                _INET = 2, // internetwork: UDP, TCP, etc.
                _IMPLINK = 3, // arpanet imp addresses
                _PUP = 4, // pup protocols: e.g. BSP
                _CHAOS = 5, // mit CHAOS protocols
                _NS = 6, // XEROX NS protocols
                _IPX = _NS, // IPX protocols: IPX, SPX, etc.
                _ISO = 7, // ISO protocols
                _OSI = _ISO, // OSI is ISO
                _ECMA = 8, // european computer manufacturers
                _DATAKIT = 9, // datakit protocols
                _CCITT = 10, // CCITT protocols, X.25 etc
                _SNA = 11, // IBM SNA
                _DECnet = 12, // DECnet
                _DLI = 13, // Direct data link interface
                _LAT = 14, // LAT
                _HYLINK = 15, // NSC Hyperchannel
                _APPLETALK = 16, // AppleTalk
                _NETBIOS = 17, // NetBios-style addresses
                _VOICEVIEW = 18, // VoiceView
                _FIREFOX = 19, // Protocols from Firefox
                _UNKNOWN1 = 20, // Somebody is using this!
                _BAN = 21, // Banyan
                _ATM = 22, // Native ATM Services
                _INET6 = 23, // Internetwork Version 6
                _CLUSTER = 24, // Microsoft Wolfpack
                _12844 = 25, // IEEE 1284.4 WG AF
                _IRDA = 26, // IrDA
                _NETDES = 28, // Network Designers OSI & gateway
            };
        };

        /*
         RECEIVE = 0x00, //SHUT_RD
         SEND = 0x01,    //SHUT_WR
         BOTH = 0x02,    //SHUT_RDWR
         NONE = 0xFF,    //SHUT_RDWR
         */
        struct SHUTDOWN{
            enum _SHUTDOWN{
                RECEIVE = 0x00, //SHUT_RD
                SEND = 0x01,    //SHUT_WR
                BOTH = 0x02,    //SHUT_RDWR
                NONE = 0xFF,    //SHUT_RDWR
            };
        };

        struct BLOCKINGMODE{
            enum _BLOCKINGMODE{
                BLOCK = 0x00, //BLOCK
                NOBLOCK = 0x01,    //NOBLOCK
            };
        };

        struct IPADDR{
            union{
                u8 u_addr_b[4];
                u16 u_addr_s[2];
                u32 u_addr;
            }Addr;
        };

        struct SOCKET_DESC{
            IPADDR ip;
            u16    port;
            ADDRESSFAMILY::_ADDRESSFAMILY addr_family;
        };

#define EVOLUTION_IP_SET(ip1,ip2,ip3,ip4) ((ip4 << 24) | (ip3 << 16) | (ip2 << 8) | (ip1))

        EVOLUTION_INLINE u32 IP_Convert(u8 ip1, u8 ip2, u8 ip3, u8 ip4){
            return ((ip4 << 24) | (ip3 << 16) | (ip2 << 8) | (ip1));
        }

        //ファイルディスクリプタの最大数
#if defined(_WIN32) || defined(_WIN64) 
        const u32 FILE_DESCRIPTOR_SIZE = 65536;
#elif defined(_LINUX)
        const u32 FILE_DESCRIPTOR_SIZE = FD_SETSIZE;
#endif

#ifndef DEF_SOCKET
#define DEF_SOCKET
        typedef EVOLUTION::u32 SOCKET;
#endif

    }
}


#endif //!__EVOLUTION_NETWORK_NUM_H_