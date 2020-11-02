cmake_minimum_required(VERSION 3.0)
project(BeeHive)

set(BEEHIVE_SOURCE_FILES
        src/bee_main.cpp
        src/bees/bee.cpp
        src/bees/bee.h
        src/bees/drone.cpp
        src/bees/queen.cpp
        src/bees/resource.cpp
        src/bees/worker.cpp
        src/bees/worker.h
        src/util/logger.cpp
        src/util/my_thread.cpp
        src/util/random.cpp
        src/world/beehive.cpp
        src/world/flower_field.cpp
        src/world/queens_chamber.cpp)

add_executable(BeeHive ${BEEHIVE_SOURCE_FILES})