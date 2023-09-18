CXX = g++
CXXFLAGS = -Wall

proj3: 	Strand.o Sequencer.o proj3.cpp
	$(CXX) $(CXXFLAGS) Strand.o Sequencer.o proj3.cpp -o proj3

driver: 	Shop.o Game.o Ingredient.h driver.cpp
	$(CXX) $(CXXFLAGS) Shop.o Ingredient.h Game.o driver.cpp -o driver

Sequencer.o: Strand.o Sequencer.cpp Sequencer.h
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

Strand.o: Strand.h Strand.cpp 
	$(CXX) $(CXXFLAGS) -c Strand.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3 proj3_data1.txt