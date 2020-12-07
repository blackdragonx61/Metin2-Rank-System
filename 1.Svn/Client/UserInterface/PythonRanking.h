#pragma once

class CPythonRanking : public CSingleton<CPythonRanking>
{
private:
	struct SRankingData
	{
		SRankingData(const char* c_name, int c_level, BYTE c_job, BYTE c_empire, const char* c_guild) 
			: name(c_name), guild(c_guild), level(c_level), job(c_job), empire(c_empire)
		{}
		std::string name, guild;
		int level;
		BYTE job, empire;
	};
	std::vector<std::shared_ptr<SRankingData>> vRankingContainer;

public:
	enum
	{
		RANK_PAGE_MAX_NUM = 10,
		RANK_SHOW_COUNT = 50,
		RANKING_MAX_NUM = 500, // game(packet.h)
	};
	CPythonRanking();
	virtual ~CPythonRanking();

	void RegisterRankingData(const char* name, int level, BYTE job, BYTE empire, const char* guild);
	void ClearRankData();

	size_t GetRankCount() const;
	std::uint16_t GetRankMyLine() const;
	SRankingData* GetRankByLine(std::uint16_t dwArrayIndex) const;
};