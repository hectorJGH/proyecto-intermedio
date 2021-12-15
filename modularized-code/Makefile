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

comp_gprof_1.x: coffee_entropy_main.cpp coffee_entropy.cpp coffee_entropy.h
	g++ -g -pg -Wall coffee_entropy.h coffee_entropy.cpp $< -o $@

gprof_1: comp_gprof_1.x
	./$< > basura.txt ;\
	gprof ./$< gmon.out > gprof-report_1.txt

comp_gprof_2.x: punto_2_main.cpp coffee_entropy.cpp coffee_entropy.h
	g++ -g -pg -Wall coffee_entropy.h coffee_entropy.cpp $< -o $@

gprof_2: comp_gprof_2.x
	./$< > basura.txt ;\
	gprof ./$< gmon.out > gprof-report_2.txt

comp_cach_1.x: coffee_entropy_main.cpp coffee_entropy.cpp coffee_entropy.h
	g++ -g coffee_entropy.h coffee_entropy.cpp $< -o $@

cachegrind_1: comp_cach_1.x
	rm cachegrind.out.* ;\
	valgrind --tool=cachegrind ./$< > basura.txt ;\
	cg_annotate --auto=yes cachegrind.out.* > cachegrind-report.txt

comp_cach_2.x: punto_2_main.cpp coffee_entropy.cpp coffee_entropy.h
	g++ -g coffee_entropy.h coffee_entropy.cpp $< -o $@

cachegrind_2: comp_cach_2.x
	valgrind --tool=cachegrind ./$<

comp_memc_1.x: coffee_entropy_main.cpp coffee_entropy.cpp coffee_entropy.h
	g++ -g coffee_entropy.h coffee_entropy.cpp $< -o $@

memcheck_1: comp_memc_1.x
	valgrind --tool=memcheck ./$< >basura.txt

comp_memc_2.x: punto_2_main.cpp coffee_entropy.cpp coffee_entropy.h
	g++ -g coffee_entropy.h coffee_entropy.cpp $< -o $@

memcheck_2: comp_memc_2.x
	valgrind --tool=memcheck ./$< >basura.txt

#targets punto 4
hole.x: punto_4_main.cpp input4.txt coffee_entropy.h coffee_entropy.cpp
	g++ -g -fsanitize=address -fsanitize=undefined -fsanitize=leak coffee_entropy.h coffee_entropy.cpp $< -o $@

hole.txt: hole.x
	./$< > $@

hole_last.txt: hole.txt
	sed -n '100000,1000000p' $< > $@

Hole_fit.png: graph_hole.gp hole_last.txt hole.txt
	gnuplot $<
###
Time.png: time.gp time.txt
	gnuplot $<

report: Informe.tex Entropy.png Fit_equilibrium.png Hole_fit.png Radius_fit.png Time.png
	pdflatex $<

clean:
	rm -f *.x *.png *.log radius_fit.txt basura.txt *.out* 
