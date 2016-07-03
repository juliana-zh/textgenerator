cmake_minimum_required(VERSION 2.8)

project(textGenerator)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 5.2
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.2)
        message(FATAL_ERROR "GCC version must be at least 5.2!")
    endif()
else()
    message(WARNING "You are using an unsupported compiler! Compilation has only been tested with GCC.")
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0 -std=c++11 -Wall")

find_package(Boost 1.54.0 COMPONENTS filesystem system regex unit_test_framework program_options REQUIRED)
find_package(ICU 52.1 COMPONENTS io i18n REQUIRED )

include_directories(${Boost_INCLUDE_DIR} ${ICU_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIR})


add_executable(textGenerator 
      src/generator.cpp 
      src/model.cpp 
      src/utils.cpp 
      src/dictionary.cpp 
      src/main.cpp
      )
target_link_libraries( textGenerator      
      ${Boost_LIBRARIES} 
      ${ICU_LIBRARIES}      
      )

add_executable(utest
      src/model.cpp
      src/dictionary.cpp 
      src/utils.cpp
      src/generator.cpp
      test/test_dictionary.cpp 
      test/test_utils.cpp
      test/test_generator.cpp
      test/main.cpp
      test/test_model.cpp
      )      
target_link_libraries( utest      
      ${Boost_LIBRARIES} 
      ${ICU_LIBRARIES}
      )
      
install(TARGETS textGenerator RUNTIME DESTINATION bin)
