#pragma once
#include <vector>

extern "C" {
#include <pebble.h>
}

namespace pebble {
namespace mock {

    /**
     * AccelService controls the Pebble AS mocks. Its ``<<`` operators
     * provide mechanism to push the accelerometer data.
     *
     * Any callbacks will be triggered after pushing the data in.
     */
    class AccelService {
    private:
        std::vector<AccelRawData> raw_data;
        int samples_per_update;
        AccelRawDataHandler raw_data_handler;

        void trigger_raw();
    public:
        AccelService& operator<<(const AccelRawData data);
        AccelService& operator<<(const std::vector<AccelRawData> &data);

        void accel_raw_data_service_subscribe(uint32_t samples_per_update, AccelRawDataHandler handler);
    };

}
}
