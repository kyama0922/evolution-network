#ifndef __EVOLUTION_NETWORK_RESULT_H__
#define __EVOLUTION_NETWORK_RESULT_H__


namespace EVOLUTION{
    namespace NETWORK{

        struct NetworkResult{
            enum _RESULT{
                //----------------------------成功----------------------------
                RESULT_OK = 0x00000000,//成功
                NONE_ACCEPT_SOCKET    ,//アクセプト要求がありません

                //----------------------------失敗----------------------------
                UNKNOWN_FAILED = 0x80000000, //失敗
                NONE_INSTANCE,               //インスタンスがありません
                CREATE_FAILED,               //作成に失敗
                GET_IPADDR_FAILED,           //IPアドレスの取得に失敗
                CONNECT_SOCKET_FAILED,       //ソケットの作成に失敗
                CONNECT_FAILED,              //接続に失敗
                BIND_FAILED,                 //BINDに失敗
                LISTEN_FAILED,               //LISTENに失敗
                CREATE_PROTOCOL_FAILED,             //プロトコルの作成に失敗
                CREATE_SOCKET_FAILED,               //ソケットの作成に失敗
            };

        };

        struct ERR{
            enum _ERROR{
                _EPERM = 1,
                _ENOENT = 2,
                _ESRCH = 3,
                _EINTR = 4,
                _EIO = 5,
                _ENXIO = 6,
                _E2BIG = 7,
                _ENOEXEC = 8,
                _EBADF = 9,
                _ECHILD = 10,
                _EAGAIN = 11,
                _ENOMEM = 12,
                _EACCES = 13,
                _EFAULT = 14,
                _ENOTBLK = 15,
                _EBUSY = 16,
                _EEXIST = 17,
                _EXDEV = 18,
                _ENODEV = 19,
                _ENOTDIR = 20,
                _EISDIR = 21,
                _EINVAL = 22,
                _ENFILE = 23,
                _EMFILE = 24,
                _ENOTTY = 25,
                _ETXTBSY = 26,
                _EFBIG = 27,
                _ENOSPC = 28,
                _ESPIPE = 29,
                _EROFS = 30,
                _EMLINK = 31,
                _EPIPE = 32,
                _EDOM = 33,
                _ERANGE = 34,
                _EDEADLK = 35,
                _ENAMETOOLONG = 36,
                _ENOLCK = 37,
                _ENOSYS = 38,
                _ENOTEMPTY = 39,
                _ELOOP = 40,
                _EWOULDBLOCK = _EAGAIN,
                _ENOMSG = 42,
                _EIDRM = 43,
                _ECHRNG = 44,
                _EL2NSYNC = 45,
                _EL3HLT = 46,
                _EL3RST = 47,
                _ELNRNG = 48,
                _EUNATCH = 49,
                _ENOCSI = 50,
                _EL2HLT = 51,
                _EBADE = 52,
                _EBADR = 53,
                _EXFULL = 54,
                _ENOANO = 55,
                _EBADRQC = 56,
                _EBADSLT = 57,
                _EDEADLOCK = _EDEADLK,
                _EBFONT = 59,
                _ENOSTR = 60,
                _ENODATA = 61,
                _ETIME = 62,
                _ENOSR = 63,
                _ENONET = 64,
                _ENOPKG = 65,
                _EREMOTE = 66,
                _ENOLINK = 67,
                _EADV = 68,
                _ESRMNT = 69,
                _ECOMM = 70,
                _EPROTO = 71,
                _EMULTIHOP = 72,
                _EDOTDOT = 73,
                _EBADMSG = 74,
                _EOVERFLOW = 75,
                _ENOTUNIQ = 76,
                _EBADFD = 77,
                _EREMCHG = 78,
                _ELIBACC = 79,
                _ELIBBAD = 80,
                _ELIBSCN = 81,
                _ELIBMAX = 82,
                _ELIBEXEC = 83,
                _EILSEQ = 84,
                _ERESTART = 85,
                _ESTRPIPE = 86,
                _EUSERS = 87,
                _ENOTSOCK = 88,
                _EDESTADDRREQ = 89,
                _EMSGSIZE = 90,
                _EPROTOTYPE = 91,
                _ENOPROTOOPT = 92,
                _EPROTONOSUPPORT = 93,
                _ESOCKTNOSUPPORT = 94,
                _EOPNOTSUPP = 95,
                _EPFNOSUPPORT = 96,
                _EAFNOSUPPORT = 97,
                _EADDRINUSE = 98,
                _EADDRNOTAVAIL = 99,
                _ENETDOWN = 100,
                _ENETUNREACH = 101,
                _ENETRESET = 102,
                _ECONNABORTED = 103,
                _ECONNRESET = 104,
                _ENOBUFS = 105,
                _EISCONN = 106,
                _ENOTCONN = 107,
                _ESHUTDOWN = 108,
                _ETOOMANYREFS = 109,
                _ETIMEDOUT = 110,
                _ECONNREFUSED = 111,
                _EHOSTDOWN = 112,
                _EHOSTUNREACH = 113,
                _EALREADY = 114,
                _EINPROGRESS = 115,
                _ESTALE = 116,
                _EUCLEAN = 117,
                _ENOTNAM = 118,
                _ENAVAIL = 119,
                _EISNAM = 120,
                _EREMOTEIO = 121,
                _EDQUOT = 122,
                _ENOMEDIUM = 123,
                _EMEDIUMTYPE = 124,
                _ECANCELED = 125,
                _ENOKEY = 126,
                _EKEYEXPIRED = 127,
                _EKEYREVOKED = 128,
                _EKEYREJECTED = 129,
                _EOWNERDEAD = 130,
                _ENOTRECOVERABLE = 131,
            };
        };


