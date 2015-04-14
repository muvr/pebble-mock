#include "app_messages.h"

using namespace pebble::services;

AppMessageResult app_messages::app_message_open(const uint32_t, const uint32_t) {
    return m_open_result;
}

void app_messages::app_message_deregister_callbacks() {
}

void* app_messages::app_message_get_context() {
    return m_context;
}

void* app_messages::app_message_set_context(void *context) {
    m_context = context;
    return m_context;
}

AppMessageInboxReceived app_messages::app_message_register_inbox_received(AppMessageInboxReceived received_callback) {
    m_received_callback = received_callback;
    return m_received_callback;
}

AppMessageInboxDropped app_messages::app_message_register_inbox_dropped(AppMessageInboxDropped dropped_callback) {
    m_dropped_callback = dropped_callback;
    return m_dropped_callback;
}

AppMessageOutboxSent app_messages::app_message_register_outbox_sent(AppMessageOutboxSent sent_callback) {
    m_sent_callback = sent_callback;
    return m_sent_callback;
}

AppMessageOutboxFailed app_messages::app_message_register_outbox_failed(AppMessageOutboxFailed failed_callback) {
    m_failed_callback = failed_callback;
    return m_failed_callback;
}

uint32_t app_messages::app_message_outbox_size_maximum() {
    return APP_MESSAGE_OUTBOX_SIZE_MINIMUM;
}

uint32_t app_messages::app_message_inbox_size_maximum() {
    return APP_MESSAGE_INBOX_SIZE_MINIMUM;
}

AppMessageResult app_messages::app_message_outbox_begin(DictionaryIterator **iterator) {
    if (m_current_dict) return APP_MSG_BUSY;

    m_current_dict = std::unique_ptr<dictionary_iterator>(new dictionary_iterator());
    *iterator = reinterpret_cast<DictionaryIterator *>(m_current_dict.get());

    return m_outbox_begin_result;
}

AppMessageResult app_messages::app_message_outbox_send() {
    if (!m_current_dict) return APP_MSG_CLOSED;

    m_last_dict = *m_current_dict;
    m_current_dict.release();

    return m_outbox_send_result;
}

dictionary_iterator app_messages::last_dict() const {
    return m_last_dict;
}

void app_messages::set_outbox_begin_result(AppMessageResult outbox_begin_result) {
    m_outbox_begin_result = outbox_begin_result;
}

void app_messages::set_open_result(AppMessageResult open_result) {
    m_open_result = open_result;
}

void app_messages::set_outbox_send_result(AppMessageResult outbox_send_result) {
    m_outbox_send_result = outbox_send_result;
}

// Mirror API
extern "C" {
#include "mocks.h"

AppMessageResult app_message_open(const uint32_t size_inbound, const uint32_t size_outbound) {
    return pebble::mocks::app_messages()->app_message_open(size_inbound, size_outbound);
}

void app_message_deregister_callbacks(void) {
    pebble::mocks::app_messages()->app_message_deregister_callbacks();
}

void *app_message_get_context(void) {
    return pebble::mocks::app_messages()->app_message_get_context();
}

void *app_message_set_context(void *context) {
    return pebble::mocks::app_messages()->app_message_set_context(context);
}

AppMessageInboxReceived app_message_register_inbox_received(AppMessageInboxReceived received_callback) {
    return pebble::mocks::app_messages()->app_message_register_inbox_received(received_callback);
}

AppMessageInboxDropped app_message_register_inbox_dropped(AppMessageInboxDropped dropped_callback) {
    return pebble::mocks::app_messages()->app_message_register_inbox_dropped(dropped_callback);
}

AppMessageOutboxSent app_message_register_outbox_sent(AppMessageOutboxSent sent_callback) {
    return pebble::mocks::app_messages()->app_message_register_outbox_sent(sent_callback);
}

AppMessageOutboxFailed app_message_register_outbox_failed(AppMessageOutboxFailed failed_callback) {
    return pebble::mocks::app_messages()->app_message_register_outbox_failed(failed_callback);
}

uint32_t app_message_inbox_size_maximum(void) {
    return pebble::mocks::app_messages()->app_message_inbox_size_maximum();
}

uint32_t app_message_outbox_size_maximum(void) {
    return pebble::mocks::app_messages()->app_message_outbox_size_maximum();
}

AppMessageResult app_message_outbox_begin(DictionaryIterator **iterator) {
    return pebble::mocks::app_messages()->app_message_outbox_begin(iterator);
}

AppMessageResult app_message_outbox_send(void) {
    return pebble::mocks::app_messages()->app_message_outbox_send();
}

}
