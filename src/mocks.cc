#include "mocks.h"

using namespace pebble;

std::shared_ptr<services::accel_service> mocks::m_accel_service = std::shared_ptr<services::accel_service>(new services::accel_service());;
std::shared_ptr<services::app_messages> mocks::m_app_messages = std::shared_ptr<services::app_messages>(new services::app_messages());


std::shared_ptr<services::app_messages> mocks::app_messages() {
    return m_app_messages;
}

std::shared_ptr<services::accel_service> mocks::accel_service() {
    return m_accel_service;
}

void mocks::reset() {
    m_accel_service = std::shared_ptr<services::accel_service>(new services::accel_service());
    m_app_messages = std::shared_ptr<services::app_messages>(new services::app_messages());
}
