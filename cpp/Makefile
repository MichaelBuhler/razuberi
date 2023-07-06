CXXFLAGS := -Werror=return-type $(CXXFLAGS)

source_headers := $(shell find -s src -name "*.h")
razuberi_headers := $(source_headers:src/%=out/include/%)

source_files := $(shell find -s src -name "*.cpp")
razuberi_objects := $(source_files:src/%.cpp=out/obj/%.o)

.PHONY: all
all: headers lib out/test

.PHONY: lib
lib: out/lib/librazuberi.a
out/lib/librazuberi.a: out/lib/librazuberi.a($(razuberi_objects)) | out/lib
	ranlib out/lib/librazuberi.a

out/lib/librazuberi.a($(razuberi_objects)): | out/lib

$(razuberi_objects): out/obj/%.o: src/%.cpp | out/obj
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: headers
headers: ${razuberi_headers}
$(razuberi_headers): out/include/%: src/% | out/include
	cp $< $@

.PHONY: test
test: out/test
	@echo Running out/test...
	@echo
	@out/test
out/test: out/obj/test.o out/lib/librazuberi.a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -Lout/lib -lrazuberi $< -o out/test
out/obj/test.o: test.cpp ${razuberi_headers} | out/obj
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -Iout/include test.cpp -o out/obj/test.o

.PHONY: clean
clean:
	rm -frv out

out:
	mkdir out
out/include: | out
	mkdir out/include
out/lib: | out
	mkdir out/lib
out/obj: | out
	mkdir out/obj

