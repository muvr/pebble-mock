#pragma once
#include "accel_service.h"
#include "app_messages.h"

namespace pebble {

    struct instances {
        static services::accel_service accel_service;
        static services::app_messages app_messages;
    };

}
