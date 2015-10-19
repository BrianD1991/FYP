CXX = g++
CXXFLAGS=  -std=gnu++11  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


%.o : %.cpp %.h
	g++ -std=gnu++11 -c *.cpp -lsfml-graphics -lsfml-window -lsfml-system


ALL: *.o
	g++ -std=gnu++11 *.o -o Sugarscape -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


