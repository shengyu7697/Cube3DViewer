find_package(glfw3)

add_executable(cube3dviewer
    main.cpp
    GLUtil.cpp
    FakePoseGenerator.cpp
    SocketPoseService.cpp
    ../../thirdparty/TinyTcp/src/TinyTcp/TinyTcpServer.cpp
    ../../thirdparty/TinyTcp/src/TinyTcp/SocketUtil.cpp
)

target_include_directories(cube3dviewer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/TinyTcp/src/TinyTcp")
target_link_libraries(cube3dviewer GL GLEW glfw)