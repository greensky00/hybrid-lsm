LDFLAGS = -pthread
CXXFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./src -I./tests \
	--std=c++11 \

#CXXFLAGS += -Wall
#CXXFLAGS += -O3 

FILEOPS_TEST = \
	tests/test_common.o \
	tests/fileops_test.o \
	src/fileops_posix.o \

PROGRAMS = \
	tests/fileops_test \

all: $(PROGRAMS)

tests/fileops_test: $(FILEOPS_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so