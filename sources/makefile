#OBJS specifies which files to compile as part of the project
OBJ = Main

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lGL -lGLEW

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJ).cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ)