# MouseAccelFix
Fix shitty mouse acceleration in games such as Nier Replicant (remaster)
Basically what this does, is it disables mouse acceleration and sets sensitivity to a certain value whenever the game window is in focus.
It was originally made (and only tested) on NieR Replicant ver.1.22474487139 but it might work on other games with similar problem.
Usage instructions: Download the DLL and rename it to DXGI.DLL, then copy the real DXGI.DLL from system32 and rename it to DXG2.DLL and put both the modded DXGI.DLL and DXG2.DLL into the game directory.
Optionally you may create a file called MouseAccelFix.ini in the game directory with a format the same as the MouseAccelFix.ini file in the releases page.
