main: paper.pdf

scatter_data.txt: config.yml
	python create_scatter_data.py

top.pdf: scatter_data.txt
	python top_view.py

x.pdf: scatter_data.txt
	python x_view.py

y.pdf: scatter_data.txt
	python y_view.py

paper.pdf: paper.tex x.pdf y.pdf top.pdf
	pdflatex paper.tex

clean:
	rm -f hello_world.txt *.pdf scatter_data.txt

