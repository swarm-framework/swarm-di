# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.8)

# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(swarm-di VERSION 0.1.0)

# Include config
include(Config/config.cmake)

# Include sub projects
find_dependencies(cxx-log)
find_dependencies(swarm-commons)

# Create targets
add_library(swarm-di
    Sources/swarm/di/Inject.cxx Sources/swarm/di/Inject.hxx Sources/swarm/di/Inject.txx 
    Sources/swarm/di/Injectable.hxx
    Sources/swarm/di/InjectableEntry.cxx Sources/swarm/di/InjectableEntry.hxx
    Sources/swarm/di/Scope.cxx Sources/swarm/di/Scope.hxx Sources/swarm/di/Scope.txx
)

# Global includes. Used by all targets
target_include_directories(
    swarm-di 
        
    PRIVATE
        ${cxx-log_INCLUDE_DIR}
        ${swarm-commons_INCLUDE_DIR}
)

# Include build
include(Config/build.cmake)

# Include test
add_subdirectory(Tests)
