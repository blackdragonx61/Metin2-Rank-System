//Find
typedef struct packet_dead
{
	...
} TPacketGCDead;

///Add
#if defined(__BL_RANKING__)
enum RANK
{
	SUBHEADER_RANKING_SEND,
	SUBHEADER_RANKING_OPEN,
	HEADER_GC_RANKING = 160,
};
typedef struct packet_ranking_send
{
	BYTE	header;
	BYTE	subheader;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	char	szGuildName[GUILD_NAME_MAX_LEN + 1];
	int		level;
	BYTE	job;
	BYTE	empire;
} TPacketGCRankingSend;
#endif