        struct CONNECT_ERROR{
            enum _CONNECT_ERROR{
                NONE = 0,                   //ERROR無し
                ACCES = ERR::_EACCES,         //UNIX ドメインソケットはパス名で識別される。 ソケット・ファイルへの書き込み許可がなかったか、パス名へ 到達するまでのディレクトリのいずれかに対する検索許可がなかった
                PERM = ERR::_EPERM,           //ソケットのブロードキャスト・フラグが有効になっていないのに ユーザがブロードキャストへ接続を試みた。または、ローカルのファイアウォールの 規則により接続の要求が失敗した。 
                ADDRINUSE = ERR::_EADDRINUSE,    //ローカルアドレスが既に使用されている。 
                ADDRNOTAVAIL = ERR::_EADDRNOTAVAIL, //sockfd が参照するソケットがそれ以前にアドレスにバインドされておらず、 そのソケットに一時ポートをバインドしようとした際に、 一時ポートとして使用する範囲のポート番号がすべて使用中であった。
                AFNOSUPPORT = ERR::_EAFNOSUPPORT,  //渡されたアドレスの sa_family フィールドが正しいアドレス・ファミリーではない。
                AGAIN = ERR::_EAGAIN,         //ルーティングキャッシュにエントリーが十分にない。 
                ALREADY = ERR::_EALREADY,     //ソケットが非停止 (nonblocking) に設定されており、 前の接続が完了していない。 
                BADF = ERR::_EBADF,          //ファイルディスクリプターがディスクリプターテーブルの 有効なインデックスではない。 
                CONNREFUSED = ERR::_ECONNREFUSED,  //リモートアドレスで接続を待っているプログラムがない
                FAULT = ERR::_EFAULT,      //ソケット構造体のアドレスがユーザーのアドレス空間外にある。 
                INPROGRESS = ERR::_EINPROGRESS,   //ソケットが非停止 (nonblocking) に設定されていて、接続をすぐに 完了することができない
                INTR = ERR::_EINTR,          //捕捉されたシグナルによりシステムコールが中断された
                ISCONN = ERR::_EISCONN,      //ソケットは既に接続 (connect) されている。 
                NETUNREACH = ERR::_ENETUNREACH,   //到達できないネットワークである。 
                NOTSOCK = ERR::_ENOTSOCK,      //ファイルディスクリプターがソケットと関連付けられていない。 
                TIMEDOUT = ERR::_ETIMEDOUT,    //接続を試みている途中で時間切れ (timeout) になった。サーバーが混雑していて 新たな接続を受け入れられないのかもしれない
            };
        };
    }
}

#endif // !__EVOLUTION_NETWORK_RESULT_H__