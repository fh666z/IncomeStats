TEMPLATE = app

QT += qml quick sql
CONFIG += c++1y

SOURCES += main.cpp \
    IncomeOrder.cpp \
    Storage.cpp \
    JsonStorage.cpp \
    IncomeOrderModel.cpp \
    SQLStorage.cpp \
    IncomeOrderSQLModel.cpp \
    IncomeType.cpp

RESOURCES += qml.qrc


# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    IncomeOrder.hpp \
    JsonStorage.hpp \
    Storage.hpp \
    Definitions.hpp \
    IncomeOrderModel.hpp \
    SQLStorage.hpp \
    IncomeOrderSQLModel.hpp \
    IncomeType.hpp
