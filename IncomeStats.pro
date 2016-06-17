TEMPLATE = app

QT += qml quick
CONFIG += c++1y

SOURCES += main.cpp \
    IncomeOrder.cpp \
    Storage.cpp \
    JsonStorage.cpp \
    IncomeOrderModel.cpp

RESOURCES += qml.qrc


# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    IncomeOrder.hpp \
    JsonStorage.hpp \
    Storage.hpp \
    Definitions.hpp \
    IncomeOrderModel.hpp
