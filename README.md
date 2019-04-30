# GBMO

GBMO is a Nintendo GameBoy emulator written in C++. It uses the SDL2 library.

The emulator is currently in its version 0.7 so please be aware of some missing functionallity and some bugs. Please check the version history and ![roadmap](https://github.com/jcornejope/GBMO/blob/master/roadmap.txt).
The current version already supports CPU, display, joypad, memory and cartridge emulation including MBC1, MBC2 and MBC3 bank controllers and save and load to/from cartridges with battery support.

The CPU passes all Blargg CPU Instruction tests.

![blargg_cpu](https://github.com/jcornejope/GBMO/blob/master/gif/gbmo_v0.7_blargg_test_passed.png)

It emulates a wide variety of games (Please note that due to format compression and size restriction these gifs are not fully representative of the actual quality and framerate):

![z](https://github.com/jcornejope/GBMO/blob/master/gif/z_gbmo_v0.7_5fps.gif)
![cl](https://github.com/jcornejope/GBMO/blob/master/gif/cl_gbmo_v0.7_7fps.gif)
![sml](https://github.com/jcornejope/GBMO/blob/master/gif/sml_gbmo_v0.7_20fps.gif)
![t](https://github.com/jcornejope/GBMO/blob/master/gif/t_gbmo_v0.7_20fps.gif)
![m2](https://github.com/jcornejope/GBMO/blob/master/gif/m2_gbmo_v0.7_20fps.gif)
![pb](https://github.com/jcornejope/GBMO/blob/master/gif/pb_gbmo_v0.7_7fps.gif)

## Command line args

> -F 
  - FullScreen Keep Aspect Ratio: ( -F ) Starts the emulator in fullscreen mode adding black bars to the sides to keep the original aspect ratio.
> -f 
  - FullScreen: ( -f ) Starts the emulator in fullscreen mode stretching the image to fit the screen.
> -p 
  - Position: ( -p <x> <y> ) Window position when starting the application. Negative values will center the screen.
> -P
  - Palette index: ( -P <palette_index> ) Index of the palette to use at startup.
> -s or -S 
  - Screen scale: ( -s <screen_scale> ) Integer value for the screen scalar.
> -r or -R 
  - Rom: ( -r <rom_path> )
> -l or -L 
  - Log: ( -l <log_file> ) An empty log file means no log. No option will use the default file (".\log.txt").
  