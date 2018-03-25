cppfiles=$(wildcard ./*.cpp)
objfiles=$(patsubst %.cpp,%.o,$(cppfiles))
<<<<<<< HEAD
cppfiles=./rabbitmq_client.cpp
=======

cppfiles=./rabbitmq_client.cpp

>>>>>>> a4e337f93adee7a160ceb457a86d42fc9257ab24
target=rbmq_client.out

CXX=g++
STD=-std=c++11
LIBRARY=-lSimpleAmqpClient -lrabbitmq
FLAGS= -Wall -g
LIB_INCLUDE=/usr/local/lib64

all:$(target)

$(target):$(objfiles)
	$(CXX) -o $@ $^ $(STD) $(FLAGS) -I$(LIB_INCLUDE) $(LIBRARY)

$(objfiles):$(cppfiles)
	gcc -c $< -o $@  

clean:
	rm -rf ./*.o

.PHONY:clean all
