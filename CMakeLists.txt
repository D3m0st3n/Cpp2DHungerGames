cmake_minimum_required(VERSION 3.10)
project(Sim2D)

# SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS})

# Set files names
set(SOURCE_FILES src/main.cpp src/Simulation2D.cpp src/Fly2D.cpp src/Arena2D.cpp src/Wall.cpp src/Entrance.cpp src/Food.cpp src/Rectangle.cpp)
set(DRAW_2D_FILES src/DrawArena2D.cpp src/Simulation2D.cpp src/Fly2D.cpp src/Arena2D.cpp src/Wall.cpp  src/Entrance.cpp src/Food.cpp src/Utility_SDL.cpp src/Rectangle.cpp)

# SDL2 search command, REQUIRES SLD2 to be installed
find_package(SDL2 REQUIRED)

# Create SimData directory for data storage
file(MAKE_DIRECTORY build/SimData)
file(MAKE_DIRECTORY build/SimConfig)

# Create executables
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(DrawArena2d ${DRAW_2D_FILES})

# Link SDL2 directory to project
target_include_directories(DrawArena2d PUBLIC ${SDL2_INCLUDE_DIRS})

# Link SDL2 library to project
target_link_libraries(DrawArena2d ${SDL2_LIBRARIES})
