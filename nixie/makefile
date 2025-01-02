.PHONY: all clean

all: main.hex
	@echo "done"

main.hex: main.ihx
	packihx $< > $@

main.ihx: main.rel delay.rel LCD1602.rel matrix_key.rel nixie.rel
	sdcc $^ -o $@

nixie.rel: ./src/nixie.c
	sdcc -c $< -o $@ -I ./include

matrix_key.rel: ./src/matrix_key.c
	sdcc -c $< -o $@ -I ./include

delay.rel: ./src/delay.c
	sdcc -c $< -o $@ -I ./include

LCD1602.rel: ./src/LCD1602.c
	sdcc -c $< -o $@ -I ./include

main.rel: main.c
	sdcc -c $< -o $@ -I ./include

clean:
	rm -rf *.rel *.asm *.rst *.sym *.lst *.hex *.lk *.ihx *.map *.mem
