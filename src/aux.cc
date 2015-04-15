#include <iostream>

extern "C" {

void psleep(int millis) {
    // noop
}

size_t heap_bytes_used(void) {
    return 20000;
}

void app_log(uint8_t log_level, const char *src_filename, int src_line_number, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buffer[256];
    std::vsprintf(buffer, fmt, args);
    va_end(args);

    std::cout << std::string(buffer) << std::flush;
}

}