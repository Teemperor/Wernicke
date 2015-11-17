cmake_minimum_required(VERSION 3.3)
project (wernicke)

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/WernickeMachine.cpp src/WernickeMachine.h src/Record.cpp src/Record.h src/NormalDistribution.cpp src/NormalDistribution.h src/Tools.h src/SilenceClassificator.cpp src/SilenceClassificator.h src/Range.cpp src/Range.h tests/RecordTest.cpp src/Criterion.cpp src/Criterion.h)

add_library(wernicke ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(wernicke ${Boost_LIBRARIES} )

#########
# TESTS #
#########
enable_testing()

configure_file(tests/testfiles/adrei01.raw ${CMAKE_CURRENT_BINARY_DIR}/adrei01.raw COPYONLY)
configure_file(tests/testfiles/silence.raw ${CMAKE_CURRENT_BINARY_DIR}/silence.raw COPYONLY)

file(GLOB TEST_FILES "tests/*Test.cpp")
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(BASENAME ${TEST_FILE} NAME_WE)
    add_executable(${BASENAME} ${TEST_FILE})
    target_link_libraries(${BASENAME} wernicke ${LIBS})
    add_test(${BASENAME} ${BASENAME})
endforeach()
