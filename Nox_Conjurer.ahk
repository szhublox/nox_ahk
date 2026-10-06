#IfWinActive, OpenNox
{
;This script allows the player to activate various spells in OpenNox via hotkeys by leveraging the
;'manual spellcasting'/'phoneme spellcasting' system. In order for this script to work, the numpad
;must be mapped to the phonemes in the following order (from top to bottom in the input options menu):
;824697315
;The list of hotkeys is as follows (listed in left-to-right order):

;qwerty (Attack spells, ascending power, sorted by element):
;Pixie Swarm, Burn, Meteor, Fist of Vengeance, Toxic Cloud, Force of Nature

;`1234567 (Defense/Utility spells, first Blink, then Charm Creature, then magic defenses, then buffs, then heals):
;Blink, Charm Creature, Counterspell, Inversion, Vampirism, Infravision, Greater Heal, Cure Poison

;Mouse 'forward' (mouse4): Stun
;Mouse 'back' (mouse5): Poison
;ctrl+x: Lesser Heal (Chosen because it corresponds to default health potion hotkey)

;This setup is meant to be used alongside one specific spellset setup in game:
;Spellset 1 (debuffs and protection): Slow, Tag, Protection from Fire/Shock/Poison
;The remaining spell sets are meant to be devoted to creature summons, navigated with mousewheel. The only two spells
;omitted from this set are Moonglow and Light, which are generally not useful in PVP, but can be placed on the spell lists if desired.

;qwerty set (Pixie Swarm, Burn, Meteor, Fist of Vengeance, Toxic Cloud, Force of Nature)
;Pixie Swarm
q::
SendInput, {Numpad4 down}
Sleep, 40
SendInput, {Numpad4 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad6 down}
Sleep, 40
SendInput, {Numpad6 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Burn
w::
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad8 down}
Sleep, 40
SendInput, {Numpad8 up}
Sleep, 40
SendInput, {Numpad8 down}
Sleep, 40
SendInput, {Numpad8 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Meteor
e::
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Fist of Vengeance
r::
SendInput, {Numpad7 down}
Sleep, 40
SendInput, {Numpad7 up}
Sleep, 40
SendInput, {Numpad9 down}
Sleep, 40
SendInput, {Numpad9 up}
Sleep, 40
SendInput, {Numpad8 down}
Sleep, 40
SendInput, {Numpad8 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Toxic Cloud
t::
SendInput, {Numpad9 down}
Sleep, 40
SendInput, {Numpad9 up}
Sleep, 40
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad7 down}
Sleep, 40
SendInput, {Numpad7 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Force of Nature
y::
SendInput, {Numpad3 down}
Sleep, 40
SendInput, {Numpad3 up}
Sleep, 40
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return


;`1234567 set (Blink, Charm Creature, Counterspell, Inversion, Vampirism, Infravision, Greater Heal, Cure Poison)
;Blink
`::
SendInput, {Numpad6 down}
Sleep, 40
SendInput, {Numpad6 up}
Sleep, 40
SendInput, {Numpad4 down}
Sleep, 40
SendInput, {Numpad4 up}
Sleep, 40
SendInput, {Numpad8 down}
Sleep, 40
SendInput, {Numpad8 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Charm Creature
1::
SendInput, {Numpad7 down}
Sleep, 40
SendInput, {Numpad7 up}
Sleep, 40
SendInput, {Numpad9 down}
Sleep, 40
SendInput, {Numpad9 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Counterspell
2::
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad3 down}
Sleep, 40
SendInput, {Numpad3 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Inversion
3::
SendInput, {Numpad7 down}
Sleep, 40
SendInput, {Numpad7 up}
Sleep, 40
SendInput, {Numpad9 down}
Sleep, 40
SendInput, {Numpad9 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Vampirism
4::
SendInput, {Numpad8 down}
Sleep, 40
SendInput, {Numpad8 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad4 down}
Sleep, 40
SendInput, {Numpad4 up}
Sleep, 40
SendInput, {Numpad6 down}
Sleep, 40
SendInput, {Numpad6 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Infravision
5::
SendInput, {Numpad6 down}
Sleep, 40
SendInput, {Numpad6 up}
Sleep, 40
SendInput, {Numpad4 down}
Sleep, 40
SendInput, {Numpad4 up}
Sleep, 40
SendInput, {Numpad6 down}
Sleep, 40
SendInput, {Numpad6 up}
Sleep, 40
SendInput, {Numpad4 down}
Sleep, 40
SendInput, {Numpad4 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Greater Heal
6::
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad8 down}
Sleep, 40
SendInput, {Numpad8 up}
Sleep, 40
SendInput, {Numpad3 down}
Sleep, 40
SendInput, {Numpad3 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Cure Poison
7::
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad9 down}
Sleep, 40
SendInput, {Numpad9 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;remaining set: Stun, Poison, Lesser Heal
;Stun, mouse 'forward'
XButton2::
SendInput, {Numpad7 down}
Sleep, 40
SendInput, {Numpad7 up}
Sleep, 40
SendInput, {Numpad2 down}
Sleep, 40
SendInput, {Numpad2 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Poison, mouse 'back'
XButton1::
SendInput, {Numpad9 down}
Sleep, 40
SendInput, {Numpad9 up}
Sleep, 40
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

;Lesser Heal, ctrl+x
^x::
SendInput, {Numpad3 down}
Sleep, 40
SendInput, {Numpad3 up}
Sleep, 40
SendInput, {Numpad8 down}
Sleep, 40
SendInput, {Numpad8 up}
Sleep, 40
SendInput, {Numpad1 down}
Sleep, 40
SendInput, {Numpad1 up}
Sleep, 40
SendInput, {Numpad5 down}
Sleep, 40
SendInput, {Numpad5 up}
return

return
}