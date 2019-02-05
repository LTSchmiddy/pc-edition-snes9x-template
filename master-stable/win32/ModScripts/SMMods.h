//#pragma once


//#include <map>
//#include <set>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <assert.h>
//#include <ctype.h>


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

//Config Variables:

extern bool UseNewControls;

//extern bool SaveStationsHeal;
//extern bool XraySMRedesignMode;
//extern bool AllowChargeBeamToggling;
//extern bool QuitOnExit;


//Methods:
bool ShouldRunRegen();

void HideMenu(void);
void SMOnLoadState(void);


void SMOnLoadRom(void);

bool ModInputUpdate(uint32 id, bool pressed);

void ModGameplayControl(uint32 id, bool pressed);


void SMMainLoop(void);


void SMMainLoop_Late(void);

void SMOnEndRom(void);