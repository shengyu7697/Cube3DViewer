add_executable(test_client
    client.cpp
    SocketPoseClient.cpp
)

target_include_directories(test_client PUBLIC tinytcp)
target_link_libraries(test_client pthread tinytcp)