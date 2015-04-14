#pragma once
#include <stdint.h>
extern "C" {
#include <pebble.h>
}

namespace pebble {
namespace services {

    class dictionary_iterator {
    public:
        dictionary_iterator();
        dictionary_iterator(const dictionary_iterator &that);

        DictionaryResult write_data(const uint32_t key, const uint8_t *data, const uint16_t size);
        DictionaryResult write_int8(const uint32_t key, const int8_t value);
    };


}
}