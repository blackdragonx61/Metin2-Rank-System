//Find
	int pc_get_dx( lua_State* L )
	{
		...
	}
	
///Add
#if defined(__BL_RANKING__)
	int pc_open_player_ranking(lua_State* L)
	{
		LPCHARACTER pkChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if (!pkChar || !pkChar->GetDesc())
			return 0;

		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("SELECT player.name, player.level, player.job, player_index.empire, guild.name AS guild_name FROM player.player LEFT JOIN player.player_index ON player_index.id=player.account_id LEFT JOIN player.guild_member ON guild_member.pid=player.id LEFT JOIN player.guild ON guild.id=guild_member.guild_id INNER JOIN account.account ON account.id=player.account_id WHERE account.status != 'BLOCK' ORDER BY player.level DESC, player.name ASC LIMIT %d", RANK::RANKING_MAX_NUM));
		if (pMsg->uiSQLErrno)
			return 0;

		MYSQL_ROW row;
		while ((row = mysql_fetch_row(pMsg->Get()->pSQLResult))) {
			if (!strncmp(row[0], "[", 1)) // GM
				continue;
			const char* GuildName = row[4] ? row[4] : "-";
			const TPacketGCRankingSend t = TPacketGCRankingSend(row[0], std::stoi(row[1]), std::stoi(row[2]), std::stoi(row[3]), GuildName);
			pkChar->GetDesc()->Packet(&t, sizeof(t));
		}

		const TPacketGCRankingSend t = TPacketGCRankingSend();
		pkChar->GetDesc()->Packet(&t, sizeof(t));

		return 0;
	}
#endif

//Find
			{ "can_warp",			pc_can_warp		},
			
///Add
#if defined(__BL_RANKING__)
			{ "open_player_ranking", pc_open_player_ranking },
#endif