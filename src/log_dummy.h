#pragma once

#include "log_base.h"
#include "fileops_base.h"

class LogDummy : public LogBase {
public:
    LogDummy();
    ~LogDummy();

    HLStatus open(const std::string filename, const LogOptions& options);
    HLStatus close();
    HLStatus get();
    HLStatus set();
    HLStatus getAll();
    HLStatus sync();
    HLStatus destroy();

private:
    FileOpsBase *file;
};

