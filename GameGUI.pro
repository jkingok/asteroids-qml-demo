TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    asteroidfield.cpp \
    asteroidcreator.cpp \
    asteroid.cpp \
    asteroidupdater.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    asteroidfield.h \
    asteroidcreator.h \
    asteroid.h \
    asteroidupdater.h \
    asteroidprovider.h
