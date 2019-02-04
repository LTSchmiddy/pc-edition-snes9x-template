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
#include "ModScripts\Utilities.h"
#include "ModScripts\NewControls.h"
#include "ModScripts\NewGamePlus.h"

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




// Constant Variables: ===============================================


string TrueString = "true";
string FalseString = "false";

// Active Variables:====================================================



//Better Save Stations:
int SMLastSaveTime = 0;

//File Config:

bool UseNewControls = false;
bool NoChargeForDash = false;
bool AutoPush = false;
bool DropsNeverVanish = false;

bool BalancedHealthRegen = false;
bool BalancedMagicRegen = false;



const char * DefaultConfigPathBase = "Default_GameConfig.txt";


const string UseNewControlsStr = "UseNewControls";
const string NoChargeForDashStr = "NoChargeForDash";
const string AutoPushStr = "AutoPush";
const string DropsNeverVanishStr = "DropsNeverVanish";
const string BalancedHealthRegenStr = "BalancedHealthRegen";
const string BalancedMagicRegenStr = "BalancedMagicRegen";
const string BetterHeartsStr = "BetterHearts";





//Function Declairations: ================================================================================================
void ModGameplayControl(uint32, bool);
void LoadSMGameConfig();



// Function Methods: ================================================================================================
//Tools:

//void PrintByte(uint32 addr) {
//	printf("Address 0x%08x = 0x%08x\n", addr, AlexGet2BytesFree(addr));
//}



//Utilities: **********************************************************************


//External Calls:
void HideMenu() {
	SetMenu(GUI.hWnd, NULL);
}

// Main Loop Function:

void SMOnLoadRom() {
	LoadSMGameConfig();
}

void ReadGameConfigFromFile(const char * path) {
	std::ifstream infile;

	infile.open(path, ios::in);

	if (infile.is_open()) {
		printf("Opened GameConfig File '");
		printf(path);
		printf("'\n");
	}
	else {

		printf("GameConfig File '");
		printf(path);
		printf("' not found. Continuing without...\n");

		return;
	}

	printf("Reading Config\n");
	std::string line;

	//while (infile >> line)
	while (std::getline(infile, line))
	{


		if (line.find("#") != std::string::npos) {
			continue;
		}

		// Use New Controls:
		if (line.find(UseNewControlsStr) != std::string::npos) {
			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				UseNewControls = true;
				printf("Enabling New Controls\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				UseNewControls = false;
				printf("Disabling New Controls\n");
			}
		}

		// Use InstantDash:
		if (line.find(NoChargeForDashStr) != std::string::npos) {
			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				NoChargeForDash = true;
				printf("Enabling Instant Dash\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				NoChargeForDash = false;
				printf("Disabling Instant Dash\n");
			}
		}

		// Use AutoPush:
		if (line.find(AutoPushStr) != std::string::npos) {
			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				AutoPush = true;
				printf("Enabling Auto Push\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				AutoPush = false;
				printf("Disabling Auto Push\n");
			}
		}

		// Use DropsNeverVanish:
		if (line.find(DropsNeverVanishStr) != std::string::npos) {
			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				DropsNeverVanish = true;
				printf("Enabling Drops Never Vanish\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				DropsNeverVanish = false;
				printf("Disabling Drops Never Vanish\n");
			}
		}		
		
		// Use BalancedHealthRegen
		if (line.find(BalancedHealthRegenStr) != std::string::npos) {
			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				BalancedHealthRegen = true;
				printf("Enabling Balanced Health Regen\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				BalancedHealthRegen = false;
				printf("Disabling Balanced Health Regen\n");
			}
		}

		if (line.find(BalancedMagicRegenStr) != std::string::npos) {
			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				BalancedMagicRegen = true;
				printf("Enabling Balanced Magic Regen\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				BalancedMagicRegen = false;
				printf("Disabling Balanced Magic Regen\n");
			}
		}
	
	}


}

