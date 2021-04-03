# this variable will contain the names of all c source files
SRCS:=$(wildcard src/*.c)

# this will contain the names of all intermediate object files
OBJECTS:=$(patsubst src/%.c,bin/%.o,$(SRCS))

# $< are the names of all prerequisites (the object files)
# $@ is the name of the target (obj/myprogram in this case)
main: $(OBJECTS)
	gcc $^ -o $@ 

# but now we have to tell make how to build the object files
# -c option tells g++ to only compile one source file at a tile
#  $< is the name of the first prerequisite (the c file in this case)
bin/%.o: src/%.c
	gcc $< -c -o $@ 

clean:
	rm main -f bin/*.o