
stand=-std=c++11
CXX=g++
FLAGS= -Wall -g 
LIBS= -lprotobuf

sout=protbuf.out
target=$(sout)
main_cpp=protobuf_serv.cpp
src_cc=$(wildcard ./src/*.cc)
src_cpp=$(wildcard ./src/*.cpp)

ccobj=$(patsubst %.cc,%.o,$(src_cc))
cppobj=$(patsubst %.cpp,%.o,$(src_cpp))

all:$(target)


$(ccobj):%.o:%.cc
	$(CXX) -c $< -o $@  $(stand) 

$(cppobj):%.o:%.cpp
	$(CXX) -c $< -o $@  $(stand) 

$(sout):$(ccobj) $(cppobj)
	$(CXX) -o $@ $(main_cpp) $^  $(FLAGS) $(stand) $(LIBS)


clean:
	rm -rf $(ccobj) $(cppobj) 
	rm -rf $(target)

.PHONEY:all clean










