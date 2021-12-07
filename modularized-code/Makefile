all: Entropia.png
entropia.x: coffee_entropy_main.cpp coffee_entropy.cpp coffee_entropy.h input.txt
	g++ -g -fsanitize=address -fsanitize=undefined -fsanitize=leak $< -o $@
entropia.txt: entropia.x
	./$< > $@
Entropia.png: graf_ent.gp entropia.txt
	gnuplot $<
clean:
	rm -f *.x *.png
