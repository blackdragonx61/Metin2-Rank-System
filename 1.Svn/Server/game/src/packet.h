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
	RANKING_MAX_NUM = 500,
	HEADER_GC_RANKING = 160,
};
typedef struct packet_ranking_send
{
	packet_ranking_send()
	{
		std::strncpy(szName, "", sizeof(szName));
		std::strncpy(szGuildName, "", sizeof(szGuildName));
	}
	packet_ranking_send(const char* name, int c_level, int c_job, int c_empire, const char* guild)
		: subheader(RANK::SUBHEADER_RANKING_SEND), level(c_level), job(c_job), empire(c_empire)
	{
		std::strncpy(szName, name, sizeof(szName));
		std::strncpy(szGuildName, guild, sizeof(szGuildName));
	}
	BYTE	header = HEADER_GC_RANKING;
	BYTE	subheader = SUBHEADER_RANKING_OPEN;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	char	szGuildName[GUILD_NAME_MAX_LEN + 1];
	int		level = 0;
	BYTE	job = 0;
	BYTE	empire = 0;
} TPacketGCRankingSend;
#endif