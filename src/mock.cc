#include "mock.h"

using namespace pebble::mock;

extern "C" {

void app_log(uint8_t log_level, const char *src_filename, int src_line_number, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    va_end(args);
}

}
