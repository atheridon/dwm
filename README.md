# Fork of dwm

The [suckless dwm (dynamic window manager)](https://dwm.suckless.org/).

## Patches applied

+ actualfullscreen
+ alpha
+ autostart
+ cfacts
+ hide vacant tags
+ noborder
+ pertag
+ resetlayout
+ resizecorners
+ scratchpad
+ stacker 
+ statusallmons
+ swallow 
+ systray
+ vanitygaps

### cfacts + vanitygaps
Big thanks to [bakkeby](https://github.com/bakkeby) for his cfacts-vanitygaps patch that made both work when combined in dwm!

### systray + picom/compton shadow
Picom (compton) will not put a shadow on the systray icons with this dwm build. Thanks again to [bakkeby](https://github.com/bakkeby) for helping me out with this! Patch for this can be found in the patches/ directory.

## Configuration

Simply modify the `config.h` file. 
Default configuration is stored in `config.def.h`.

## Installation

```
sudo make clean install
```
