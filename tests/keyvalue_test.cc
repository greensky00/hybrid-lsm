#include <stdio.h>
#include <string.h>

#include "test_common.h"
#include "keyvalue.h"

int sb_empty_test() {
    SizedBinary sb;

    CHK_EQ(0, sb.size);
    CHK_NULL(sb.data);

    return 0;
}

int sb_normal_test() {
    SizedBinary sb;
    char str[16];
    char str2[8];

    sb = SizedBinary(16, str);
    CHK_EQ(16, sb.size);
    CHK_NONNULL(sb.data);

    sb.set(8, str2);
    CHK_EQ(8, sb.size);
    CHK_EQ((void*)str2, sb.data);

    return 0;
}

int sb_clone_test() {
    SizedBinary sb;
    SizedBinary sb_clone(sb);

    CHK_EQ(sb.size, sb_clone.size);
    CHK_EQ(sb.data, sb_clone.data);

    return 0;
}

int sb_string_test() {
    SizedBinary sb;

    std::string str1 = "test_string";
    std::string str2 = "hello world";

    sb = SizedBinary(str1);
    CHK_EQ(str1.size(), sb.size);
    CHK_OK(!memcmp(str1.c_str(), sb.data, sb.size));

    sb.set(str2);
    CHK_EQ(str2.size(), sb.size);
    CHK_OK(!memcmp(str2.c_str(), sb.data, sb.size));

    std::string str3 = sb.toString();
    CHK_EQ(str2, str3);

    return 0;
}

int sb_equal_test() {
    std::string str1 = "test_string";
    std::string str2 = "test_string";
    std::string str3 = "!!test_string";
    SizedBinary sb1(str1), sb2(str2), sb3(str3);

    CHK_OK((void*)sb1.data != (void*)sb2.data);
    CHK_OK((void*)sb2.data != (void*)sb3.data);
    CHK_OK((void*)sb3.data != (void*)sb1.data);

    CHK_OK(sb1 == sb2);
    CHK_OK(sb1 != sb3);
    CHK_OK(sb2 != sb3);

    return 0;
}

int sb_equal_empty_test() {
    std::string str3 = "!!test_string";
    SizedBinary sb1, sb2, sb3(str3);

    CHK_OK((void*)sb2.data != (void*)sb3.data);
    CHK_OK((void*)sb3.data != (void*)sb1.data);

    CHK_OK(sb1 == sb2);
    CHK_OK(sb1 != sb3);
    CHK_OK(sb2 != sb3);

    return 0;
}

int sb_clear_test()
{
    SizedBinary sb;

    std::string str = "test_string";
    sb = SizedBinary(str);
    CHK_EQ(str.size(), sb.size);
    CHK_OK(!memcmp(str.c_str(), sb.data, sb.size));

    sb.clear();
    CHK_EQ(0, sb.size);
    CHK_NULL(sb.data);

    return 0;
}

int kv_empty_test()
{
    KeyValue kv;
    SizedBinary sb_empty;

    CHK_EQ(sb_empty, kv.key);
    CHK_EQ(sb_empty, kv.value);

    return 0;
}

int main() {
    TestSuite test;

    test.doTest("SizedBinary empty test", sb_empty_test);
    test.doTest("SizedBinary normal test", sb_normal_test);
    test.doTest("SizedBinary clone test", sb_clone_test);
    test.doTest("SizedBinary string test", sb_string_test);
    test.doTest("SizedBinary functional test", sb_clear_test);
    test.doTest("SizedBinary equal test", sb_equal_test);
    test.doTest("SizedBinary equal empty test", sb_equal_empty_test);

    test.doTest("KeyValue empty test", kv_empty_test);

    return 0;
}
