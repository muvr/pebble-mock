#pragma once
#include "accel_service.h"
#include "app_messages.h"

namespace pebble {

    struct mocks {
    private:
        static std::shared_ptr<services::accel_service> m_accel_service;
        static std::shared_ptr<services::app_messages> m_app_messages;
    public:
        static std::shared_ptr<services::accel_service> accel_service();
        static std::shared_ptr<services::app_messages> app_messages();

        void reset();
    };

}
