#Add
if app.__BL_RANKING__:
	import uiPlayerRanking
	
#Find
		self.wndChatLog = wndChatLog
		
#Add
		if app.__BL_RANKING__:
			self.wndPlayerRanking = uiPlayerRanking.PlayerRankingDialog()
			
#Find
		if self.wndSafebox:
			self.wndSafebox.Destroy()
			
#Add
		if app.__BL_RANKING__:
			if self.wndPlayerRanking:
				self.wndPlayerRanking.Destory()
				
#Find
		del self.wndItemSelect
		
#Add
		if app.__BL_RANKING__:
			del self.wndPlayerRanking
			
#Find
	def RefreshSafebox(self):
		self.wndSafebox.RefreshSafebox()
		
#Add
	if app.__BL_RANKING__:
		def OpenPlayerRanking(self):
			self.wndPlayerRanking.Open()