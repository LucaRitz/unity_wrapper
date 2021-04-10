#include "parallel_task.hpp"

app::InternalCountEvent::InternalCountEvent(int counter) : _counter(counter) {
}

app::ParallelTask::ParallelTask(Listener& listener) :
    _exitSignal(),
    _worker(std::thread(&ParallelTask::work, _exitSignal.get_future(), std::ref(listener))) {
}

app::ParallelTask::~ParallelTask() {
    if (_worker.joinable()) {
        _exitSignal.set_value();
        _worker.join();
    }
}

void app::ParallelTask::work(std::future<void> exitSignal, Listener& callback) {
    int counter = 0;
    while (exitSignal.wait_for(std::chrono::seconds(1)) == std::future_status::timeout) {
        callback.onCountChanged(InternalCountEvent{counter++});
    }
}