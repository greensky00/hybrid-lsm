#include <stdio.h>
#include <string.h>

#include "fileops_posix.h"
#include "test_common.h"

int read_write_without_open_test()
{
    const std::string prefix = "file_posix_test";
    TestSuite::clearTestFile(prefix);

    HLStatus s;
    FileOpsBase *t_file = new FileOpsPosix();
    char buf[256];

    s = t_file->pread(buf, 256, 0);
    CHK_NOT(s);

    memset(buf, 'x', 256);
    s = t_file->pwrite(buf, 256, 0);
    CHK_NOT(s);

    s = t_file->close();
    CHK_NOT(s);

    delete t_file;
    TestSuite::clearTestFile(prefix);

    return 0;
}

int normal_read_write_test()
{
    const std::string prefix = "file_posix_test";
    TestSuite::clearTestFile(prefix);

    HLStatus s;
    std::string filename = TestSuite::getTestFileName(prefix);
    FileOpsBase *t_file = new FileOpsPosix();
    char buf[256];

    s = t_file->open(filename.c_str(), O_CREAT | O_RDWR);
    CHK_OK(s);

    memset(buf, 'x', 256);
    s = t_file->pwrite(buf, 256, 0);
    CHK_OK(s);

    memset(buf, 'a', 256);
    s = t_file->pread(buf, 256, 0);
    CHK_OK(s);

    char buf_chk[256];
    memset(buf_chk, 'x', 256);
    CHK_EQ(0, memcmp(buf_chk, buf, 256));

    s = t_file->close();
    CHK_OK(s);

    delete t_file;
    TestSuite::clearTestFile(prefix);

    return 0;
}

int eof_test()
{
    const std::string prefix = "file_posix_test";
    TestSuite::clearTestFile(prefix);

    HLStatus s;
    std::string filename = TestSuite::getTestFileName(prefix);
    FileOpsBase *t_file = new FileOpsPosix();
    char buf[256];

    s = t_file->open(filename.c_str(), O_CREAT | O_RDWR);
    CHK_OK(s);

    memset(buf, 'x', 256);
    s = t_file->pwrite(buf, 256, 0);
    CHK_OK(s);

    cs_off_t offset = t_file->eof();
    CHK_EQ(256, offset);

    s = t_file->close();
    CHK_OK(s);

    delete t_file;
    TestSuite::clearTestFile(prefix);

    return 0;
}

int fsync_test()
{
    const std::string prefix = "file_posix_test";
    TestSuite::clearTestFile(prefix);

    HLStatus s;
    std::string filename = TestSuite::getTestFileName(prefix);
    FileOpsBase *t_file = new FileOpsPosix();
    char buf[256];

    s = t_file->open(filename.c_str(), O_CREAT | O_RDWR);
    CHK_OK(s);

    memset(buf, 'x', 256);
    s = t_file->pwrite(buf, 256, 0);
    CHK_OK(s);

    s = t_file->fsync();
    CHK_OK(s);

    s = t_file->close();
    CHK_OK(s);

    delete t_file;
    TestSuite::clearTestFile(prefix);

    return 0;
}

int main() {
    TestSuite test;

    test.doTest("read write without open test", read_write_without_open_test);
    test.doTest("normal read write test", normal_read_write_test);
    test.doTest("file EOF test", eof_test);
    test.doTest("file fsync test", fsync_test);

    return 0;
}
