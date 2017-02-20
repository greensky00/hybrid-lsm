#include <stdio.h>
#include <string.h>

#include "test_common.h"
#include "keyvalue.h"

int sized_binary_test()
{
    SizedBinary sb;
    CHK_EQ(0, sb.size);
    CHK_NULL(sb.data);

    char str[16];
    sb = SizedBinary(16, str);
    CHK_EQ(16, sb.size);
    CHK_NONNULL(sb.data);

    SizedBinary sb_clone(sb);
    CHK_EQ(sb.size, sb_clone.size);
    CHK_EQ(sb.data, sb_clone.data);

    char str2[8];
    sb.set(8, str2);
    CHK_EQ(8, sb.size);
    CHK_EQ((void*)str2, sb.data);

    std::string str3 = "test_string";
    sb = SizedBinary(str3);
    CHK_EQ(str3.size(), sb.size);
    CHK_OK(!memcmp(str3.c_str(), sb.data, sb.size));

    std::string str4 = "hello world";
    sb.set(str4);
    CHK_EQ(str4.size(), sb.size);
    CHK_OK(!memcmp(str4.c_str(), sb.data, sb.size));

    std::string str5 = sb.toString();
    CHK_EQ(str4, str5);

    sb.clear();
    CHK_EQ(0, sb.size);
    CHK_NULL(sb.data);

    return 0;
}

int main() {
    TestSuite test;

    test.doTest("SizedBinary functional test", sized_binary_test);

    return 0;
}
