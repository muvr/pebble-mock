#include "dict.h"
using namespace pebble::services;

dictionary_iterator::dictionary_iterator() {
}

dictionary_iterator::dictionary_iterator(const dictionary_iterator &that) {
}

DictionaryResult dictionary_iterator::write_data(const uint32_t key, const uint8_t *data, const uint16_t size) {
    return DICT_OK;
}

DictionaryResult dictionary_iterator::write_int8(const uint32_t key, const int8_t value) {
    return DICT_OK;
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
    return di->write_int8(key, value);
}

uint32_t dict_write_end(DictionaryIterator *iter) {
    return 0;
}

}
#pragma clang diagnostic pop
