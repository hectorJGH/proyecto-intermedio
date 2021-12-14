all: Entropia.png

entropia.x: bosquejo.cpp input.txt
	g++ -g -fsanitize=address -fsanitize=undefined -fsanitize=leak $< -o $@

entropia.txt: entropia.x
	./$< > $@

Entropia.png: graf_ent.gp entropia.txt
	gnuplot $<

radius_fit.txt: entropia.txt
	sed -n '1,30000p' $< > $@

Radius_fit.png: graph_fit_radius.gp radius_fit.txt
	gnuplot $<

clean:
	rm -f *.x *.png *.log radius_fit.txt
