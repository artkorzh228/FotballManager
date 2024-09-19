cmake_minimum_required(VERSION 3.30)
project(Football)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Football
        Defender.cpp
        Defender.h
        enums.h
        Forward.cpp
        Forward.h
        functions.cpp
        functions.h
        Goalkeeper.cpp
        Goalkeeper.h
        main.cpp
        Midfielder.cpp
        Midfielder.h
        Player.cpp
        Player.h
        Tactic.cpp
        Tactic.h
        Team.cpp
        Team.h)
