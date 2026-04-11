/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */

#ifndef VTCP_H
#define VTCP_H

#ifdef WIN32

#include <WinSock2.h>

#ifndef int64
typedef __int64 int64;	
#endif

#ifndef socklen_t
#define socklen_t int
#endif

#else

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#ifndef int64
typedef __int64_t int64;	
#endif

#endif


#define VTCP_OK				int(0)
#define VTCP_ERROR			int(-1)
#define VTCP_INVALID_SOCKET	int(-1)

typedef int		VTCP_SOCKET;
typedef void *	VTCP_QIO_HANDLE;


struct SVTcpKeepAlive 
{
	unsigned long onoff;
	unsigned long keepalivetime;
	unsigned long keepaliveinterval;
};

struct SVTcpLinger 
{
	unsigned short l_onoff;
	unsigned short l_linger;
};

struct SVTcpRSVP
{
	unsigned long rsvp_min;	//KB/s
	unsigned long rsvp_max;	//KB/s

};

#define VTCP_MAX_FD_SET_COUNT 128

typedef struct SVTcpFdSet
{
	int fd_count;

	VTCP_SOCKET fd_array[VTCP_MAX_FD_SET_COUNT];

}S_VTCP_FD_SET,*PS_VTCP_FD_SET;


typedef struct SVTcpStatCount					//״̬ͳ����Ϣ
{	
	int sizeOfStruct;							//�ṹ��С

	unsigned long version;						//�汾
	
	unsigned long time;							//ʱ����
	
	int64	count_recv_bytes;					//�������ֽ�
	int64	count_recv_bytes_cur;				//�������ֽڣ���ǰ�ٶȣ�
	int64	count_send_bytes;					//�������ֽ�
	int64	count_send_bytes_cur;				//�������ֽڣ���ǰ�ٶȣ�

	int64	count_do_send_data_rep;				//�������������ظ�����
	int64	count_do_send_data;					//����������������
	int64	count_do_send_data_ack;				//������������Ӧ�����
	int64	count_do_send_sync;					//����ͬ��������
	int64	count_do_send_sync_ack;				//����ͬ����Ӧ�����

	int64	count_on_recv_data_rep;				//�յ����������ظ�����
	int64	count_on_recv_data;					//�յ�������������
	int64	count_on_recv_data_ack;				//�յ���������Ӧ�����
	int64	count_on_recv_sync;					//�յ�ͬ��������
	int64	count_on_recv_sync_ack;				//�յ�ͬ����Ӧ�����

	int		tcp_rtt;							//��������
	int		tcp_cwnd;							//���ʹ���
	int		tcp_cwnd_ssthresh;					//���ʹ��ڷ�ֵ

	int		count_async_opt;					//Ӧ�ò��첽���и���
	int		count_pm_r;							//�ں˰����ն���
	int		count_pm_s;							//�ں˰����Ͷ���

	unsigned char grap_r[128];					//������״̬λͼ
	unsigned char grap_s[128];					//������״̬λͼ


}S_VTCP_STAT_COUNT,*PS_VTCP_STAT_COUNT;


enum EVTcpErrorCode
{
	VTCP_ERROR_NOT_ENOUGH_MEMORY		= 1,	//�ڴ治��
	VTCP_ERROR_INVALID_PARAMETER		= 2,	//��������
	VTCP_ERROR_INVALID_STATE			= 3,	//���״̬����
	VTCP_ERROR_INVALID_SOCKET			= 4,	//�������
	VTCP_ERROR_TIMEOUT					= 5,	//������ʱ
	VTCP_ERROR_WOULDBLOCK				= 7,	//�첽�赲
	VTCP_ERROR_CONNRESET				= 8,	//Զ�̹ر�������
	VTCP_ERROR_CONNABORTED				= 9,	//���عر�������
	VTCP_ERROR_CONNREFUSED				= 10,	//���ӱ������ܾ�
	VTCP_ERROR_MSG_SIZE					= 11,	//��Ϣ�ߴ����
	VTCP_ERROR_CANCELLED				= 12,	//������ȡ��
	VTCP_ERROR_NOT_FOUND				= 13,	//����δ����
	VTCP_ERROR_BUSY						= 14,	//ϵͳ��æ
	VTCP_ERROR_SYSTEM_FAIL				= 15,	//ϵͳ����ʧ��
	VTCP_ERROR_NETRESET					= 16,	//�򱣻���ʧ�ܶ�����

};

enum EVTcpSoOpt
{
	VTCP_SO_CONNECT_TIMEO				= 1,	//���ӳ�ʱ(unsigned long)(���룩
	VTCP_SO_RECV_TIMEO					= 2,	//���ճ�ʱ(unsigned long)(���룩
	VTCP_SO_RECVFROM_TIMEO				= 3,	//���ճ�ʱ(unsigned long)(���룩
	VTCP_SO_SEND_TIMEO					= 4,	//���ͳ�ʱ(unsigned long)(���룩
	VTCP_SO_SENDTO_TIMEO				= 5,	//���ͳ�ʱ(unsigned long)(���룩
	VTCP_SO_LINGER						= 6,	//����ʱ��(SVTcpLinger)
	VTCP_SO_KEEPALIVE					= 7,	//��������(SVTcpKeepAlive)
	VTCP_SO_RSVP						= 8,	//��ԴԤ��(SVTcpRSVP)(��Ƶ����)
	VTCP_SO_STAT_COUNT					= 9,	//ͳ����Ϣ(SVTcpStatCount)
	VTCP_SO_LOSS_PERCENT				= 10,	//��������(int)(�ٷֱ�)(0~100)

};

