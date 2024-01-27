SRC_DIR := ./src

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRC_FILES))

backtester: $(OBJ_FILES)
	g++ $(OBJ_FILES) -o backtester 

%.o: $(SRC_DIR)/%.cpp
	g++ -c $(SRC_FILES)

clean:
	del *.o
	del backtester.exe
