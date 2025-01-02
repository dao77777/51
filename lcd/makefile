.PHONY: all clean

all: main.hex
	@echo "done"

main.hex: main.ihx
	packihx $< > $@

main.ihx: main.rel delay.rel LCD1602.rel
	sdcc $^ -o $@

delay.rel: ./src/delay.c
	sdcc -c $< -o $@ -I ./include

LCD1602.rel: ./src/LCD1602.c
	sdcc -c $< -o $@ -I ./include

main.rel: main.c
	sdcc -c $< -o $@ -I ../../include

clean:
	rm -rf *.rel *.asm *.rst *.sym *.lst *.hex *.lk *.ihx *.map *.mem
