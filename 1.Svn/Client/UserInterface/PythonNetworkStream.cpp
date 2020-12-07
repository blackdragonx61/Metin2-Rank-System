//Find
			Set(HEADER_GC_DEAD,					CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDead), STATIC_SIZE_PACKET));
			
///Add
#if defined(__BL_RANKING__)
			Set(HEADER_GC_RANKING, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCRankingSend), STATIC_SIZE_PACKET));
#endif