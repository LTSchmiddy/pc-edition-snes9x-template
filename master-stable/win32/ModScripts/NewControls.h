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


//New Controls:

extern const uint32 Menu_Up;
extern const uint32 Menu_Down;
extern const uint32 Menu_Left;
extern const uint32 Menu_Right;
extern const uint32 Menu_A;
extern const uint32 Menu_B;

extern const uint32 Control_Up;
extern const uint32 Control_Down;
extern const uint32 Control_Left;
extern const uint32 Control_Right;
extern const uint32 Control_A;
extern const uint32 Control_B;


bool NewControlsInputUpdate(uint32, bool);

void NewControlsGameplayInputUpdate(uint32, bool);

void Input_OnUpdate(void);
