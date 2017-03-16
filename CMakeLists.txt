cmake_minimum_required(VERSION 3.0.0)

SET(name moran-automaton)
SET(CMAKE_CXX_FLAGS "-std=c++14")

add_executable(moran-automaton main.cpp map.cpp cell.cpp mapdrawer.cpp)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package (SDL2)
if (SDL2_FOUND)
  include_directories(${SDL2_INCLUDE_DIRS})
  target_link_libraries (moran-automaton ${SDL2_LIBRARIES} -lSDL2)
endif (SDL2_FOUND)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror")
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()