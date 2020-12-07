//Find
			case HEADER_GC_EXCHANGE:
				ret = RecvExchangePacket();
				break;
				
///Add
#if defined(__BL_RANKING__)
			case HEADER_GC_RANKING:
				ret = RecvRanking();
				break;
#endif

//Find
void CPythonNetworkStream::ToggleGameDebugInfo()
{
	...
}

///Add
#if defined(__BL_RANKING__)
bool CPythonNetworkStream::RecvRanking()
{
	TPacketGCRankingSend Packet;
	if (!Recv(sizeof(Packet), &Packet)) {
		Tracen("RecvRanking Error");
		return false;
	}

	switch (Packet.subheader)
	{
	case RANK::SUBHEADER_RANKING_SEND:
		CPythonRanking::Instance().RegisterRankingData(Packet.szName, Packet.level, Packet.job, Packet.empire, Packet.szGuildName);
		break;
	case RANK::SUBHEADER_RANKING_OPEN:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_RANK_OPEN", Py_BuildValue("()"));
		break;
	}

	return true;
}
#endif