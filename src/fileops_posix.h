#pragma once

#include "fileops_base.h"

class FileOpsPosix : public FileOpsBase {
public:
    FileOpsPosix();
    ~FileOpsPosix();

    HLStatus open(const char *pathname, int flags);
    HLStatus close();
    HLStatus pread(void *buf, size_t count, cs_off_t offset);
    HLStatus pwrite(const void *buf, size_t count, cs_off_t offset);
    cs_off_t eof();
    HLStatus fsync();

private:
    int fd;
};

