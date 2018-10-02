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



extern const uint32 HasBowAddress;
extern const uint32 HasBoomerangAddress;
extern const uint32 HasHookshotAddress;
extern const uint32 HasBombsAddress;
extern const uint32 HasHammerAddress;
extern const uint32 HasLampAddress;


int GetPlayerHealth(void);

int GetMaxPlayerHealth(void);

void SetPlayerHealth(unsigned);


int GetPlayerMagic(void);

int GetMaxPlayerMagic(void);

void SetPlayerMagic(unsigned);

bool HasItem(uint32);