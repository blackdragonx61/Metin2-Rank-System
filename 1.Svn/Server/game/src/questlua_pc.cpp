///Add
#if defined(__BL_RANKING__)
#include "buffer_manager.h"
#endif

//Find
	int pc_get_dx( lua_State* L )
	{
		...
	}
	
///Add
#if defined(__BL_RANKING__)
	int pc_open_player_ranking(lua_State* L)
	{
		const LPCHARACTER pkChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if (!pkChar || !pkChar->GetDesc())
			return 0;

		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT player.name, player.level, player.job, player_index.empire, guild.name AS guild_name FROM player.player LEFT JOIN player.player_index ON player_index.id=player.account_id LEFT JOIN player.guild_member ON guild_member.pid=player.id LEFT JOIN player.guild ON guild.id=guild_member.guild_id INNER JOIN account.account ON account.id=player.account_id WHERE account.status != 'BLOCK' ORDER BY player.level DESC, player.name ASC LIMIT %d", ERANKINFO::RANKING_MAX_NUM));
		if (pMsg->uiSQLErrno)
			return 0;

		TEMP_BUFFER buf;

		MYSQL_ROW row;
		while ((row = mysql_fetch_row(pMsg->Get()->pSQLResult))) {
			if (row[0][0] == '[') // GameMaster
				continue;

			TPacketGCRankingInfo info;
			strlcpy(info.szName, row[0], sizeof(info.szName));
			info.iLevel = std::stoi(row[1]);
			info.bJob = std::stoi(row[2]);
			info.bEmpire = std::stoi(row[3]);
			strlcpy(info.szGuildName, row[4] ? row[4] : "-", sizeof(info.szGuildName));
			buf.write(&info, sizeof(info));
		}

		TPacketGCRankingSend packet;
		packet.bHeader = HEADER_GC_RANKING;
		packet.wSize = sizeof(packet) + buf.size();
		
		if (buf.size()) {
			pkChar->GetDesc()->BufferedPacket(&packet, sizeof(packet));
			pkChar->GetDesc()->Packet(buf.read_peek(), buf.size());
		}
		else
			pkChar->GetDesc()->Packet(&packet, sizeof(packet));

		return 0;
	}
#endif

//Find
			{ "can_warp",			pc_can_warp		},
			
///Add
#if defined(__BL_RANKING__)
			{ "open_player_ranking", pc_open_player_ranking },
#endif