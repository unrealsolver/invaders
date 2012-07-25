SFML_LIB = -lsfml-graphics -lsfml-system -lsfml-window
SRC_PREFIX = ./src/

objects = main.o Entity.o Particle.o Ship.o Gui.o Grid.o

all: $(objects)
	g++ -o invaders $(objects) $(SFML_LIB)
	
main.o: main.cxx
	g++ -c main.cxx $(SFML_LIB)

Entity.o: Entity.cxx Entity.h
	g++ -c Entity.cxx

Particle.o: Particle.cxx Particle.h
	g++ -c Particle.cxx

Ship.o: Ship.cxx Ship.h
	g++ -c Ship.cxx

Gui.o: Gui.cxx Gui.h
	g++ -c  Gui.cxx
	
Grid.o: Grid.cxx Grid.h
	g++ -c Grid.cxx

.PHONY : clean
clean :
	rm  invaders $(objects)
