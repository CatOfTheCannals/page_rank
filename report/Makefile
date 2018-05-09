report.pdf: report.tex sections/*.tex caratula.sty logo_dc.jpg logo_uba.jpg
	pdflatex report.tex && pdflatex report.tex # need to compile twice to make the index

.PHONY: clean
clean:
	rm -f report.pdf *.aux *.log *.toc *.out sections/*.aux sections/*.log sections/*.toc sections/*.out

