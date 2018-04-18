DOT_FILES=$(wildcard *.dot)
DOTPNG=$(DOT_FILES:.dot=.png)

%.png: %.dot
	neato -Tpng $< > $@

.PHONY: dot
dot: $(DOTPNG)

complete_col.png: complete_col.dot
	dot -Tpng complete_col.dot > complete_col.png

complete_col_and_k_to_col.png: complete_col_and_k_to_col.dot
	dot -Tpng complete_col_and_k_to_col.dot > complete_col_and_k_to_col.png

.PHONY: clean
clean:
	rm *.png

