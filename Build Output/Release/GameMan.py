import os, subprocess, time, sys

# BaseRomName = "Super Metroid.sfc"
EmuPath = "Super Metroid - PC Edition-debug.exe"

def LaunchEmulator(RomFile = None):
    # global GameExec, AHKExec
    
    GameExec = None
    # AHKExec = None
    
    if RomFile == None:
        GameExec = subprocess.Popen([EmuPath])
        # AHKExec = subprocess.Popen("EMUAHK.exe")
    else:
        GameExec = subprocess.Popen([EmuPath, RomFile])
        # AHKExec = subprocess.Popen("EMUAHK.exe")
        
    GameExec.wait()
    # AHKExec.kill()
 
# print sys.argv
# Start Execution:
for i in sys.argv:
    if i.endswith(".sfc") or i.endswith(".smc"):
        LaunchEmulator(i)
        if "--batch" in sys.argv or "-b" in sys.argv :
            sys.exit()
        

while True:     
    os.system('cls')
    # print sys.argv

    RomList = os.listdir("Roms")
    
    if len(RomList) <= 0:
        print "No Roms Found"

        
        
    print "Available Roms to Load:"

    print "\t0: Load Emulator with no Rom (for configuration)"
    # print "\t1: Super Metroid (Vanilla Rom)"

    printIndex = 1
    for i in RomList:
        # if i == BaseRomName:
            # continue
        print "\t" + str(printIndex) + ": " + i.split(".")[0]
        printIndex += 1

        
    try:
        selectedRom = int(raw_input("Type the number of the desired rom (or leave blank to quit), and press Enter: "))
    except:
        print "Quitting..."
        time.sleep(1)
        sys.exit()

    print selectedRom



    if selectedRom <= 0:
        LaunchEmulator()

    elif (selectedRom - 1) >= len(RomList):
        print "Rom does not exist. Launching without Rom."
        LaunchEmulator()
        
    else:
        LaunchEmulator(RomList[selectedRom - 1])



# os.system("snes9x.exe project_base_0.7.3.SMC")