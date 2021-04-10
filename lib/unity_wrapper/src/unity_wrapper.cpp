#include <unity_wrapper/unity_wrapper.hpp>
#include "event_queue.hpp"

///////////////////////////////////////////////////////
//// Event-Callbacks
///////////////////////////////////////////////////////
DebugCallback _debugger = nullptr;

///////////////////////////////////////////////////////
//// Event-Callbacks
///////////////////////////////////////////////////////
using CountEventQueue = unity::EventQueue<CountEvent, CountEventCallback>;
CountEventQueue _countEventQueue;

///////////////////////////////////////////////////////
//// Application specific stuff
///////////////////////////////////////////////////////
#include "parallel_task.hpp"

class CounterListener : public app::Listener {
public:
    explicit CounterListener(CountEventQueue& queue) : _queue(queue) {
    }

    void onCountChanged(const app::InternalCountEvent& event) override {
        _queue.push(CountEvent{event._counter});
    }

private:
    CountEventQueue& _queue;
};

app::ParallelTask* parallelTask = nullptr;
CounterListener counterListener {_countEventQueue};

///////////////////////////////////////////////////////
//// Implementation
///////////////////////////////////////////////////////

void onStart() {
    // Startup and initialize application specific stuff
    parallelTask = new app::ParallelTask{counterListener};
}

void onTearDown() {
    delete parallelTask;
    parallelTask = nullptr;
}

void processEvents() {
    _countEventQueue.process();
}

void onCountEvent(CountEventCallback callback) {
    _countEventQueue.callback(callback);
}

void debug(DebugCallback callback) {
    _debugger = callback;
    _debugger("Debugger initialized");
}
