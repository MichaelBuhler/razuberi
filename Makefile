library_objects := out/lib/builtin_objects.o
library_objects += out/lib/exception.o
library_objects += out/lib/global_scope.o
library_objects += out/lib/host_objects.o
library_objects += out/lib/scope.o
library_objects += out/lib/type_conversion.o
library_objects += out/lib/value.o

.PHONY: all
all: library test

.PHONY: library
library: out/razuberi.a
out/razuberi.a: out/razuberi.a(${library_objects}) | out
	ranlib out/razuberi.a

$(library_objects): out/lib/%.o: lib/%.cpp | out/lib
	g++ -c $< -o $@

test: out/razuberi.a test.cpp
	g++ $^ -o test 

out:
	mkdir out
out/lib: | out
	mkdir out/lib

.PHONY: clean
clean:
	rm -frv out

Makefile:
	echo remaking....
