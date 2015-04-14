#include <vector>
#include "dict.h"
using namespace pebble::services;

dictionary_iterator::dictionary_iterator() {
}

dictionary_iterator::dictionary_iterator(const dictionary_iterator &that) {
    m_ints = that.m_ints;
    m_data = that.m_data;
}

DictionaryResult dictionary_iterator::write_data(const uint32_t key, const uint8_t *data, const uint16_t size) {
    std::vector<uint8_t> r;
    for (uint16_t i = 0; i < size; ++i) r.push_back(data[i]);
    m_data[key] = r;
    return DICT_OK;
}

DictionaryResult dictionary_iterator::write_int(const uint32_t key, const int64_t value) {
    m_ints[key] = value;
    return DICT_OK;
}

template<> std::vector<uint8_t> &dictionary_iterator::get(const uint32_t key) {
    return m_data[key];
}

template<> int64_t &dictionary_iterator::get(const uint32_t key) {
    return m_ints[key];
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
extern "C" {

DictionaryResult dict_write_data(DictionaryIterator *iter, const uint32_t key, const uint8_t * const data, const uint16_t size) {
    dictionary_iterator *di = reinterpret_cast<dictionary_iterator *>(iter);
    return di->write_data(key, data, size);
}

DictionaryResult dict_write_int8(DictionaryIterator *iter, const uint32_t key, const int8_t value) {
    dictionary_iterator *di = reinterpret_cast<dictionary_iterator *>(iter);
    return di->write_int(key, value);
}

uint32_t dict_write_end(DictionaryIterator *iter) {
    return 0;
}

}
#pragma clang diagnostic pop
