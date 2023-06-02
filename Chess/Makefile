TARGET = Myproject
CC = g++

PREF_SRC = ./Implement_of_Figures/
PREF_OBJ = ./Obj_Files/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	@$(CC) $(OBJ) -o $(TARGET) -lraylib

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	@$(CC) -c $< -o $@

clean : 
	rm $(TARGET) $(PREF_OBJ)*.o

install : 
	cp /usr/bin
