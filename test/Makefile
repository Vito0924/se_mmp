INC:=./cppjieba/include/cppjieba ./cppjieba/deps/
SRC:=$(wildcard ./*.cc)
OBJ:=$(patsubst %.cc,%.o,$(SRC))
EXE:=./main.exe
CPPFLAGS:=-Wall -std=c++11 $(addprefix -I,$(INC))
$(EXE):$(OBJ)
	g++ -o $@ $^ $(CPPFLAGS)
clean:
	rm $(OBJ)
	rm $(EXE)
