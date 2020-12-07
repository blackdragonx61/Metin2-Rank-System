quest player_ranking begin
	state start begin	
		when 9006.chat."Rank List" begin
			say_title(mob_name(9006))
			say("")
			say("Do you want to open Player Rank list?")
			say("")
			if select("Yes", "No") == 1 then
				setskin(NOWINDOW)
				pc.open_player_ranking()
			end
		end
	end
end