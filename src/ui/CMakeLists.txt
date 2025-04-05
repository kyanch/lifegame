# Qt for mac require cmake 3.21.1, other platform require cmake 3.16
cmake_minimum_required(VERSION 3.21.1)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Widgets)

set(QT_QML_GENERATE_QMLLS_INI ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(lifegameX
    main.cpp
    universedata.cpp
    res/main.qrc
)

qt_add_qml_module(lifegameX
    URI lgX
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/CellGrid.qml
        qml/ZoomFlick.qml
)
set_target_properties(lifegameX PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER icu.kyanch.lifegameX
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)

target_link_libraries(lifegameX
    PRIVATE Qt6::Core Qt6::Widgets Qt6::Quick lifegame
)