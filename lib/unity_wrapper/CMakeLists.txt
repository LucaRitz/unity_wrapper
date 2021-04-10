project(unity_wrapper)

add_library(${PROJECT_NAME} SHARED)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${OpenCV_INCLUDE_DIRS}
        )

add_subdirectory(src)

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD

        # Copy dependencies to unity folder
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:unity_wrapper> ${UNITY_PLUGINS}/
        )

target_link_libraries(${PROJECT_NAME})