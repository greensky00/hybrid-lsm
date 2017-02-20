#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "fileops_posix.h"


FileOpsPosix::FileOpsPosix() : fd(-1)
{
}

FileOpsPosix::~FileOpsPosix()
{
    if (fd != -1) close();
}

HLStatus FileOpsPosix::open(const char *pathname, int flags)
{
    int r = ::open(pathname, flags, 0666);
    if (r <= 0) return HLStatus(HLS_FAIL);

    fd = r;
    return HLStatus();
}

HLStatus FileOpsPosix::close()
{
    if (fd <= 0) return HLStatus(HLS_FAIL);

    int r = ::close(fd);
    if (r < 0) return HLStatus(HLS_FAIL);

    fd = -1;
    return HLStatus();
}

HLStatus FileOpsPosix::pread(void *buf, size_t count, cs_off_t offset)
{
    if (fd <= 0) return HLStatus(HLS_FAIL);
    if (!buf) return HLStatus(HLS_FAIL);

    ssize_t r = ::pread(fd, buf, count, offset);
    if (r != count) return HLStatus(HLS_FAIL);

    return HLStatus();
}

HLStatus FileOpsPosix::pwrite(const void *buf, size_t count, cs_off_t offset)
{
    if (fd <= 0) return HLStatus(HLS_FAIL);

    ssize_t r = ::pwrite(fd, buf, count, offset);
    if (r != count) return HLStatus(HLS_FAIL);

    return HLStatus();
}

cs_off_t FileOpsPosix::eof()
{
    if (fd <= 0) return -1;

    return ::lseek(fd, 0, SEEK_END);
}

HLStatus FileOpsPosix::fsync()
{
    if (fd <= 0) return HLStatus(HLS_FAIL);

    int r = ::fsync(fd);
    if (r < 0) return HLStatus(HLS_FAIL);

    return HLStatus();
}

