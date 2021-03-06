QT += network sql xml
QT -= gui

TARGET = cm-lib
TEMPLATE = lib

CONFIG += c++14

DEFINES += CMLIB_LIBRARY

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

INCLUDEPATH += source

SOURCES += \
    source/data/dropdown.cpp \
    source/data/dropdownvalue.cpp \
    source/framework/objectfactory.cpp \
    source/models/client.cpp \
    source/controllers/databasecontroller.cpp \
    source/controllers/master-controller.cpp \
    source/framework/command.cpp \
    source/controllers/command-controller.cpp \
    source/data/data-decorator.cpp \
    source/data/string-decorator.cpp \
    source/data/int-decorator.cpp \
    source/data/datetime-decorator.cpp \
    source/data/enumerator-decorator.cpp \
    source/data/entity.cpp \
    source/models/address.cpp \
    source/models/appointment.cpp \
    source/models/clientsearch.cpp \
    source/models/contact.cpp \
    source/network/WebRequest.cpp \
    source/network/networkaccessmanager.cpp \


HEADERS += \
    source/cm-lib_global.h \
    source/controllers/I-database-controller.h \
    source/controllers/databasecontroller.h \
    source/data/dropdown.h \
    source/data/dropdownvalue.h \
    source/framework/i-object-factory.h \
    source/framework/objectfactory.h \
    source/models/client.h \
    source/controllers/master-controller.h \
    source/controllers/navigation-controller.h \
    source/framework/command.h \
    source/controllers/command-controller.h \
    source/data/data-decorator.h \
    source/data/string-decorator.h \
    source/data/int-decorator.h \
    source/data/datetime-decorator.h \
    source/data/enumerator-decorator.h \
    source/data/entity.h \
    source/data/entity-collection.h \
    source/models/address.h \
    source/models/appointment.h \
    source/models/clientsearch.h \
    source/models/contact.h \
    source/network/i-network-access-manager.h \
    source/network/i-web-request.h \
    source/network/networkaccessmanager.h \
    source/network/webrequest.h \
message(cm-lib project dir: $${PWD})

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui
message(cm-lib output dir: $${DESTDIR})
