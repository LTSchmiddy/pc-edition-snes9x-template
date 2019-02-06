# link-to-the-past-pc-edition-snes9x
A port of the Snes9x emulator

DISCLAIMER: 'The Legend of Zelda: A Link to the Past' and the entire 'The Legend of Zelda' franchise are the intellectual property of Nintendo Co., Ltd. I have no affiliation with them, nor do I have any legal rights or ownership over the aforementioned properties. I'm just a fan.

Then again, you probably new that.

DISCLAIMER 2: This README is designed for someone not TOO familiar with emulation and ROM-Hacking. Sorry if this is too dumbed down for you. Please read the whole thing anyway.

Download Latest Stable Build: https://github.com/LTSchmiddy/link-to-the-past-pc-edition-snes9x/releases

===================================================================================================== Date of Readme: 2/5/2019

Table of Contents:

1) Introduction

2) Features

3) How To Configure

4) QIAWBFAIIDATH (Questions I Assume Will Be Frequently Asked If I Don't Answer Them Here)

5) Links

6) Conclusion

=====================================================================================================

===== 1) Introduction =============================================================================== (TBH, you've probably already read this part whereever you downloaded this project.)

Well, with how well my "Super Metroid - PC Edition" (aka: SMPE) project turned out (or, at least, how happy I was with with it), I figured: why stop here? Figuring out the guts of the Snes9X enough to figure out where/how to insert my game features and tweaks had been the tricky part. Once I solved that, coding the actual features themselves was fairly straightforward. I could easily generalize my source-code, and use it to build custom emulators for other retro games as well. Specifically, one other game I wanted to do this for was "The Legend of Zelda: A Link to the Past": While it is a time-honored classic and a fun game in its own right, I'm of the opinion that some aspects of the game could have aged better.

I actually started working on this about halfway through my development of SMPE. While I had it mostly finished at about that time, there was having difficulty finding the memory address of a specific variable. After playing with it on and off for the last couple months, I stumbled on the solution somewhat by accident. After implementing it, I feel confident that this is ready for a public release.

*********************

"The Legend of Zelda: A Link to the Past - PC Edition" is a modified version of the Snex9X emulator (link to their site in section 6) specifically designed for playing A Link to the Past and any ROM Hacks based on it. Unlike the vanilla version of the emulator, it makes a handful of improvements and adds some new controls to the game by means of memory manipulation (and the occasional input spoof) during runtime. And since all of this is handled by the emulator's own execution code (no changes, soft or hard, are made to the ROM itself), these improvements can be applied to ANY A Link to the Past ROM hack. On top of that, Snes9X already has a number of featured to improve the visuals and sound of the game, and this copy of the emulator is optimized A Link to the Past by default.

Additionally, I recommend using this emulator with ShadowOne333's "A Link to the Past: Redux" rom hack (available here: https://www.romhacking.net/hacks/2594/). It makes a number of improvements to the original game; these include an improved UI, using the L and R buttons to switch items, changing directions while using the Pegesus Boots, and making Link's hair be its correct, canonical color instead of purple. I've included a copy in this release.

=====================================================================================================

===== 2) Features ===================================================================================

So, exactly what does "The Legend of Zelda: A Link to the Past - PC Edition" have to offer?

Each major feature listed below can be enabled or disabled in a special config file. More on that later.

a) ADDITIONAL CONTROLS:

I've added a number of additional controls to the game. This system works by hijacking joypads 2, 3, and 4 in the emulator, so they do work with hardware controllers. The programs's input configuration screen reflects these new controls.


**** Vanilla Controls ****

Movement: WASD 

Action/Interact/Pegasus Boots: Space Bar

Use Sword: J

Use Secondary Item: K

Previous Item: L (if using the redux ROM)

Next Item: U (if using the redux ROM)

Show/Hide Inventory Screen: Q

Show/Hide Map Screen: Tab

