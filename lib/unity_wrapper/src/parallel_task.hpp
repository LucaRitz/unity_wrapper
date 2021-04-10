#pragma once

#include <thread>
#include <unity_wrapper/type.hpp>
#include <mutex>
#include <future>

namespace app {
    struct InternalCountEvent {
        explicit InternalCountEvent(int counter);

        int _counter;
    };

    class Listener {
    public:
        virtual ~Listener() = default;
        virtual void onCountChanged(const InternalCountEvent& event) = 0;
    };

    class ParallelTask {
    public:
        explicit ParallelTask(Listener& listener);
        ~ParallelTask();

    private:
        std::promise<void> _exitSignal;
        std::thread _worker;

        static void work(std::future<void> exitSignal, Listener& listener);
    };
}

