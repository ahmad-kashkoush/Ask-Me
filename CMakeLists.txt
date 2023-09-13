cmake_minimum_required(VERSION 3.24)
project(Ask_Me)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ask_Me
        main.cpp
        sourchCodeFiles/AskMe.cpp
        sourchCodeFiles/QuestionsManager.cpp
        sourchCodeFiles/UsersManager.cpp
        sourchCodeFiles/UtilityFunctions.cpp
        )
