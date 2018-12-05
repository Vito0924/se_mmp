INC:= ./inc/ ./cppjieba/include/cppjieba ./cppjieba/deps/
SRC:=$(wildcard ./src/*.cc)
OBJ:=$(patsubst %.cc,%.o,$(SRC))
#LIB:=
EXE:=./bin/se.exe
CPPFLAGS:=-Wall -std=c++11 $(addprefix -I,$(INC)) # $(LIB) 

$(EXE):$(OBJ)
	g++ $^ -o $@ $(CPPFLAGS) -lboost_regex
clean:
	rm -r $(EXE)
	rm -r $(OBJ)
	rm ./data/*
