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
    	/** collected raw_data, always reduced to samples_per_update */
        std::vector<AccelRawData> raw_data;
        /** the samples per update passed at subscribe-time */
        int samples_per_update;
        /** the handler passed at subscribe-time */
        AccelRawDataHandler raw_data_handler;

        /** processes the accumulated data */
        void trigger_raw();
    public:
    	/**
    	 * Simulate measurement of AccelRawData as if it came from the 
    	 * Pebble hardware
    	 */
        AccelService& operator<<(const AccelRawData data);

        /**
         * Simulate measurement of multiple AccelRawData as if they came from the
         * Pebble hardware
         */
        AccelService& operator<<(const std::vector<AccelRawData> &data);

        /**
         * Mirror of the Pebble Accelerometer API.
         * Viz http://developer.getpebble.com/2/api-reference/group___accelerometer_service.html and
         * http://developer.getpebble.com/2/guides/accelerometer.html
         */
        void accel_data_service_subscribe(uint32_t samples_per_update, AccelDataHandler handler);
        void accel_data_service_unsubscribe();
        void accel_raw_data_service_subscribe(uint32_t samples_per_update, AccelRawDataHandler handler);
        int accel_service_peek(AccelData* data);
        int accel_service_set_samples_per_update(uint32_t num_samples);
        int accel_service_set_sampling_rate(AccelSamplingRate rate);
        void accel_tap_service_subscribe(AccelTapHandler handler);
        void accel_tap_service_unsubscribe();
    };

}
}
