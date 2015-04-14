#pragma once
#include <stdint.h>
#include <map>
#include <vector>
extern "C" {
#include <pebble.h>
}

namespace pebble {
namespace services {

    class dictionary_iterator {
    private:
        std::map<uint32_t, std::vector<uint8_t>> m_data;
        std::map<uint32_t, int64_t> m_ints;
    public:
        dictionary_iterator();
        dictionary_iterator(const dictionary_iterator &that);

        template<typename A> A &get(const uint32_t key);

        DictionaryResult write_data(const uint32_t key, const uint8_t *data, const uint16_t size);
        DictionaryResult write_int(const uint32_t key, const int64_t value);
    };


}
}