source_headers := $(shell find -s lib -name "*.h")
library_headers := $(source_headers:lib/%=out/include/%)

source_files := $(shell find -s lib -name "*.cpp")
library_objects := $(source_files:lib/%.cpp=out/tmp/%.o)

.PHONY: all
all: library headers test

.PHONY: library
library: out/lib/librazuberi.a
out/lib/librazuberi.a: out/lib/librazuberi.a($(library_objects)) | out/lib
	ranlib out/lib/librazuberi.a

out/lib/librazuberi.a($(library_objects)): | out/lib

$(library_objects): out/tmp/%.o: lib/%.cpp | out/tmp
	g++ -c $< -o $@

.PHONY: headers
headers: ${library_headers}
$(library_headers): out/include/%: lib/% | out/include
	cp $< $@

out/tmp/test.o: test.cpp ${library_headers} | out/tmp
	g++ -Iout/include -c test.cpp -o out/tmp/test.o

test: out/tmp/test.o out/lib/librazuberi.a
	g++ -Lout/lib -lrazuberi $< -o test

out:
	mkdir out
out/include: | out
	mkdir out/include
out/lib: | out
	mkdir out/lib
out/tmp: | out
	mkdir out/tmp

.PHONY: clean
clean:
	rm -frv out
