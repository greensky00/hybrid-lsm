
#include "log_dummy.h"
#include "fileops_posix.h"

LogDummy::LogDummy() :
    file(nullptr)
{ }

LogDummy::~LogDummy()
{
    if (file) {
        delete file;
    }
}

HLStatus LogDummy::open(const std::string filename, const LogOptions& options)
{
    if (file) {
        return HLStatus(HLS_FAIL);
    }

    HLStatus s;
    file = new FileOpsPosix();
    s = file->open(filename.c_str(), O_CREAT | O_RDWR);
    if (!s.ok()) {
        delete file;
        file = nullptr;
        return s;
    }

    return HLStatus();
}

HLStatus LogDummy::close()
{
    if (!file) {
        return HLStatus(HLS_FAIL);
    }

    HLStatus s;
    s = file->close();
    if (!s.ok()) {
        return s;
    }

    return HLStatus();
}

HLStatus LogDummy::get()
{
    return HLStatus();
}
HLStatus LogDummy::set()
{
    return HLStatus();
}

HLStatus LogDummy::getAll()
{
    return HLStatus();
}

HLStatus LogDummy::sync()
{
    return HLStatus();
}

HLStatus LogDummy::destroy()
{
    return HLStatus();
}

