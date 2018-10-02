#include "ModScripts\Utilities.h"

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

// Memory Locations:

//const uint32 SamusHealthSBA = 0x7e09C2;

const uint32 PlayerHealthAddress = 0x7EF36D;
const uint32 PlayerMaxHealthAddress = 0x7EF36C;

const uint32 PlayerMagicAddress = 0x7EF36E;



const uint32 HasBowAddress = 0x7EF340;
const uint32 HasBoomerangAddress = 0x7EF341;
const uint32 HasHookshotAddress = 0x7EF342;
const uint32 HasBombsAddress = 0x7EF343;
const uint32 HasHammerAddress = 0x7EF34B;
const uint32 HasLampAddress = 0x7EF34A;


// Player Health
int GetPlayerHealth() {
	return AlexGetByteFree(PlayerHealthAddress);
}

int GetMaxPlayerHealth() {
	return AlexGetByteFree(PlayerMaxHealthAddress);
}

void SetPlayerHealth(unsigned val) {

	if (val > GetMaxPlayerHealth()) {
		val = GetMaxPlayerHealth();
	}
	AlexSetByteFree(val, PlayerHealthAddress);;
}


int GetPlayerMagic() {
	return AlexGetByteFree(PlayerMagicAddress);
}

int GetMaxPlayerMagic() {
	return 0x80;
}

void SetPlayerMagic(unsigned val) {

	if (val > GetMaxPlayerMagic()) {
		val = GetMaxPlayerMagic();
	}
	AlexSetByteFree(val, PlayerMagicAddress);;
}

bool HasItem(uint32 ItemAddress) {
	if (AlexGetByteFree(ItemAddress) != 0) {
		return true;
	}
	return false;
}