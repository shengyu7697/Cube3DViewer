find_package(glfw3)

add_executable(cube3dviewer
    main.cpp
    GLUtil.cpp
    FakePoseGenerator.cpp
)

#target_include_directories(cube3dviewer PUBLIC )
target_link_libraries(cube3dviewer GL GLEW glfw)