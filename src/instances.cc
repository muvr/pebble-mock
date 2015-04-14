#include "instances.h"

pebble::services::accel_service pebble::instances::accel_service;
pebble::services::app_messages pebble::instances::app_messages;

extern "C" {
#include <pebble.h>

void psleep(int millis) {
    // noop
}

size_t heap_bytes_used(void) {
    return 20000;
}

void app_log(uint8_t log_level, const char *src_filename, int src_line_number, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    va_end(args);
}

}
