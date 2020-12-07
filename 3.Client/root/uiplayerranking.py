import ui
import app
import player
import ranking
import math

class PlayerRankingDialog(ui.ScriptWindow):
	SLOT_RANKING = 0
	SLOT_NAME = 1
	SLOT_LEVEL = 2
	SLOT_GUILD_NAME = 3
	MAX_LINE_COUNT = ranking.RANK_PAGE_MAX_NUM
	
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.isLoaded = 0
		self.Page = 1
		self.IsShow = False
		self.board = None
		self.ResultButtonList = []
		self.ResultSlotList = {}
		self.MyResultSlotList = []
		self.ResultButtonRankList = []
		self.ScrollBar = None
		self.NowStartLineNumber = 0
		self.LoadWindow()
		self.MakeUiBoard()

	def __del__(self):
		ui.ScriptWindow.__del__(self)
		self.isLoaded = 0
		self.IsShow = False
		self.board = None
		self.ScrollBar = None
		self.ResultButtonList = []
		self.ResultSlotList = {}
		self.MyResultSlotList = []
		self.ResultButtonRankList = []

	def Destory(self):
		self.Close()
		self.isLoaded = 0
		self.IsShow = False
		self.board = None
		self.ScrollBar = None
		self.ResultButtonList = []
		self.ResultSlotList = {}
		self.MyResultSlotList = []
		self.ResultButtonRankList = []
		
	def Open(self):
		if not self.IsShow:
			self.IsShow = True
			self.SetCenterPosition()
			self.SetTop()
			self.Page = 1
			self.ScrollBar.SetPos(0)
			self.NowStartLineNumber = 0
			self.RefreshRankingBoard()
			ui.ScriptWindow.Show(self)

	def Close(self):
		self.IsShow = False
		ranking.RankClear()
		self.Hide()
	
	def LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/PlayerRanking.py")
		except:
			import exception
			exception.Abort("PlayerRankingDialog.__LoadWindow.LoadScript")
		getObject = self.GetChild
		self.board = getObject("TitleBar")
		self.prevbtn = getObject("prev_button")
		self.prevfirstbtn = getObject("prev_first_button")
		self.nextbtn = getObject("next_button")
		self.nextlastbtn = getObject("next_last_button")
		self.CurrentPageText = getObject("CurrentPage")
		self.board.SetCloseEvent(ui.__mem_func__(self.Close))
		self.prevfirstbtn.SAFE_SetEvent(self.ChangePageFL, False)
		self.nextlastbtn.SAFE_SetEvent(self.ChangePageFL, True)
		self.prevbtn.SAFE_SetEvent(self.ChangePage, -1)
		self.nextbtn.SAFE_SetEvent(self.ChangePage, 1)
		self.ScrollBar = getObject("ScrollBar")
		self.ScrollBar.SetScrollEvent(ui.__mem_func__(self.OnScrollControl))
			
	def ChangePage(self, count):
		self.Page += count
		self.ScrollBar.SetPos(0)
		self.NowStartLineNumber = 0
		self.RefreshRankingBoard()
		
	def PageControl(self):
		for prev in (self.prevfirstbtn, self.prevbtn): 
			if self.Page <= 1:
				prev.Hide()
			else:
				prev.Show()			
		for next in (self.nextlastbtn, self.nextbtn): 
			if self.Page >= self.GetLastPage():
				next.Hide()
			else:
				next.Show()	
		self.CurrentPageText.SetText(str(self.Page))
	
	def ChangePageFL(self, Last):
		self.Page = [1, self.GetLastPage()][Last == True]
		self.ScrollBar.SetPos(0)
		self.NowStartLineNumber = 0
		self.RefreshRankingBoard()
	
	def MakeUiBoard(self):
		yPos = 0
		for i in range(0, self.MAX_LINE_COUNT+1):			
			yPos = 60 + i * 24
			if i == 10:
				yPos += 10
				
			RankingSlotImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/parameter_slot_00.sub", 23, yPos)
			RankingSlotImage.SetAlpha(0)
			RankingSlot = ui.MakeTextLine(RankingSlotImage)
			self.Children.append(RankingSlotImage)
			self.Children.append(RankingSlot)

			NameImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/parameter_slot_04.sub", 77, yPos)
			NameImage.SetAlpha(0)
			NameSlot = ui.MakeTextLine(NameImage)
			self.Children.append(NameImage)
			self.Children.append(NameSlot)

			LevelImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/parameter_slot_00.sub", 205, yPos)
			LevelImage.SetAlpha(0)
			LevelSlot = ui.MakeTextLine(LevelImage)
			self.Children.append(LevelImage)
			self.Children.append(LevelSlot)
		
			GuildImage = ui.MakeImageBox(self, "d:/ymir work/ui/public/parameter_slot_00.sub", 270, yPos)
			GuildImage.SetAlpha(0)
			GuildSlot = ui.MakeTextLine(GuildImage)
			self.Children.append(GuildImage)
			self.Children.append(GuildSlot)
			
			if i < self.MAX_LINE_COUNT:
				temprankingslotlist = []
				temprankingslotlist.append(RankingSlot)		
				temprankingslotlist.append(NameSlot)
				temprankingslotlist.append(LevelSlot)
				temprankingslotlist.append(GuildSlot)
				self.ResultSlotList[i] = temprankingslotlist
			else:
				self.MyResultSlotList.append(RankingSlot)
				self.MyResultSlotList.append(NameSlot)
				self.MyResultSlotList.append(LevelSlot)
				self.MyResultSlotList.append(GuildSlot)

			itemSlotButtonImage = ui.MakeButton(self, 21, yPos, "", "d:/ymir work/ui/game/guild/dragonlairranking/", "ranking_list_button01.sub", "ranking_list_button02.sub", "ranking_list_button02.sub")
			itemSlotButtonImage.Show()
			itemSlotButtonImage.Disable()
			self.Children.append(itemSlotButtonImage)				
			if i < self.MAX_LINE_COUNT:
				self.ResultButtonList.append(itemSlotButtonImage)
	
	def RefreshRankingBoard(self):
		self.AllClear()
		self.PageControl()
		for line, ResultSlotList in self.ResultSlotList.items():
			linewpage = line + self.NowStartLineNumber + (self.Page - 1) * ranking.RANK_SHOW_COUNT
			if linewpage >= ranking.GetRankCount():
				break
			(name, level, job, empire, guild) = ranking.GetRankByLine(linewpage)
			ResultSlotList[self.SLOT_RANKING].SetText(str(linewpage+1))
			ResultSlotList[self.SLOT_NAME].SetText(name)
			ResultSlotList[self.SLOT_LEVEL].SetText(str(level))
			ResultSlotList[self.SLOT_GUILD_NAME].SetText(guild)
			self.ResultButtonList[line].Show()
			if player.GetName() == name:
				self.ResultButtonList[line].Down()

		self.MyResultSlotList[self.SLOT_NAME].SetText(player.GetName())
		self.MyResultSlotList[self.SLOT_LEVEL].SetText(str(player.GetStatus(player.LEVEL)))
		if player.GetGuildID():
			self.MyResultSlotList[self.SLOT_GUILD_NAME].SetText(player.GetGuildName())
		MyRank = ranking.GetRankMyLine()
		if MyRank:
			self.MyResultSlotList[self.SLOT_RANKING].SetText(str(MyRank))		
		self.ScrollBar.SetMiddleBarSize(float(self.MAX_LINE_COUNT) / float(self.CheckNowItemCount()))
		
	def AllClear(self):
		for line, ResultSlotList in self.ResultSlotList.items():
			ResultSlotList[self.SLOT_RANKING].SetText("")
			ResultSlotList[self.SLOT_NAME].SetText("")
			ResultSlotList[self.SLOT_LEVEL].SetText("")
			ResultSlotList[self.SLOT_GUILD_NAME].SetText("")
			self.ResultButtonList[line].SetUp()
			self.ResultButtonList[line].Hide()
		self.MyResultSlotList[self.SLOT_RANKING].SetText("-")
		self.MyResultSlotList[self.SLOT_NAME].SetText("-")
		self.MyResultSlotList[self.SLOT_LEVEL].SetText("-")
		self.MyResultSlotList[self.SLOT_GUILD_NAME].SetText("-")
		
	def GetLastPage(self):
		return int(math.ceil(float(ranking.GetRankCount()) / ranking.RANK_SHOW_COUNT))
		
	def GetRemaining(self):
		remaining = [ranking.RANK_SHOW_COUNT, ranking.GetRankCount() % ranking.RANK_SHOW_COUNT][self.Page == self.GetLastPage()]
		return remaining
	
	def CheckNowItemCount(self):
		remaining = self.GetRemaining()
		if remaining <= self.MAX_LINE_COUNT:
			return self.MAX_LINE_COUNT
		return remaining
	
	def OnScrollControl(self):
		remaining = self.GetRemaining()
		if remaining <= self.MAX_LINE_COUNT:
			nowitemcount = 0
		else:
			nowitemcount = (remaining - self.MAX_LINE_COUNT)
			
		pos = self.ScrollBar.GetPos() * nowitemcount
		if not int(pos) == self.NowStartLineNumber:
			self.NowStartLineNumber = int(pos)
			self.RefreshRankingBoard()

	def OnPressEscapeKey(self):
		self.Close()
		return True
 