enum EVTcpQIOEvent
{
	VTCP_QIO_EVENT_ACCEPT		= 1, //����VTCP_QIO_EVENT_RECV
	VTCP_QIO_EVENT_CONNECT		= 2, //����VTCP_QIO_EVENT_SEND
	VTCP_QIO_EVENT_RECV			= 3,
	VTCP_QIO_EVENT_RECVFROM		= 4,
	VTCP_QIO_EVENT_SEND			= 5,
	VTCP_QIO_EVENT_SENDTO		= 6,

};


enum EVTcpCtl
{
	VTCP_CTL_GET_NONBIO			= 1,
	VTCP_CTL_SET_NONBIO			= 2,

};


#endif

#ifdef WIN32
#define VTCP_EXPORT_API(t) t WINAPI		
#else
#define VTCP_EXPORT_API(t) extern "C" t
#endif

//APIʹ�ð��� WWW.VTCP123.COM  

VTCP_EXPORT_API(VTCP_SOCKET		)vtcp_accept		(VTCP_SOCKET s, sockaddr * sai, socklen_t * sailen);
VTCP_EXPORT_API(int				)vtcp_bind			(VTCP_SOCKET s, const struct sockaddr * sai, socklen_t sailen);
VTCP_EXPORT_API(int				)vtcp_cleanup		();
VTCP_EXPORT_API(int				)vtcp_close			(VTCP_SOCKET s);
VTCP_EXPORT_API(int				)vtcp_connect		(VTCP_SOCKET s, const struct sockaddr * sai, socklen_t sailen);
VTCP_EXPORT_API(int				)vtcp_ctl			(VTCP_SOCKET s, EVTcpCtl ctl,unsigned long * p);
VTCP_EXPORT_API(int				)vtcp_geterror		();
VTCP_EXPORT_API(int				)vtcp_getsockname	(VTCP_SOCKET s, struct sockaddr * sai, socklen_t * sailen);
VTCP_EXPORT_API(int				)vtcp_getpeername	(VTCP_SOCKET s, struct sockaddr * sai, socklen_t * sailen);
VTCP_EXPORT_API(int				)vtcp_listen		(VTCP_SOCKET s, int backlog);
VTCP_EXPORT_API(int				)vtcp_recv			(VTCP_SOCKET s, char * buffer, int cb, int flag);
VTCP_EXPORT_API(int				)vtcp_recvfrom		(VTCP_SOCKET s, char * buffer, int cb, int flag, struct sockaddr * from, socklen_t * fromlen);
VTCP_EXPORT_API(int				)vtcp_send			(VTCP_SOCKET s, char * buffer, int cb, int flag);
VTCP_EXPORT_API(int				)vtcp_sendto		(VTCP_SOCKET s, char * buffer, int cb, int flag, const struct sockaddr * to, socklen_t tolen);
VTCP_EXPORT_API(int				)vtcp_getsockopt	(VTCP_SOCKET s, int level, int optname, char * optval, int * optlen);
VTCP_EXPORT_API(int				)vtcp_setsockopt	(VTCP_SOCKET s, int level, int optname, char * optval, int   optlen);
VTCP_EXPORT_API(int				)vtcp_select		(SVTcpFdSet * fdr, SVTcpFdSet * fdw, SVTcpFdSet * fde, const struct timeval * to);
VTCP_EXPORT_API(VTCP_SOCKET		)vtcp_socket		(int af, int itype, int protocol);
VTCP_EXPORT_API(VTCP_SOCKET		)vtcp_socketshare	(VTCP_SOCKET s);
VTCP_EXPORT_API(int				)vtcp_startup		();

VTCP_EXPORT_API(VTCP_QIO_HANDLE	)vtcp_qio_create	();
VTCP_EXPORT_API(int				)vtcp_qio_post		(VTCP_QIO_HANDLE qio, VTCP_SOCKET   s, EVTcpQIOEvent   qio_event, void *  qio_data, int   qio_error);
VTCP_EXPORT_API(int				)vtcp_qio_get		(VTCP_QIO_HANDLE qio, VTCP_SOCKET * s, EVTcpQIOEvent * qio_event, void ** qio_data, int * qio_error, unsigned long timeout);
VTCP_EXPORT_API(int				)vtcp_qio_set		(VTCP_QIO_HANDLE qio, VTCP_SOCKET   s, EVTcpQIOEvent   qio_event, void *  qio_data);
VTCP_EXPORT_API(int				)vtcp_qio_close		(VTCP_QIO_HANDLE qio);

//VTCP.H


