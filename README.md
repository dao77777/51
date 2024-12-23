# Compile tool
Tool: sdcc

Install: `paru -S sdcc-svn`

**Sdcc example use**
```bash
sdcc main.c -o main.ihx # compile source code to .ihx, but 51 need .hex to run, so we need another step to translate
packihx main.ihx > main.hex # step further translate to .hex
```

**How to specify 51 lib**
```c
#include <mcs51/8051.h>
```

# Flash tool
Tool: stcflash

Install: `paru -S stcflash-git`

**Stcflash example use**
```bash
sudo stcflash main.hex # flash program to 51 directly, port will be auto detected
sudo stcflash main.hex --port /dev/ttyUSB1 --lowbaud 1200 # specify port & baudrate manually
```
# Simple Script

Use the tool above to create a simple bash script making the process easier

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

```c
void delay(unsigned int time) {
  unsigned ini i, j;
  for (i = 1; i <= time; i++)
    for (j = 1; j <= 100; j++);
}
```

# Peripheral

## LED

Pin map: P2_0-P2_7

## Key

Pin map
- P3_1: K1
- P3_0: K2
- P3_2: K3
- P3_3: K4

**Dithering**

When press a key down, there's may exists 5-10ms dithering, then become stable, the same as when key up

## Nixie

Pin map
- P2_2, P2_3, P2_4: Position Select according to 138 decoder
- P0_0-P0_7: Segment Select according to bidirectional data transfer

***Segment select*** & ***Position select***

All nixie share the same segment select, but with different position select

Segment Select can be ether ***common anode*** or ***common anode***

Commonly, the Position select is implemented according to 138 decoder translating 3-bit to 8-bit, the Segment select is implemented according to bidirectional data transfer

Driver: mcu drive or dedicated drive chip

## Decoder

Translate 3-bit to 8-bit

138 Decoder: 74LS138

## Bidirectional Data Transfer

Change the direction of data transfer & increase the driving capability

74HC245
