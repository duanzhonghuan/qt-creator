include(../../qtcreatorplugin.pri)

SOURCES = \
    compilationdatabaseproject.cpp \
    compilationdatabaseprojectmanagerplugin.cpp \
    compilationdatabaseutils.cpp

HEADERS = \
    compilationdatabaseproject.h \
    compilationdatabaseprojectmanagerplugin.h \
    compilationdatabaseconstants.h \
    compilationdatabaseutils.h

equals(TEST, 1) {
    HEADERS += \
        compilationdatabasetests.h

    SOURCES += \
        compilationdatabasetests.cpp

    RESOURCES += compilationdatabasetests.qrc
}
