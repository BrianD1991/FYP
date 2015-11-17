CXX = g++
CXXFLAGS=  -std=gnu++11  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -fopenmp

%.o : %.cpp %.h
	$(CXX)  -c *.cpp  $(CXXFLAGS)


ALL: *.o
	$(CXX) *.o -o Sugarscape  $(CXXFLAGS)


DEBUG: *.o
	$(CXX) -g *.o -o Sugarscape $(CXXFLAGS)

CLEAN:
	rm *.o


