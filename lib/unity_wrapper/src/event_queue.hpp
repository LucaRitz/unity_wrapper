#pragma once

#include <queue>
#include <mutex>

namespace unity {
    template <class Event, class Callback>
    class EventQueue {
    public:
        void callback(Callback callback) {
            _guard.lock();
            this->_callback = callback;
            _guard.unlock();
        }

        void push(Event event) {
            _guard.lock();
            _queue.push(event);
            _guard.unlock();
        }

        void process() {
            _guard.lock();

            if (!_queue.empty() && _callback != nullptr) {
                auto oldest = _queue.front();
                _callback(oldest);
                _queue.pop();
            }

            _guard.unlock();
        }

    private:
        std::mutex _guard;
        std::queue<Event> _queue;

        Callback _callback;
    };
}