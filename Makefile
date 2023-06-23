library_headers := out/include/builtin_objects.h
library_headers += out/include/exception.h
library_headers += out/include/global_scope.h
library_headers += out/include/host_objects.h
library_headers += out/include/razuberi.h
library_headers += out/include/scope.fwd.h
library_headers += out/include/scope.h
library_headers += out/include/type_conversion.h
library_headers += out/include/value.fwd.h
library_headers += out/include/value.h

library_objects := out/tmp/builtin_objects.o
library_objects += out/tmp/exception.o
library_objects += out/tmp/global_scope.o
library_objects += out/tmp/host_objects.o
library_objects += out/tmp/razuberi.o
library_objects += out/tmp/scope.o
library_objects += out/tmp/type_conversion.o
library_objects += out/tmp/value.o

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
