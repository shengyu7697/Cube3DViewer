find_package(glfw3 REQUIRED)

set(FILES
    main.cpp
    GLUtil.cpp
    FakePoseGenerator.cpp
    SocketPoseService.cpp
    ../../thirdparty/TinyTcp/src/TinyTcp/TinyTcpServer.cpp
    ../../thirdparty/TinyTcp/src/TinyTcp/SocketUtil.cpp
)

if(USE_PROTOBUF)
	find_package(Protobuf REQUIRED)
	PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS pose.proto)
	list(APPEND FILES ${PROTO_SRCS})
endif()

add_executable(cube3dviewer	${FILES})

if(USE_PROTOBUF)
target_include_directories(cube3dviewer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/TinyTcp/src/TinyTcp" ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(cube3dviewer GL GLEW glfw ${PROTOBUF_LIBRARIES})
else()
target_include_directories(cube3dviewer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/TinyTcp/src/TinyTcp")
target_link_libraries(cube3dviewer GL GLEW glfw)
endif()