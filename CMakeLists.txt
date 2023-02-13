cmake_minimum_required(VERSION 3.16)

project(CcpMath VERSION 1.0.0)

if(NOT DEFINED ENV{CCP_EVE_PERFORCE_BRANCH_PATH})
    message(FATAL_ERROR "Missing required environment variable CCP_EVE_PERFORCE_BRANCH_PATH")
elseif(NOT IS_ABSOLUTE $ENV{CCP_EVE_PERFORCE_BRANCH_PATH})
    message(FATAL_ERROR "CCP_EVE_PERFORCE_BRANCH_PATH needs to be an absolute path")
elseif(NOT EXISTS $ENV{CCP_EVE_PERFORCE_BRANCH_PATH})
    message(FATAL_ERROR "CCP_EVE_PERFORCE_BRANCH_PATH is pointing at a non-existing location $ENV{CCP_EVE_PERFORCE_BRANCH_PATH}")
elseif(NOT IS_DIRECTORY $ENV{CCP_EVE_PERFORCE_BRANCH_PATH})
    message(FATAL_ERROR "CCP_EVE_PERFORCE_BRANCH_PATH needs to be a directory")
else()
    message(STATUS "Using CCP_EVE_PERFORCE_BRANCH_PATH located at $ENV{CCP_EVE_PERFORCE_BRANCH_PATH}")
endif()

file(TO_CMAKE_PATH "$ENV{CCP_EVE_PERFORCE_BRANCH_PATH}" BRANCH_ROOT_DIR)
list(INSERT CMAKE_MODULE_PATH 0 ${BRANCH_ROOT_DIR}/cmake)
include(CcpGlobalSettings)
include(CcpPackageConfigHelpers)

find_package(DirectXMath REQUIRED NO_CMAKE_PATH)

ccp_add_library(CcpMath STATIC)
target_sources(CcpMath PRIVATE
    src/AxisAlignedBox.cpp
    src/Color.cpp
    src/Float16.cpp
    src/Matrix.cpp
    src/Plane.cpp
    src/Quaternion.cpp
    src/Sphere.cpp
    src/Vector2.cpp
    src/Vector3.cpp
    src/Vector4.cpp
)

set(PUBLIC_HEADER_FILES
    include/AxisAlignedBox.h
    include/AxisAlignedBox_inline.h
    include/AxisAlignedEllipsoid.h
    include/AxisAlignedEllipsoid_inline.h
    include/NumConst.h
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
target_sources(CcpMath PRIVATE ${PUBLIC_HEADER_FILES})

set_target_properties(CcpMath PROPERTIES POSITION_INDEPENDENT_CODE ON EXPORT_NAME CcpMath)
target_include_directories(CcpMath
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(CcpMath PUBLIC DirectXMath)

target_compile_options(CcpMath PRIVATE "${MATH_OPTIMIZE_FLAG}")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    option(BUILD_TESTING "Build and run tests. Enabled by default." ON)
    include(CTest)
    if(BUILD_TESTING)
	    add_subdirectory(tests)
    endif()
endif()

# Provide an install target iff this is the top level project only
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Install rule to ensure that our runtime and linker files are in the expected, platform-specific folders
    install(
        TARGETS CcpMath
        EXPORT CcpMathTargets
        CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES}
        ARCHIVE DESTINATION lib/${CCP_PLATFORM}/${CCP_ARCHITECTURE}/${CCP_TOOLSET}/
        RUNTIME DESTINATION bin/${CCP_PLATFORM}/${CCP_ARCHITECTURE}/${CCP_TOOLSET}/
    )
    # Install rule for available public headers
    install(FILES ${PUBLIC_HEADER_FILES} DESTINATION include)

    configure_ccp_vendor_config_file(
        TARGET CcpMath
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/CcpMathConfig.cmake"
        DEPENDENCIES "DirectXMath"
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CcpMathConfig.cmake DESTINATION .)
endif()

