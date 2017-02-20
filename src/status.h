#pragma once

typedef enum {
    HLS_SUCCESS = 0,
    HLS_FAIL = -32768
} HLStatusValue;

class HLStatus {
public:
    HLStatus() : status(HLS_SUCCESS) { }
    HLStatus(HLStatusValue _v) : status(_v) { }
    ~HLStatus() { }

    explicit operator bool() {
        return ok();
    }

    bool ok() {
        return status == HLS_SUCCESS;
    }

    void set(HLStatusValue _status) {
        status = _status;
    }

private:
    HLStatusValue status;
};

