#include "ModScripts\Utilities.h"
#include "ModScripts\NewControls.h"
#include "SMMods.h"

#include "SMMods.h"
#include "wsnes9x.h"
#include "win32_sound.h"
#include "win32_display.h"
#include "CCGShader.h"
#include "../shaders/glsl.h"
#include "CShaderParamDlg.h"
#include "../snes9x.h"
#include "../memmap.h"
#include "../cpuexec.h"
#include "../display.h"
#include "../cheats.h"
#include "../controls.h"
#include "../conffile.h"
#include "../statemanager.h"
#include "InputCustom.h"

#include <iostream>
//#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>

using namespace std;

#include <sstream>
#include <string>

#include <iostream>
#include <fstream>

#include <commctrl.h>
#include <io.h>
#include <time.h>
#include <direct.h>

//#include <direct.h>
#include <stdlib.h>
#include <stdio.h>


//New Controls:

const uint32 Menu_Up = 0x81100808;
const uint32 Menu_Down = 0x81100809;
const uint32 Menu_Left = 0x8110080a;
const uint32 Menu_Right = 0x8110080b;
const uint32 Menu_A = 0x81100801;
const uint32 Menu_B = 0x81100802;

const uint32 Control_Up = 0x81100108;
const uint32 Control_Down = 0x81100109;
const uint32 Control_Left = 0x8110010a;
const uint32 Control_Right = 0x8110010b;
const uint32 Control_A = 0x81100101;
const uint32 Control_B = 0x81100102;


// Quick Buttons:
const uint32 StrafeButton = 0x81100201;
const uint32 QuickBow = 0x81100200;
const uint32 QuickBoomerang = 0x81100203;
const uint32 QuickHookshot = 0x81100202;
const uint32 QuickBomb = 0x81100204;
const uint32 QuickHammer = 0x81100205;
const uint32 QuickLamp = 0x81100207;


// Addresses:
const uint32 StrafeAddress = 0x7e0050;
const uint32 FacingAddress1 = 0x7e002F;
const uint32 FacingAddress2 = 0x7e0323;

const uint32 ItemAddress = 0x7E0303;

const uint8 BowIndex = 0x03;
const uint8 BoomerangIndex = 0x02;
const uint8 HookshotIndex = 0x0E;
const uint8 BombIndex = 0x01;
const uint8 LampIndex = 0x09;
const uint8 HammerIndex = 0x04;

uint8 oldFacing = 0x00;



// Active Variables:====================================================

bool MenuPressed_Up = false;
bool MenuPressed_Down = false;
bool MenuPressed_Left = false;
bool MenuPressed_Right = false;
bool MenuPressed_A = false;
bool MenuPressed_B = false;

bool DoStrafe = false;
bool ForceItemButton = false;


unsigned lastPress = 0;
unsigned OldItem = 0xff;



//Methods:

bool SetMenuControls(bool pressedIn) {

	if (AlexGetByteFree(0x7E0010) >= 0x0C || AlexGetByteFree(0x7E0010) <= 0x05) {
		//if (AlexGetByteFree(0x7E0010) == 0x0E) {
		return pressedIn;
	}

	return false;

}

bool NewControlsInputUpdate(uint32 id, bool pressed) {

	
	if (id == Menu_Up) {
		//printf("\nPressing Up\n");
		MenuPressed_Up = SetMenuControls(pressed);
	}

	else if (id == Menu_Down) {
		MenuPressed_Down = SetMenuControls(pressed);
	}

	else if (id == Menu_Left) {
		MenuPressed_Left = SetMenuControls(pressed);
	}

	else if (id == Menu_Right) {
		MenuPressed_Right = SetMenuControls(pressed);
	}

	else if (id == Menu_A) {
		MenuPressed_A = SetMenuControls(pressed);
	}

	else if (id == Menu_B) {
		MenuPressed_B = SetMenuControls(pressed);
	}



	if (id == Control_Up && MenuPressed_Up) {
		//printf("Spoofing Up");
		pressed = true;
	}

	if (id == Control_Down && MenuPressed_Down) {
		pressed = true;
	}

	if (id == Control_Left && MenuPressed_Left) {
		pressed = true;
	}

	if (id == Control_Right && MenuPressed_Right) {
		pressed = true;
	}

	if (id == Control_A && MenuPressed_A) {
		pressed = true;
	}

	if (id == Control_B && MenuPressed_B) {
		pressed = true;
	}



	if (id == 0x81100103 && ForceItemButton) {
		pressed = true;
	}

	return pressed;


}
void QuickItemUpdate(unsigned id, bool pressed, unsigned ItemID, unsigned HasItemAddress, unsigned ItemIndex) {
	if (id == ItemID) {
		if (HasItem(HasItemAddress) && pressed && lastPress == 0) {
			lastPress = ItemID;
			OldItem = AlexGetByteFree(ItemAddress);
			AlexSetByteFree(ItemIndex, ItemAddress);
			//printf("FireBow\n");
			ForceItemButton = true;
		}
		else if (!pressed && lastPress == ItemID) {
			lastPress = 0;
			AlexSetByteFree(OldItem, ItemAddress);
			ForceItemButton = false;
		}
	}
}


void NewControlsGameplayInputUpdate(uint32 id, bool pressed) {
	if (id == StrafeButton && pressed) {
		if (!DoStrafe) {
			oldFacing = AlexGetByteFree(FacingAddress1);
		}
		DoStrafe = true;
		AlexSetByteFree(oldFacing, FacingAddress1);
		AlexSetByteFree(oldFacing, FacingAddress2);
		AlexSetByteFree(0x01, StrafeAddress);



	}
	else if (id == StrafeButton && !pressed) {
		if (DoStrafe) {
			DoStrafe = false;
			AlexSetByteFree(0x00, StrafeAddress);
		}
		oldFacing = AlexGetByteFree(FacingAddress1);

	}

	QuickItemUpdate(id, pressed, QuickBow, HasBowAddress, BowIndex);
	QuickItemUpdate(id, pressed, QuickBoomerang, HasBoomerangAddress, BoomerangIndex);
	QuickItemUpdate(id, pressed, QuickHookshot, HasHookshotAddress, HookshotIndex);
	QuickItemUpdate(id, pressed, QuickBomb, HasBombsAddress, BombIndex);
	QuickItemUpdate(id, pressed, QuickHammer, HasHammerAddress, HammerIndex);
	QuickItemUpdate(id, pressed, QuickLamp, HasLampAddress, LampIndex);
	//QuickItemUpdate(id, pressed, QuickBow, HasBowAddress, BowIndex);

}

void Input_OnUpdate() {

	

}
