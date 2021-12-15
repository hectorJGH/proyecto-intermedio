all: Entropia.png

entropia.x: coffee_entropy_main.cpp coffee_entropy.cpp coffee_entropy.h input.txt
	g++ -O3 -g -fsanitize=address -fsanitize=undefined -fsanitize=leak coffee_entropy.h coffee_entropy.cpp $< -o $@

entropia.txt: entropia.x
	./$< > $@

Entropia.png: graf_ent.gp entropia.txt
	gnuplot $<

radius_fit.txt: entropia.txt
	sed -n '1,30000p' $< > $@

Radius_fit.png: graph_fit_radius.gp radius_fit.txt
	gnuplot $<

f_eq: graf_fit_equilibrio.gp lattice_v_t_eq.txt
	gnuplot $<

punto_2.x: punto_2.cpp coffee_entropy.h coffee_entropy.cpp
	g++ -O3 -g -fsanitize=address -fsanitize=undefined -fsanitize=leak coffee_entropy.h coffee_entropy.cpp $< -o $@

graph_p_2: punto_2.x input.txt
	./$< | gnuplot

clean:
	rm -f *.x *.png *.log radius_fit.txt
