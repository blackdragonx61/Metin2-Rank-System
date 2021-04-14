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

	CPythonRanking::Instance().ClearRankData();
	
	for (auto iPacketSize = Packet.wSize - sizeof(Packet); iPacketSize > 0; iPacketSize -= sizeof(TPacketGCRankingInfo)) {
		TPacketGCRankingInfo SRankInfo;
		if (Recv(sizeof(SRankInfo), &SRankInfo))
			CPythonRanking::Instance().RegisterRankingData(SRankInfo.szName, SRankInfo.iLevel, SRankInfo.bJob, SRankInfo.bEmpire, SRankInfo.szGuildName);
	}

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_RANK_OPEN", Py_BuildValue("()"));

	return true;
}
#endif