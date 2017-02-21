#pragma once

#include <string.h>
#include <string>
#include <iostream>

struct SizedBinary {
    SizedBinary() : size(0), data(nullptr) { }

    SizedBinary(size_t _size, void* _data) : size(_size), data(_data) { }

    SizedBinary(const SizedBinary& src) {
        size = src.size;
        data = src.data;
    }

    SizedBinary(const std::string& str) {
        set(str.size(), (void*)str.c_str());
    }

    bool operator==(const SizedBinary &other) const {
        if (size != other.size) {
            return false;
        }
        if (size) {
            return memcmp(data, other.data, size) == 0;
        }
        return true;
    }

    bool operator!=(const SizedBinary &other) const {
        return !operator==(other);
    }

    friend std::ostream &operator<<(std::ostream &output, const SizedBinary &sb) {
        char addr[16];
        sprintf(addr, "%p", sb.data);
        output << sb.size << ", " << addr;
        return output;
    }

    void set(const std::string& str) {
        set(str.size(), (void*)str.c_str());
    }

    void set(size_t _size, void *_data) {
        size = _size;
        data = _data;
    }

    std::string toString() {
        return std::string((const char*)data, size);
    }

    void clear() {
        size = 0;
        data = nullptr;
    }

    size_t size;
    void *data;
};

struct KeyValue {
    KeyValue() { }

    KeyValue(size_t _key_size, void *_key_data,
             size_t _value_size, void *_value_data) {
        key.set(_key_size, _key_data);
        value.set(_value_size, _value_data);
    }

    KeyValue(const SizedBinary& _key, const SizedBinary& _value) :
        key(_key), value(_value) { }

    KeyValue(const KeyValue& src) {
        key = src.key;
        value = src.value;
    }

    KeyValue(const std::string& _key, const std::string& _value) {
        key.set(_key.size(), (void*)_key.c_str());
        value.set(_value.size(), (void*)_value.c_str());
    }

    void set(const std::string& _key, const std::string& _value) {
        key.set(_key.size(), (void*)_key.c_str());
        value.set(_value.size(), (void*)_value.c_str());
    }

    void set(const SizedBinary& _key, const SizedBinary& _value) {
        key = _key;
        value = _value;
    }

    void clear() {
        key.clear();
        value.clear();
    }

    SizedBinary key;
    SizedBinary value;
};


