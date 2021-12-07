all: Entropia.png
entropia.x: bosquejo.cpp input.txt
	g++ -g -fsanitize=address -fsanitize=undefined -fsanitize=leak $< -o $@
entropia.txt: entropia.x
	./$< > $@
Entropia.png: graf_ent.gp entropia.txt
	gnuplot $<
clean:
	rm -f *.x *.png
