test: out/test.o out/lib/exception.o out/lib/host_objects.o out/lib/scope.o out/lib/type_conversion.o out/lib/value.o
	g++ -o test out/test.o out/lib/exception.o out/lib/host_objects.o out/lib/scope.o out/lib/type_conversion.o out/lib/value.o

out/test.o: out test.cpp
	g++ -c -o out/test.o $(CFLAGS) test.cpp

out/lib/exception.o: out/lib lib/exception.cpp lib/exception.h
	g++ -c -o out/lib/exception.o lib/exception.cpp
out/lib/host_objects.o: out/lib lib/host_objects.cpp lib/host_objects.h
	g++ -c -o out/lib/host_objects.o lib/host_objects.cpp
out/lib/scope.o: out/lib lib/scope.cpp lib/scope.h lib/scope.fwd.h lib/value.h lib/value.fwd.h
	g++ -c -o out/lib/scope.o lib/scope.cpp
out/lib/type_conversion.o: out/lib lib/type_conversion.cpp lib/type_conversion.h lib/exception.h lib/value.h
	g++ -c -o out/lib/type_conversion.o lib/type_conversion.cpp
out/lib/value.o: out/lib lib/value.cpp lib/value.h lib/value.fwd.h lib/type_conversion.h lib/exception.h lib/scope.h lib/scope.fwd.h
	g++ -c -o out/lib/value.o lib/value.cpp

out:
	mkdir -p out
out/lib: out
	mkdir -p out/lib

clean:
	rm -frv out
