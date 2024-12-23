# Compile tool
tool: sdcc

install: `paru -S sdcc-svn`

**sdcc example use**
```bash
sdcc main.c -o main.ihx # compile source code to .ihx, but 51 need .hex to run, so we need another step to translate
packihx main.ihx > main.hex # step further translate to .hex
```

**How to specify 51 lib**
```c
#include <mcs51/8051.h>
```

# Flash tool
tool: stcflash

install: `paru -S stcflash-git`

**stcflash example use**
```bash
sudo stcflash main.hex # flash program to 51 directly, port will be auto detected
sudo stcflash main.hex --port /dev/ttyUSB1 --lowbaud 1200 # specify port & baudrate manually
```
# Simple Script

use the tool above to create a simple bash script making the process easier

**~/dotfile/bin/flash51**
```bash
#!/bin/bash

tmpdir=$(mktemp -d)

sdcc $1 -o "$tmpdir/tmp.ihx"
if [ $? -ne 0 ]; then
    rm -rf $tmpdir
    exit 1
fi

packihx "$tmpdir/tmp.ihx" >"$tmpdir/tmp.hex"

stcflash "$tmpdir/tmp.hex"
if [ $? -ne 0]; then
  rm -rf $tmpdir
  exit 1
fi
echo "Flash successful"

```

# Delay

# Key Dithering

when press a key down, there's may exists 5-10ms dithering, then become stable, the same as when key up


