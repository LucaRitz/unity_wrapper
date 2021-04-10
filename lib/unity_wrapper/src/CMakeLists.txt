target_sources(${PROJECT_NAME}
        PUBLIC
        ../include/unity_wrapper/unity_wrapper.hpp
        ../include/unity_wrapper/type.hpp

        PRIVATE
        event_queue.hpp
        unity_wrapper.cpp
        parallel_task.hpp
        parallel_task.cpp
        type.cpp)
