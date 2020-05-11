QT += quick

CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        directorywatcher/directorywatcher.cpp \
        directorywatcher/directorywatcher_win_p.cpp \
        filesmodel.cpp \
        main.cpp \
        worker.cpp

RESOURCES +=  qml/qml.qrc

HEADERS += \
    directorywatcher/directorywatcher.h \
    directorywatcher/directorywatcher_p.h \
    directorywatcher/directorywatcher_win_p.h \
    directorywatcher/directorywatcherhelper.h \
    filesmodel.h \
    worker.h

OTHER_FILES += \
    README.md
