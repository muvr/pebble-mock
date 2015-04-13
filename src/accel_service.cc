#include "accel_service.h"
#include "mock.h"

using namespace pebble::mock;

accel_service &accel_service::operator<<(const AccelRawData data) {
    this->raw_data.push_back(data);
    trigger_raw();
    return *this;
}

accel_service &accel_service::operator<<(const std::vector <AccelRawData> &data) {
    this->raw_data.insert(this->raw_data.end(), data.begin(), data.end());
    trigger_raw();
    return *this;
}

void accel_service::trigger_raw() {
    bool sent = false;
    for (int i = 0; i < this->raw_data.size() / this->samples_per_update; ++i) {
        std::vector<AccelRawData> update(this->raw_data.begin() + i * this->samples_per_update,
                this->raw_data.begin() + i * this->samples_per_update + this->samples_per_update);
        this->raw_data_handler(update.data(), (uint32_t) update.size(), 0);
        sent = true;
    }

    if (sent) this->raw_data.clear();
}

void accel_service::accel_raw_data_service_subscribe(uint32_t samples_per_update, AccelRawDataHandler handler) {
    if (samples_per_update < 1) throw std::runtime_error("");
    if (handler == nullptr) throw std::runtime_error("");

    this->raw_data_handler = handler;
    this->samples_per_update = samples_per_update;
}

void accel_service::accel_data_service_subscribe(uint32_t samples_per_update, AccelDataHandler handler) {

}

void accel_service::accel_data_service_unsubscribe() {

}

int accel_service::accel_service_peek(AccelData *data) {
    return 0;
}

int accel_service::accel_service_set_samples_per_update(uint32_t num_samples) {
    return 0;
}

int accel_service::accel_service_set_sampling_rate(AccelSamplingRate rate) {
    return 0;
}

void accel_service::accel_tap_service_subscribe(AccelTapHandler handler) {

}

void accel_service::accel_tap_service_unsubscribe() {

}

// Mirror API
extern "C" {

void accel_raw_data_service_subscribe(uint32_t samples_per_update, AccelRawDataHandler handler) {
    mock_accel_service.accel_raw_data_service_subscribe(samples_per_update, handler);
}

void accel_data_service_subscribe(uint32_t samples_per_update, AccelDataHandler handler) {
    mock_accel_service.accel_data_service_subscribe(samples_per_update, handler);
}

void accel_data_service_unsubscribe() {
    mock_accel_service.accel_data_service_unsubscribe();
}

int accel_service_peek(AccelData *data) {
    return mock_accel_service.accel_service_peek(data);
}

int accel_service_set_samples_per_update(uint32_t num_samples) {
    return mock_accel_service.accel_service_set_samples_per_update(num_samples);
}

int accel_service_set_sampling_rate(AccelSamplingRate rate) {
    return mock_accel_service.accel_service_set_sampling_rate(rate);
}

void accel_tap_service_subscribe(AccelTapHandler handler) {
    mock_accel_service.accel_tap_service_subscribe(handler);
}

void accel_tap_service_unsubscribe() {
    mock_accel_service.accel_tap_service_unsubscribe();
}

}
