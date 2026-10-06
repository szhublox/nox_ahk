;This script allows the player to activate various spells in OpenNox via hotkeys by leveraging the
;'manual spellcasting'/'phoneme spellcasting' system. The list of hotkeys is as follows (listed in left-to-right order):

;qwerty (Attack spells, ascending power, sorted by element):
;Missiles of Magic, Burn, Fireball, Ring of Fire, Shock, Energy Bolt

;`1235067 (Defense/Utility spells, teleports first, then magic defenses second, utility magic third):
;Blink, Swap Location, Counterspell, Inversion, Reflective Shield, Haste, Telekinesis, Wall

;Mouse 'forward' (mouse4): Teleport to Target
;Mouse 'back' (mouse5): Drain Mana
;ctrl+x: Lesser Heal (Chosen because it corresponds to default health potion hotkey)
;ctrl+1234: Mark Location 1-4
;alt+1234: Teleport to Mark 1-4

;This setup is meant to be used alongside two specific spellset setups in game:
;Spellset 1 (debuffs): Slow, Confuse, Fumble, Run, Anchor
;Spellset 2 (buffs): Force Field, Invisibility, Protection from Fire/Lightning/Poison
;These are meant to be navigated with the mousewheel. The player is expected to stay on Spellset 1 when not buffing.

;XButton2::Cast(2, 8, 4, 6)	;Teleport to Target
;XButton1::Cast(8, 7, 2, 9)	;Drain Mana

pre_timer := 40
post_timer := 40
spell_timer := 50
global lock := False
queue := []

Cast(keys) {
	global lock
	global queue
	global timer

	; if lock {
		queue.Push(keys)
		Goto DoQueue
		return
	; }
	; lock := True

	SendEvent "{Numpad5 down}"
	Sleep pre_timer
	SendEvent "{Numpad5 up}"
	Sleep pre_timer

	for index, key in keys {
		SendEvent "{Numpad" . key . " down}"
		Sleep spell_timer
		SendEvent "{Numpad" . key . " up}"
		Sleep spell_timer
	}

	SendEvent "{Numpad5 down}"
	Sleep post_timer
	SendEvent "{Numpad5 up}"
	Sleep post_timer

	lock := False

	if queue.Length > 0 {
		keys := queue.RemoveAt(1)
		Cast(keys)
	}
}

q::Cast([4, 8, 6, 8])		;Missiles of Magic
w::Cast([2, 2, 8, 8])		;Burn
e::Cast([2, 2, 8])		;Fireball
r::Cast([3, 2, 1, 8])		;Ring of Fire
t::Cast([2, 6, 4, 4])		;Shock
y::Cast([2, 6, 4, 8])		;Energy Bolt

`::Cast([6, 4, 8])		;Blink
1::Cast([2, 8, 4, 6])		;Teleport to Target
2::Cast([2, 3])			;Counterspell
3::Cast([7, 9])			;Inversion
4::Cast([8, 2, 2, 1, 3])	;Reflective Shield
5::Cast([4, 6, 6])		;Haste
6::Cast([2, 8, 2, 8])		;Telekinesis
7::Cast([7, 8, 9])		;Wall

^q::Cast([8, 8, 2, 2])		;Swap Location
^w::Cast([8, 7, 2, 9])		;Drain Mana

^x::Cast([3, 8, 1])		;Lesser Heal

^1::Cast([8, 2, 8])		;Mark Location 1
^2::Cast([8, 2, 6])		;Mark Location 2
^3::Cast([8, 2, 2])		;Mark Location 3
^4::Cast([8, 2, 4])		;Mark Location 4
!1::Cast([2, 8, 8])		;Teleport to Marker 1
!2::Cast([2, 8, 6])		;Teleport to Marker 2
!3::Cast([2, 8, 2])		;Teleport to Marker 3
!4::Cast([2, 8, 4])		;Teleport to Marker 4

DoQueue:
if queue.Length > 0 {
MsgBox(queue.Length)
}
