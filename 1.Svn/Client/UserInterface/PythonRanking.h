#pragma once

class CPythonRanking : public CSingleton<CPythonRanking>
{
public:
	CPythonRanking();
	virtual ~CPythonRanking();

	enum
	{
		RANK_PAGE_MAX_NUM = 10,
		RANK_SHOW_COUNT = 50,
		RANKING_MAX_NUM = 500, // game(packet.h)
	};

	struct SRankingData
	{
		SRankingData(const char* c_name, int c_level, BYTE c_job, BYTE c_empire, const char* c_guild)
			: sName(c_name), iLevel(c_level), bJob(c_job), bEmpire(c_empire), sGuild(c_guild) {}
		std::string sName;
		int iLevel;
		BYTE bJob;
		BYTE bEmpire;
		std::string	sGuild;
	};

	void RegisterRankingData(const char* name, int level, BYTE job, BYTE empire, const char* guild);
	void ClearRankData();

	size_t GetRankCount() const;
	std::uint16_t GetRankMyLine() const;
	SRankingData* GetRankByLine(std::uint16_t RankIndex) const;

private:
	std::vector<std::shared_ptr<SRankingData>> vRankingContainer;
};