
#include "test_common.h"

TestSuite::TestSuite() :
    cntPass(0),
    cntFail(0)
{
}

TestSuite::~TestSuite()
{
    printf(_CL_GREEN("%zu") " tests pased", cntPass);
    if (cntFail) {
        printf(", " _CL_RED("%zu") " tests failed", cntFail);
    }
    printf(" out of " _CL_CYAN("%zu") "\n", cntPass+cntFail);
}

std::string TestSuite::getTestFileName(std::string prefix)
{
    std::string ret = prefix;
    int rnd_num = std::rand();
    ret += "_";
    ret += std::to_string(rnd_num);
    return ret;
}

void TestSuite::clearTestFile(std::string prefix)
{
    int r;
    (void)r;
    std::string command = "rm -f ";
    command += prefix;
    command += "*";
    r = system(command.c_str());
}

void TestSuite::doTest(std::string test_name,
                       test_func *func,
                       TestArgsBase *args)
{
    int ret = func();
    if (ret < 0) {
        printf("[ " _CL_RED("FAIL") " ] %s\n", test_name.c_str());
        cntFail++;
    } else {
        printf("[ " _CL_GREEN("PASS") " ] %s\n", test_name.c_str());
        cntPass++;
    }
}

