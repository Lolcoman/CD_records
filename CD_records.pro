QT       += core gui sql #přidáno SQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasedata.cpp \
    imagedelegate.cpp \
    infowindow.cpp \
    insertwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    record.cpp \
    updatewindow.cpp

HEADERS += \
    databasedata.h \
    imagedelegate.h \
    infowindow.h \
    insertwindow.h \
    mainwindow.h \
    record.h \
    updatewindow.h

FORMS += \
    infowindow.ui \
    insertwindow.ui \
    mainwindow.ui \
    updatewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
