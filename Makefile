CXX := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN := bin
SRC := src
INCLUDE := include
LIB := lib

LIBRARIES :=
EXECUTABLE := json_driver

SO_NAME := json

LIB_INSTALL_DIR := /usr/lib
BIN_INSTALL_DIR := /usr/local/bin

all: $(LIB)/lib$(SO_NAME).so $(BIN)/$(EXECUTABLE)

run: clean all
		./$(BIN)/$(EXECUTABLE)

$(LIB)/lib$(SO_NAME).so: $(SRC)/$(SO_NAME)/*.cpp
	$(CXX) $(CXX_FLAGS) -fPIC -c -Wall -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE): $(SRC)/$(EXECUTABLE)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES) -L$(LIB) -l$(SO_NAME)

clean:
	-rm -f $(BIN)/*
	-rm -f $(LIB)/*

install:
	cp $(LIB)/lib$(SO_NAME).so $(LIB_INSTALL_DIR)/
	cp $(BIN)/$(EXECUTABLE) $(BIN_INSTALL_DIR)/

remove:
	rm $(LIB_INSTALL_DIR)/lib$(SO_NAME).so
	rm $(BIN_INSTALL_DIR)/$(EXECUTABLE)
