cmake_minimum_required (VERSION 3.23.0)

file(GLOB CLEAN_FOLDER ${CMAKE_BINARY_DIR}/build/)


find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})
link_libraries(${wxWidgets_LIBRARIES})
# and for each of your dependent executable/library targets:


include_directories("src/Utilities")
include_directories("src/World")
include_directories("src/Tracers")
include_directories("src/GeometricObjects")
include_directories("src/Build")
include_directories("src/Stb")
include_directories("src/Samplers")
include_directories("src/Cameras")



set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")


project (tracer VERSION 1.0
            DESCRIPTION "Ray Tracing from the Ground Up book example project"
            LANGUAGES C CXX
)



set (SOURCE_GEOMETRICOBJECTS
  src/GeometricObjects/GeometricObject.cpp
  src/GeometricObjects/GeometricObject.h
  src/GeometricObjects/Sphere.cpp
  src/GeometricObjects/Sphere.h
  src/GeometricObjects/Plane.cpp
  src/GeometricObjects/Plane.h
)

set (SOURCE_CAMERAS
  src/Cameras/Camera.cpp
  src/Cameras/Camera.h
  src/Cameras/Pinhole.cpp
  src/Cameras/Pinhole.h
  src/Cameras/ThinLens.cpp
  src/Cameras/ThinLens.h
  src/Cameras/FishEye.cpp
  src/Cameras/FishEye.h
)




set (SOURCE_SAMPLERS
  src/Samplers/Sampler.h
  src/Samplers/Sampler.cpp
  src/Samplers/Jittered.h
  src/Samplers/Jittered.cpp
  src/Samplers/Regular.h
  src/Samplers/Regular.cpp
  src/Samplers/MultiJittered.h
  src/Samplers/MultiJittered.cpp
  src/Samplers/NRooks.h
  src/Samplers/NRooks.cpp
  src/Samplers/Hammersley.h
  src/Samplers/Hammersley.cpp
)


set (SOURCE_TRACERS
  src/Tracers/SingleSphere.cpp
  src/Tracers/SingleSphere.h
  src/Tracers/MultipleObjects.cpp
  src/Tracers/MultipleObjects.h
  src/Tracers/Tracer.cpp
  src/Tracers/Tracer.h
)

set (SOURCE_UTILITIES
src/Utilities/Constants.h
src/Utilities/Maths.h
src/Utilities/Point2D.h
src/Utilities/Point2D.cpp
src/Utilities/Matrix.cpp
src/Utilities/Matrix.h
src/Utilities/Normal.cpp
src/Utilities/Normal.h
src/Utilities/Point3D.cpp
src/Utilities/Point3D.h
src/Utilities/Ray.cpp
src/Utilities/Ray.h
src/Utilities/RGBColor.cpp
src/Utilities/RGBColor.h
src/Utilities/ShadeRec.cpp
src/Utilities/ShadeRec.h
src/Utilities/Vector3D.cpp
src/Utilities/Vector3D.h
)
set (SOURCE_WORLD
  src/World/ViewPlane.cpp
  src/World/ViewPlane.h
  src/World/World.cpp
  src/World/World.h
)

source_group ("src/GeometricObjects" FILES ${SOURCE_GEOMETRICOBJECTS})
source_group ("src/Tracers" FILES ${SOURCE_TRACERS})
source_group ("src/Utilities" FILES ${SOURCE_UTILITIES})
source_group ("src/World" FILES ${SOURCE_WORLD})
source_group ("src/Samplers" FILES ${SOURCE_SAMPLERS})
source_group ("src/Cameras" FILES ${SOURCE_CAMERAS})


add_library (libRTF STATIC
  ${SOURCE_GEOMETRICOBJECTS}
  ${SOURCE_TRACERS}
  ${SOURCE_UTILITIES}
  ${SOURCE_WORLD}
  ${SOURCE_SAMPLERS}
  ${SOURCE_CAMERAS}
)

add_executable (tracer src/main.cpp)
target_link_libraries (tracer libRTF)


# Unit Test Setup

enable_testing ()


# SET_DIRECTORY_PROPERTIES(
#   PROPERTIES
#   ADDITIONAL_CLEAN_FILES
#   "${CMAKE_CURRENT_SOURCE_DIR}/build"
# )




