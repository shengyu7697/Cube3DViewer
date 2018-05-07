find_package(glfw3 REQUIRED)

set(FILES
    main.cpp
    GLUtil.h
    GLUtil.cpp
)

if(USE_NETWORK_SOCKET)
    list(APPEND FILES SocketPoseService.h SocketPoseService.cpp)
    list(APPEND INCLUDE_DIRS tinytcp)
    list(APPEND LIBRARIES tinytcp)
else()
    list(APPEND FILES FakePoseGenerator.h FakePoseGenerator.cpp)
endif()

if(USE_PROTOBUF)
    find_package(Protobuf REQUIRED)
    PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS pose.proto)
    list(APPEND FILES ${PROTO_SRCS})
    list(APPEND INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIRS})
    list(APPEND LIBRARIES ${PROTOBUF_LIBRARIES})
endif()

if (WIN32)
    list(APPEND OPENGL_LIBRARIES opengl32)
else() # Linux
    list(APPEND OPENGL_LIBRARIES GL GLEW)
    list(APPEND LIBRARIES pthread)
endif()

add_executable(cube3dviewer ${FILES})

target_include_directories(cube3dviewer PUBLIC ${INCLUDE_DIRS} "./deps")
target_link_libraries(cube3dviewer glfw ${LIBRARIES} ${OPENGL_LIBRARIES})
