#pragma once

#include <string>
#include <iostream>

typedef int (test_func)();

#define _CLM_GREEN     "\033[32m"
#define _CLM_B_GREEN   "\033[1;32m"
#define _CLM_RED       "\033[31m"
#define _CLM_B_RED     "\033[1;31m"
#define _CLM_BLUE       "\033[34m"
#define _CLM_B_BLUE     "\033[1;34m"
#define _CLM_MAGENTA   "\033[35m"
#define _CLM_B_MAGENTA "\033[1;35m"
#define _CLM_CYAN      "\033[36m"
#define _CLM_END       "\033[0m"

#define _CL_GREEN(str)     _CLM_GREEN str _CLM_END
#define _CL_RED(str)       _CLM_RED str _CLM_END
#define _CL_MAGENTA(str)   _CLM_MAGENTA str _CLM_END
#define _CL_B_MAGENTA(str) _CLM_MAGENTA str _CLM_END
#define _CL_CYAN(str)      _CLM_CYAN str _CLM_END


#define CHK_EQ(exp_value, value) \
    if (exp_value != value) { \
        std::cout << "\n    " _CLM_GREEN << __FILE__ << _CLM_END "::"; \
        std::cout << _CLM_GREEN << __LINE__ << _CLM_END << ",\n" ; \
        std::cout << "      " _CLM_CYAN << __func__ << "()" _CLM_END; \
        std::cout << ", value of " _CLM_B_BLUE #value _CLM_END "\n"; \
        std::cout << "    expected: " _CLM_B_GREEN << exp_value << _CLM_END "\n"; \
        std::cout << "      actual: " _CLM_B_RED << value << _CLM_END "\n"; \
        return -1; \
    } \

#define CHK_OK(value) \
    if (!value) { \
        std::cout << "\n    " _CLM_GREEN << __FILE__ << _CLM_END "::"; \
        std::cout << _CLM_GREEN << __LINE__ << _CLM_END << ",\n" ; \
        std::cout << "      " _CLM_CYAN << __func__ << "()" _CLM_END; \
        std::cout << ", value of " _CLM_B_BLUE #value _CLM_END "\n"; \
        std::cout << "    expected: " _CLM_B_GREEN << "true" << _CLM_END "\n"; \
        std::cout << "      actual: " _CLM_B_RED << "false" << _CLM_END "\n"; \
        return -1; \
    } \

#define CHK_NOT(value) \
    if (value) { \
        std::cout << "\n    " _CLM_GREEN << __FILE__ << _CLM_END "::"; \
        std::cout << _CLM_GREEN << __LINE__ << _CLM_END << ",\n" ; \
        std::cout << "      " _CLM_CYAN << __func__ << "()" _CLM_END; \
        std::cout << ", value of " _CLM_B_BLUE #value _CLM_END "\n"; \
        std::cout << "    expected: " _CLM_B_GREEN << "false" << _CLM_END "\n"; \
        std::cout << "      actual: " _CLM_B_RED << "true" << _CLM_END "\n"; \
        return -1; \
    } \


class TestArgsBase {
    virtual ~TestArgsBase() { }
};

class TestSuite {
public:
    TestSuite();
    ~TestSuite();

    static std::string getTestFileName(std::string prefix);
    static void clearTestFile(std::string prefix);

    void doTest(std::string test_name, test_func *func, TestArgsBase *args = nullptr);

private:
    size_t cntPass;
    size_t cntFail;
};


