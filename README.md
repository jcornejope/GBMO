# GBMO

GBMO is a Nintendo GameBoy emulator written in C++. It uses the ![SDL2](https://www.libsdl.org/), ![LibZip](https://github.com/nih-at/libzip) (which uses ![ZLib](https://www.zlib.net/)) and ![inih](https://github.com/jtilly/inih) libraries.

The emulator is currently in its version 0.8 so please be aware of some missing functionallity and some bugs. Please check the version history and ![roadmap](https://github.com/jcornejope/GBMO/blob/master/roadmap.txt).
The current version already supports CPU, display, joypad, memory and cartridge emulation including MBC1, MBC2 and MBC3 bank controllers and save and load to/from cartridges with battery support.

The CPU passes all Blargg CPU Instruction tests.

![blargg_cpu](https://github.com/jcornejope/GBMO/blob/master/gif/gbmo_v0.7_blargg_test_passed.png)
![blargg_cpu_timing](https://github.com/jcornejope/GBMO/blob/master/gif/gbmo_v0.7_cpu_instr_passed.png)

It emulates a wide variety of games (Please note that due to format compression and size restriction these gifs are not fully representative of the actual quality and framerate):

![z](https://github.com/jcornejope/GBMO/blob/master/gif/z_gbmo_v0.7_5fps.gif)
![cl](https://github.com/jcornejope/GBMO/blob/master/gif/cl_gbmo_v0.7_7fps.gif)
![sml](https://github.com/jcornejope/GBMO/blob/master/gif/sml_gbmo_v0.7_20fps.gif)
![t](https://github.com/jcornejope/GBMO/blob/master/gif/t_gbmo_v0.7_20fps.gif)
![m2](https://github.com/jcornejope/GBMO/blob/master/gif/m2_gbmo_v0.7_20fps.gif)
![pb](https://github.com/jcornejope/GBMO/blob/master/gif/pb_gbmo_v0.7_7fps.gif)
  
