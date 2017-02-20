#pragma once

#include <stdint.h>
#include <stddef.h>
#include <fcntl.h>

#include "status.h"

typedef int64_t cs_off_t;

class FileOpsBase {
public:
    virtual ~FileOpsBase() { }

    virtual HLStatus open(const char *pathname, int flags) = 0;
    virtual HLStatus close() = 0;
    virtual HLStatus pread(void *buf, size_t count, cs_off_t offset) = 0;
    virtual HLStatus pwrite(const void *buf, size_t count, cs_off_t offset) = 0;
    virtual cs_off_t eof() = 0;
    virtual HLStatus fsync() = 0;
};


