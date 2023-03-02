BINARY = ConsoleLogbook
OBJECTS = main.o cl_session.o cl_session_manager.o
HEADERS = cl_session.hpp cl_session_manager.hpp cl_parse.hpp

CFLAGS = g++ -std=c++11 -O0 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -g

.PHONY: all clean

all: $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)

$(BINARY): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@