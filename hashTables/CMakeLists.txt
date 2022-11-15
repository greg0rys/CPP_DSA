cmake_minimum_required(VERSION 3.23)
project(hashTables)

set(CMAKE_CXX_STANDARD 14)



message(STATUS "Starting build of hashTables 🧑‍💻" )

add_executable(project_two
        driver.cpp
        driver.h
        table.h
        table.cpp
        person.h
        person.cpp
        )

message(STATUS "hashTables build completed.❤️")

