LDFLAGS = -pthread
CXXFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./src -I./tests \
	--std=c++11 \

CXXFLAGS += -Wall
#CXXFLAGS += -O3 

FILEOPS_TEST = \
	tests/test_common.o \
	tests/fileops_test.o \
	src/fileops_posix.o \

KEYVALUE_TEST = \
	tests/test_common.o \
	tests/keyvalue_test.o \

LOG_TEST = \
	tests/test_common.o \
	tests/log_test.o \
	src/fileops_posix.o \
	src/log_dummy.o \

PROGRAMS = \
	tests/fileops_test \
	tests/keyvalue_test \
	tests/log_test \

all: $(PROGRAMS)

tests/fileops_test: $(FILEOPS_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

tests/keyvalue_test: $(KEYVALUE_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

tests/log_test: $(LOG_TEST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so ./*/*.o ./*/*.so