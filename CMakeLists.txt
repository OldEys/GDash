cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(GDash)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(cmake/Options.cmake)

###############################################################################

# external dependencies with FetchContent
if (NOT DEFINED ENV{GITHUB_ACTIONS} OR NOT $ENV{GITHUB_ACTIONS})
    # AddressSanitizer settings
    set(USE_ASAN ON)
endif ()

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# din cauza SFML
set(WARNINGS_AS_ERRORS OFF)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:84
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
    # GIT_TAG        69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
    # GIT_TAG        origin/master
    GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)

FetchContent_MakeAvailable(SFML)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME}
    main.cpp
    generated/src/Helper.cpp
    env_fixes.h
        sources/Player.cpp
        headers/Player.h
        sources/Game.cpp
        headers/Game.h
        sources/Obstacle.cpp
        headers/Obstacle.h
        sources/Ground.cpp
        headers/Ground.h
        sources/Chunk.cpp
        headers/Chunk.h
        sources/TextureManager.cpp
        headers/TextureManager.h
        headers/Block.h
        sources/Block.cpp
        headers/Spike.h
        sources/Spike.cpp
        sources/Platform.cpp
        headers/Platform.h
        sources/Short_Spike.cpp
        headers/Short_Spike.h
        sources/Final.cpp
        headers/Final.h
        sources/LevelProgression.cpp
        headers/LevelProgression.h
        sources/AttemptCounter.cpp
        headers/AttemptCounter.h
        sources/DeathEffect.cpp
        headers/DeathEffect.h
        sources/Exceptions.cpp
        headers/Exceptions.h
        headers/JumpOrb.h
        sources/JumpOrb.cpp
        sources/ObstacleFactory.cpp
        headers/ObstacleFactory.h
        headers/Level.h
        sources/Level.cpp
        headers/Menu.h
        sources/Menu.cpp
        headers/Button.h
        sources/Button.cpp
)

include(cmake/CompilerFlags.cmake)

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE generated/include)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-audio sfml-system Threads::Threads)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()


# copy dependent DLLs to build dir
# see https://en.sfml-dev.org/forums/index.php?topic=28580.0
# remove this if not using audio or if using SFML 3
if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
         ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
         $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()


include(cmake/CopyHelper.cmake)
copy_files(FILES tastatura.txt DIRECTORY font sound images maps)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)
