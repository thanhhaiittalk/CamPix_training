cmake_minimum_required(VERSION 3.10)
project(ChatRoomMediatorPattern)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/mediator
    ${PROJECT_SOURCE_DIR}/user
)

# Source files
set(SOURCES
    main.cpp
    mediator/ChatRoomMediator.cpp
    user/ConcreteUser.cpp
)

# Build the executable
add_executable(chatroom ${SOURCES})
