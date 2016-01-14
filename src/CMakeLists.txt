add_library(sm_utils STATIC OdeSystem.cpp OdeSolver.cpp)
add_executable(euler_test EulerTest.cpp)
target_link_libraries(euler_test sm_utils)
