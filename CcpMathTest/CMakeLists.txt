add_executable(CcpMathTest
    CcpFloat.h
    Color.cpp
    Float16.cpp
    Matrix.cpp
    Plane.cpp
    Quaternion.cpp
    Vector2.cpp
    Vector3.cpp
    Vector4.cpp
)
target_link_libraries(CcpMathTest PRIVATE CcpMath GTest::GTest GTest::Main)
if(APPLE)
    target_link_libraries(CcpMathTest PRIVATE "-framework CoreFoundation")
endif()

set_target_properties(CcpMathTest PROPERTIES FOLDER "Tests")