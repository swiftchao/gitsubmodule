cmake_minimum_required(VERSION 3.10)
project(cmakehello CXX C ASM)
set(VERSION 1.0.0)

# Make sure we can import out CMake functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/boost")

#set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/src")
set(BoostRoot ${CMAKE_SOURCE_DIR}/src/boost)

add_subdirectory(src/glog)
add_subdirectory(src/googletest)
add_subdirectory(src/rapidjson)
#add_subdirectory(src/rocksdb)
#add_subdirectory(src/leveldb)
#add_subdirectory(src/zstd)
#add_subdirectory(src/boost)
#add_subdirectory(src/xxHash)
add_subdirectory(src/lib)
add_subdirectory(src/main)

include_directories(
  ${PROJECT_BINARY_DIR}/src/include
  ${PROJECT_SOURCE_DIR}/src)

#put all the libs and binaries in one place
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
include_directories(${PROJECT_SOURCE_DIR}/src/rapidjson/include)
include_directories(${PROJECT_SOURCE_DIR}/src/boost)

# Boost
option(WITH_SYSTEM_BOOST "require and build with system Boost" OFF)

# Boost::thread depends on Boost::atomic, so list it explicitly.
set(BOOST_COMPONENTS
  atomic chrono thread system regex random program_options date_time
  iostreams filesystem)
set(BOOST_HEADER_COMPONENTS container)

if(WITH_MGR)
  list(APPEND BOOST_COMPONENTS
    python${MGR_PYTHON_VERSION_MAJOR}${MGR_PYTHON_VERSION_MINOR})
endif()
if(WITH_BOOST_CONTEXT)
  list(APPEND BOOST_COMPONENTS context coroutine)
endif()
if(WITH_SEASTAR)
  list(APPEND BOOST_COMPONENTS filesystem timer)
endif()

set(Boost_USE_MULTITHREADED ON)
# require minimally the bundled version
if(WITH_SYSTEM_BOOST)
  if(ENABLE_SHARED)
    set(Boost_USE_STATIC_LIBS OFF)
  else()
    set(Boost_USE_STATIC_LIBS ON)
  endif()
  if(BOOST_ROOT AND CMAKE_LIBRARY_ARCHITECTURE)
    set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib/${CMAKE_LIBRARY_ARCHITECTURE}")
  endif()
  #find_package(Boost 1.72 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
  find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
else()
  set(BOOST_J 1 CACHE STRING
    "max jobs for Boost build") # override w/-DBOOST_J=<n>
  set(Boost_USE_STATIC_LIBS ON)
  include(BuildBoost)
  #build_boost(1.72
  build_boost(
    COMPONENTS ${BOOST_COMPONENTS} ${BOOST_HEADER_COMPONENTS})
endif()
include_directories(BEFORE SYSTEM ${Boost_INCLUDE_DIRS})
set(Boost_USE_MULTITHREADED ON)
