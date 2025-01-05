cmake_minimum_required(VERSION 3.5)
project(lutil C)

set(LUTIL_VERSION_MAJOR 1)
set(LUTIL_VERSION_MINOR 0)
set(LUTIL_VERSION_PATCH 0)
set(LUTIL_VERSION
    "${LUTIL_VERSION_MAJOR}.${LUTIL_VERSION_MINOR}.${LUTIL_VERSION_PATCH}"
)

# Export compile commands (helps with IDEs / editors, e.g. clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------------
# Create the library
# --------------------------------------------
add_library(lutil
    src/llog.c
    src/lresult.c
    src/ltest.c
)

target_include_directories(lutil
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_property(TARGET lutil PROPERTY C_STANDARD 99)

# --------------------------------------------
# Install rules
# --------------------------------------------
install(TARGETS lutil
    EXPORT lutil-targets      # For exporting to config
    RUNTIME DESTINATION bin   # For .dll/.exe on Windows
    LIBRARY DESTINATION lib   # For .so/.dylib on Linux/macOS
    ARCHIVE DESTINATION lib   # For .a/.lib
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include
)

# --------------------------------------------
# Export and Config for find_package
# --------------------------------------------
install(EXPORT lutil-targets
    FILE lutilTargets.cmake
    NAMESPACE lutil::
    DESTINATION lib/cmake/lutil
)

# Generate a basic version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/lutilConfigVersion.cmake"
    VERSION ${LUTIL_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Create a config file referencing the exports
configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/lutilConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/lutilConfig.cmake"
    @ONLY
)

install(FILES
    "${PROJECT_BINARY_DIR}/lutilConfig.cmake"
    "${PROJECT_BINARY_DIR}/lutilConfigVersion.cmake"
    DESTINATION lib/cmake/lutil
)

message(STATUS "lutil library version: ${LUTIL_VERSION}")

