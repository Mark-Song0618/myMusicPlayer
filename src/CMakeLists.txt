# config qt
set(CMAKE_PREFIX_PATH "D:\\qtForVs")
#set(AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/src/ui)
# 设置qrc文件的路径
set(QRC_FILE "D:\\MyProjects\\GitHubProjects\\QtMusicPlayer\\resources\\res.qrc")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS Widgets Sql Multimedia MultimediaWidgets REQUIRED)

file(GLOB src ./*.cpp)
file(GLOB headers ./*.h)
file(GLOB uis ./*.ui)
qt_add_resources(QRC_SOURCES ${QRC_FILE})
add_executable(MyMusicPlayer ${src} ${headers} ${uis} ${QRC_SOURCES})

target_link_libraries(MyMusicPlayer
					  Qt6::Widgets 
					  Qt6::MultimediaWidgets 
					  Qt6::Sql
					  Qt6::Multimedia)

add_custom_command(TARGET MyMusicPlayer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "D:\\qtForVs\\6.5.0\\msvc2019_64\\plugins\\sqldrivers\\qsqlited.dll"
            ${CMAKE_BINARY_DIR}/qsqlited.dll
    COMMENT "Copying yourfile.txt to the binary directory"
)