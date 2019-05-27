cmake_minimum_required(VERSION 3.5)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(PROJECT_MINOR_VERSION $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(PROJECT_MINOR_VERSION 0)
endif()

project(ip_filter VERSION 0.0.${PROJECT_MINOR_VERSION})

include(gtest.cmake)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT py.krivosheev@gmail.com)
set(CPACK_PACKAGE_DESCRIPTION "Matrix")

include(CPack)
