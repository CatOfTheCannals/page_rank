DOT_FILES=$(wildcard *.dot)
DOTPNG=$(DOT_FILES:.dot=.png)

%.png: %.dot
	neato -Tpng $< > $@ #&& viewnior $@ &

.PHONY: dot
dot: $(DOTPNG)


.PHONY: clean
clean:
	rm *.png