void LoadSMGameConfig() {

	const char * DefaultConfigPath = S9xGetFileInDirectory(DefaultConfigPathBase, HOME_DIR);
	printf("\nDefault GameConfig Path: ");
	//strcat(DefaultConfigPath, DefaultConfigPathBase);
	printf(DefaultConfigPath);
	printf("\n");

	ReadGameConfigFromFile(DefaultConfigPath);

	const char * ROMConfigPath = S9xGetFilename("_GameConfig.txt", PATCH_DIR);
	printf("ROM GameConfig Path: ");
	printf(ROMConfigPath);
	printf("\n");
	ReadGameConfigFromFile(ROMConfigPath);
}

//And this is where the extra controls are applied:
bool ModInputUpdate(uint32 id, bool pressed) {

	if (UseNewControls) {
		pressed = NewControlsInputUpdate(id, pressed);
	}

	return pressed;
}


void ModGameplayControl(uint32 id, bool pressed) {
	if (UseNewControls) {
		NewControlsGameplayInputUpdate(id, pressed);
	}
}

// HealthRegen Info:
unsigned LastHealth = 0;
const unsigned HitDelay = 600;
unsigned HitDelayCounter = 0;
const unsigned FillDelay= 120;
unsigned FillDelayCounter = 0;
unsigned HealPerTick = 0x04;


// MagicRegen Info:
unsigned LastMagic = 0;
const unsigned UseDelay = 600;
unsigned UseDelayCounter = 600;
const unsigned MFillDelay = 10;
unsigned MFillDelayCounter = 0;
unsigned MRegenPerTick = 1;

bool ShouldRunRegen() {
	if (AlexGetByteFree(0x7E0010) == 0x18) {
		return true;

	}

	if (AlexGetByteFree(0x7E0010) >= 0x0C || AlexGetByteFree(0x7E0010) <= 0x05) {
	//if (AlexGetByteFree(0x7E0010) == 0x0E) {
		return false;
	}

	return true;

}

void SMMainLoop() {
	if (NoChargeForDash) {
		AlexSetByteFree(0x27, 0x0790B9);
	}

	if (AutoPush) {
		AlexSetByteFree(0x10, 0x7E0048);
	}

	if (DropsNeverVanish) {
		AlexSetByteFree(0xEA, 0x06D0F9);
	}

	//Do Health Regen:


	if (BalancedHealthRegen && ShouldRunRegen()){
		bool hit = false;
		
		if (LastHealth > GetPlayerHealth()) {
			hit = true;
		}

		if (hit) {
			HitDelayCounter = HitDelay;
			FillDelayCounter = 0;
		}
		else {
			if (HitDelayCounter > 0) {
				HitDelayCounter--;
			}
			else {
				if (FillDelayCounter > 0) {
					FillDelayCounter--;
				}
				else {
					FillDelayCounter = FillDelay;
					SetPlayerHealth(GetPlayerHealth() + HealPerTick);
				}
			}
		}
		LastHealth = GetPlayerHealth();
	}


	//Do Magic Regen:
	if (BalancedMagicRegen && ShouldRunRegen()) {
		bool hit = false;

		if (LastMagic > GetPlayerMagic()) {
			hit = true;
		}

		if (hit) {
			UseDelayCounter = UseDelay;
			MFillDelayCounter = 0;
		}
		else {
			if (UseDelayCounter > 0) {
				UseDelayCounter--;
			}
			else {
				if (MFillDelayCounter > 0) {
					MFillDelayCounter--;
				}
				else {
					MFillDelayCounter = MFillDelay;
					SetPlayerMagic(GetPlayerMagic() + MRegenPerTick);
				}
			}
		}
		LastMagic= GetPlayerMagic();
	}
}


void SMMainLoop_Late() {


}




void SMOnEndRom() {



}

void SMOnLoadState() {
	HitDelayCounter = HitDelay;
	UseDelayCounter = UseDelay;
}