Show Save Menu: ` [Back-tick]



**** New Controls ****

Strafe: Left Shift

Quick Boomerang: M

Quick Bow: N

Quick Hookshot: H

Quick Bombs: L

Quick Lantern: ; [Semi-Colon]

Quick Hammer: E



Menu - Navigate: Arrow Keys

Menu - Select/Confirm: Enter

Menu - Back/Cancel: Backspace

Pause Game: Escape (Not in menus)


b) IMPROVED MOVEMENT:

Admittedly, because of ALTTP's simplistic movement controls, it can be VERY difficult to avoid taking damage from enemies because your shield is largely useless. It works when you're standing in the exact right spot, and if you turn away to adjust your position the shield is no longer between you and your enemy. Basically, it's very difficult to actually make use of.

To fix this, I've added a strafe button (Left Shift by default) to the emulator. While holding it, Link will continue to face the same direction regardless of what direction you move in. This way, you can more easily position yourself so that your shield in between you and that incoming enemy or projectile.

Additionally, I've made the it so there is no wind-up time for running with the Pegesus Boots. In all of the later titles in the series, Link has his incredibly handy dive-roll to help him quickly manuver away from enemy attacks in a pinch. By removing the wind-up time on the Pegesus Boots, they can be used in a similar manner.

c) HEALTH/MAGIC REGENERATION:

I know some people may not like this next feature, so let me remind you that it is EASILY disabled if you wish.

On top of the game's awkward combat, recovering health and magic is a huge pain as well. In dungeons, pots don't respawn unless you die, whereas later games would respawn them after you left the room. On top of that, ALTTP is incredibly stingy about giving out health pickups in the first place, and each heart is worth half the health they are worth in later games. In short, back-tracking and grinding to replenish your health is often a near impossible task that produces meager results. I often found myself save-scumming using the emulator save states in order to have anything remotely close to a good time.

Magic has the same problem as well. While you can unlock a wide number of magical items and abilities, the difficulty of recovering your magic power highly discourages you from using most of them outside of when they are strictly needed, reducing the variety of gameplay quite signifigantly.

After considering several options, I decided that the best thing I could do (or rather, could figure out how to do) was to implement a SLOW health and magic regeneration system. For your health, you will recover half a heart every 2 seconds, kicking 10 seconds after the last time you took damage. Similarly for magic, you will recover 1 point of magic every 2 seconds, kicking 10 seconds after the last time you use magic.

For the record, the Health and Magic Regeneration are enabled/disabled indepentently of each other. In some future version, I may allow the player to configure the regeneration rates and delays to their own liking.



=====================================================================================================

===== 3) How To Configure ===========================================================================

See that file named "Default_GameConfig.txt"? Open it.

This file controls which major features are enabled. When a ROM is loaded, the emulator reads through this file, line by line, looking for a handful of flags. If a flag is found, it checks the next line for either 'true' or 'false', which determines whether the feature is enabled or disabled. If the line contains the '#' character, it is ignored.


The current flags are:

'UseNewControls' - This enables the new controls I discussed above, including the new strafing button.

'NoChargeForDash' - Disables the wind-up time for the Pegesus Boots.

'DropsNeverVanish' - Prevents item drops in the current area from disappearing until you leave. Just handy.

'BalancedHealthRegen" - This enables the health regeneration I discussed above.

'BalancedMagicRegen' - This enables the magic regeneration I discussed above.



There mey be some flags for experimental features that I'm still working on. They will be marked properly, and you should really leave these off, as some of them WILL break the game and none of them work properly yet.

If a flag is never found, the associated feature will be disabled.

You can have unique settings for ROMs by creating a file with your ROM name + '_GameConfig.txt' in the Patches folder (example: if your ROM is named 'MyHack.smc', then you need to make a file named 'MyHack_GameConfig.txt' in the patches folder. If you're still confused, the stdout.txt file will show you the name of the GameConfig file it's looking for when you open a ROM). Setting found in this file will override the defaults.

Note, these files are COMPLETELY CASE SENSITIVE!!!

Everything else works the same way it does in normal Snes9X.

=====================================================================================================

===== 4) QIAWBFAIIDATH (Questions I Assume Will Be Frequently Asked If I Don't Answer Them Here) ====

********************************************************************************
Q: What ROMs is this compatable with?
A: As far as I know, any version of 'A Link to the Past' (or any ROM Hack based on it) should work fine. I've tested the emulator with bothe the vanilla game and the Redux version I mentioned in the intro, and haven't had any issues.

... Oh, also, in case this isn't obvious: don't try to use a non-ALTTP-based ROM with this emulator. I have no idea what will happen, but I doubt it will be good.

********************************************************************************
Q: Where can I get your source code? Where are your changes?
A: Right Here.

The code I've added it mostly contained in the files SMMods.cpp and SMMods.h, and in the directory named ModScripts, along with a slight reworking of the beginning of the program's Main() method, found in wsnes9x.cpp, and some parts of UI-related code also in that file. Everything else is either making certain methods available outside of their origin file, or calls to the methods in SMMods.cpp to make these features work.

If people are interested, I could put in a programmer's API/Documentation at some point.

********************************************************************************
Q: Does this work on Mac/Linux?
A: It could at some point. But not as of yet. Once I'm confident that the windows version is stable and is fully functional, then I'll consider other platforms.

... I'll be adding to this part as people begin to ask questions....

=====================================================================================================

===== 5) Links ======================================================================================

http://www.SNES9x.com/ - Snes9X's official website. If it's not a question related to my changes, look here.

https://github.com/LTSchmiddy/link-to-the-past-pc-edition-snes9x - The source code for this project.

https://github.com/snes9xgit/snes9x - The source code for the official version of Snes9X, on which my version is based.

https://www.romhacking.net/hacks/2594/ - ShadowOne333's "A Link to the Past: Redux" rom hack. IT makes a number of improvements to the game, and so I definitely recommend using this ROM hack over the vanilla version.

https://visualstudio.microsoft.com/downloads/ - If you wanna try to work on my code, you're gonna need Microsoft Visual Studio 2017 - Community Edition (which is what I used).


=====================================================================================================

===== 6) Conclusion =================================================================================

Well, that's all I gotta say about this project. Give it a play, lemme know what ya think!

If you got questions or comments or feedback, hit me up on Twitter (@Lt_ASchmiddy) or Discord (LT_Schmiddy), and I'll be glad to talk / help you out!

LT_Schmiddy, out.

=====================================================================================================