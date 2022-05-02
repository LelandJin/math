project(CcpMath VERSION 1.0.0)

add_library(CcpMath STATIC)
target_sources(CcpMath PRIVATE
    AxisAlignedBox.cpp
    Color.cpp
    Float16.cpp
    Matrix.cpp
    Plane.cpp
    Quaternion.cpp
    Sphere.cpp
    Vector2.cpp
    Vector3.cpp
    Vector4.cpp
    include/AxisAlignedBox.h
    include/AxisAlignedBox_inline.h
    include/CcpMath.h
    include/Color.h
    include/Color_inline.h
    include/Float16.h
    include/Float16_inline.h
    include/Matrix.h
    include/Matrix_inline.h
    include/Plane.h
    include/Plane_inline.h
    include/Quaternion.h
    include/Quaternion_inline.h
    include/Ray.h
    include/Ray_inline.h
    include/Requirements.h
    include/Sphere.h
    include/Sphere_inline.h
    include/Vector2.h
    include/Vector2_inline.h
    include/Vector3.h
    include/Vector3_inline.h
    include/Vector4.h
    include/Vector4_inline.h
)

set_target_properties(CcpMath PROPERTIES POSITION_INDEPENDENT_CODE ON EXPORT_NAME CcpMath)
target_include_directories(CcpMath
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(CcpMath PUBLIC DirectXMath)

target_compile_options(CcpMath PRIVATE "${MATH_OPTIMIZE_FLAG}")