//Find
typedef struct packet_dead
{
	...
} TPacketGCDead;

///Add
#if defined(__BL_RANKING__)
enum ERANKINFO
{
	HEADER_GC_RANKING = 160,
};

typedef struct packet_ranking_send
{
	BYTE bHeader;
	WORD wSize;
} TPacketGCRankingSend;

typedef struct packet_ranking_info
{
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	int		iLevel;
	BYTE	bJob;
	BYTE	bEmpire;
	char	szGuildName[GUILD_NAME_MAX_LEN + 1];
} TPacketGCRankingInfo;
#endif