
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(../lib/src)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp Recorder.cpp Recorder.h RecordDialog.cpp RecordDialog.h LinearDisplay.cpp LinearDisplay.h WernickeMainWindow.cpp WernickeMainWindow.h TwoDimensionDisplay.cpp TwoDimensionDisplay.h RecordDisplay.cpp RecordDisplay.h)
add_executable(wernickeui ${SOURCE_FILES})

target_link_libraries(wernickeui wernicke portaudio Qt5::Widgets Qt5::PrintSupport Qt5::Multimedia qcustomplot)
