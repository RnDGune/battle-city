cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set ( PROJECT_NAME BattleCity) #set variable PROJECT_NAME = BattleCity
project (${PROJECT_NAME})# using PROJECT_NAME meaning

add_executable(${PROJECT_NAME} src/main.cpp)

#Flags for compile glfw library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Path to glfw for cmakelist.txt of glfw
add_subdirectory (external/glfw)
#Link library glfw ot project BattleCity
target_link_libraries (${PROJECT_NAME} glfw)


