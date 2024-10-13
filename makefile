CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = monopoly
OBJS = main.o Game.o Board.o Player.o Dice.o Space.o GUI.o
TEST_OBJS = tests.o Game.o Board.o Player.o Dice.o Space.o GUI.o
SOURCES = main.cpp Game.cpp Board.cpp Player.cpp Dice.cpp Space.cpp GUI.cpp
INCLUDES = -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

tests: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o tests $^ $(INCLUDES) $(LIBS)
	./tests

clean:
	rm -f $(TARGET) $(OBJS) tests $(TEST_OBJS)
