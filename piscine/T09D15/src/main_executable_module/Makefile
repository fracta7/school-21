#compiler
CC = gcc

#flags for the compiler
FLAGS = -Wextra -Wall -Werror

#Source files
MAIN_SRC = main_executable_module.c
DATA_IO_SRC = ../data_libs/data_io.c
DATA_PROCESS_SRC = ../data_module/data_process.c
DECISION_SRC = ../yet_another_decision_module/decision.c
DATA_STAT_SRC = ../data_libs/data_stat.c

#OBJ files
MAIN_EXECUTABLE_OBJ = ../../build/main_executable_module.o
DATA_IO_OBJ = ../../build/data_io.o
DATA_PROCESS_OBJ = ../../build/data_process.o
DECISION_OBJ = ../../build/decision.o
DATA_STAT_OBJ = ../../build/data_stat.o
DATA_STAT_LIB_STAT = ../../build/libdata_stat.a
DATA_PROCESS_DYN = ../../build/libdata_process.so

#build files
QUEST_3 = ../../build/Quest_3
QUEST_5 = ../../build/Quest_5
QUEST_6 = ../../build/Quest_6

all : build build_with_static build_with_dynamic

build : $(MAIN_EXECUTABLE_OBJ) $(DATA_IO_OBJ) $(DATA_PROCESS_OBJ) $(DECISION_OBJ) $(DATA_STAT_OBJ)
	$(CC) $(FLAGS) $(MAIN_EXECUTABLE_OBJ) $(DATA_IO_OBJ) $(DATA_PROCESS_OBJ) $(DECISION_OBJ) $(DATA_STAT_OBJ) -o $(QUEST_3) -lm

build_with_static : $(MAIN_EXECUTABLE_OBJ) $(DATA_IO_OBJ) $(DATA_PROCESS_OBJ) $(DECISION_OBJ) $(DATA_STAT_LIB_STAT)
	$(CC) $(FLAGS) $(MAIN_EXECUTABLE_OBJ) $(DATA_IO_OBJ) $(DATA_PROCESS_OBJ) $(DECISION_OBJ) -L../../build -ldata_stat -o $(QUEST_5) -lm

build_with_dynamic : $(MAIN_EXECUTABLE_OBJ) $(DATA_IO_OBJ) $(DATA_STAT_OBJ) $(DECISION_OBJ) $(DATA_PROCESS_DYN)
	$(CC) $(FLAGS) $(MAIN_EXECUTABLE_OBJ) $(DATA_IO_OBJ) $(DATA_STAT_OBJ) $(DECISION_OBJ) -L../../build -ldata_process -o $(QUEST_6) -lm

$(MAIN_EXECUTABLE_OBJ) : $(MAIN_SRC)
	$(CC) $(FLAGS) -c $(MAIN_SRC) -o $(MAIN_EXECUTABLE_OBJ)


$(DATA_IO_OBJ) : $(DATA_IO_SRC)
	$(CC) $(FLAGS) -c $(DATA_IO_SRC) -o $(DATA_IO_OBJ)


$(DATA_PROCESS_OBJ) : $(DATA_PROCESS_SRC)
	$(CC) $(FLAGS) -c $(DATA_PROCESS_SRC) -o $(DATA_PROCESS_OBJ)


$(DECISION_OBJ) : $(DECISION_SRC)
	$(CC) $(FLAGS) -c $(DECISION_SRC) -o $(DECISION_OBJ)


$(DATA_STAT_OBJ) : $(DATA_STAT_SRC)
	$(CC) $(FLAGS) -c $(DATA_STAT_SRC) -o $(DATA_STAT_OBJ)

$(DATA_STAT_LIB_STAT) : $(DATA_STAT_OBJ)
	ar rcs $(DATA_STAT_LIB_STAT) $(DATA_STAT_OBJ)

$(DATA_PROCESS_DYN) : $(DATA_PROCESS_OBJ)
	$(CC) $(FLAGS) -fPIC -shared $(DATA_PROCESS_OBJ) -o $(DATA_PROCESS_DYN)

rebuild :
	clean build

clean :
	rm -rf ../../build/*.o ../../build/*.a ../../build/*.so $(QUEST_3) $(QUEST_5) $(QUEST_6)
