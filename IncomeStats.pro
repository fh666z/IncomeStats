TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    IncomeOrder.cpp \
    Storage.cpp \
    JsonStorage.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    IncomeOrder.hpp \
    JsonStorage.hpp \
    Storage.hpp \
    Definitions.hpp
