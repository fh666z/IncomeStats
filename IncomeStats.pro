TEMPLATE = app

RC_ICONS = images/app_icon.ico

QT += qml quick sql widgets
CONFIG += c++1y

INCLUDEPATH += "C:\Program Files (x86)\MySQL\MySQL Server 5.7\include"
INCLUDEPATH += "C:\Program Files (x86)\MySQL\MySQL Server 5.7\lib"

LIBS += -L"C:\Program Files (x86)\MySQL\MySQL Server 5.7\lib" -llibmysql

SOURCES += main.cpp \
    IncomeOrder.cpp \
    Storage.cpp \
    JsonStorage.cpp \
    IncomeOrderModel.cpp \
    SQLStorage.cpp \
    IncomeOrderSQLModel.cpp \
    IncomeType.cpp \
    ViewModelTransactionHandler.cpp

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
    IncomeType.hpp \
    ViewModelTransactionHandler.hpp

DISTFILES += \
    images/app_icon.ico
