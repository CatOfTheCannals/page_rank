report.pdf: report.tex sections/*.tex caratula.sty logo_dc.jpg logo_uba.jpg
	 pdflatex 		report.tex 	&& pdflatex 			report.tex # need to compile twice to make the index
	#pdflatex -shell-escape report.tex 	&& pdflatex -shell-escape 	report.tex # added -shell-escape for minted package (uses python)

.PHONY: clean
clean:
	rm -f report.pdf *.aux *.log *.toc *.out sections/*.aux sections/*.log sections/*.toc sections/*.out

