add_executable(Exercise_1 "Exercise_1.cpp" "Exercise_1.h")
target_compile_features(Exercise_1 PRIVATE cxx_std_20)
target_link_libraries(Exercise_1 glfw3 opengl32)
