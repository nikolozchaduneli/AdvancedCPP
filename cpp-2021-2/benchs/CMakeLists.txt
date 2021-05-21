find_package(benchmark REQUIRED)

add_executable(benchmark benchs.cpp)
target_link_libraries(benchmark PUBLIC benchmark::benchmark cppa)

add_custom_target(bench COMMAND benchmark DEPENDS benchmark)