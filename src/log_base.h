#pragma once

#include "status.h"
#pragma once

#include <string>

#include "status.h"
#include "keyvalue.h"

struct LogOptions {
    LogOptions() { }
    ~LogOptions() { }
};

class LogBase {
public:
    virtual ~LogBase() { }

    virtual HLStatus open(const std::string filename, const LogOptions& options) = 0;
    virtual HLStatus close() = 0;
    virtual HLStatus get() = 0;
    virtual HLStatus set() = 0;
    virtual HLStatus getAll() = 0;
    virtual HLStatus sync() = 0;
    virtual HLStatus destroy() = 0;
};

