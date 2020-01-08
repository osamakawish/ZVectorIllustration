QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ActionMethods/mouseaction.cpp \
    ActionMethods/mousebehaviour.cpp \
    ActionMethods/penaction.cpp \
    ActionMethods/textaction.cpp \
    ActionMethods/zoomaction.cpp \
    Curves/curve.cpp \
    Curves/graphicsitem.cpp \
    Curves/node.cpp \
    Curves/vector.cpp \
    SubWidgets/colorsetter.cpp \
    SubWidgets/radiobuttongrid.cpp \
    SubWidgets/valuesetter.cpp \
    Windows/settingswindow.cpp \
    Windows/helpwindow.cpp \
    filewidget.cpp \
    graphicsview.cpp \
    main.cpp \
    mainwindow.cpp \
    propertywidget.cpp

HEADERS += \
    ActionMethods/mouseaction.h \
    ActionMethods/mousebehaviour.h \
    ActionMethods/penaction.h \
    ActionMethods/textaction.h \
    ActionMethods/zoomaction.h \
    Curves/curve.h \
    Curves/graphicsitem.h \
    Curves/node.h \
    Curves/vector.h \
    SubWidgets/colorsetter.h \
    SubWidgets/radiobuttongrid.h \
    SubWidgets/valuesetter.h \
    Windows/settingswindow.h \
    Windows/helpwindow.h \
    filewidget.h \
    graphicsview.h \
    mainwindow.h \
    propertywidget.h

FORMS += \
    SubWidgets/colorsetter.ui \
    SubWidgets/radiobuttongrid.ui \
    SubWidgets/valuesetter.ui \
    Windows/settingswindow.ui \
    Windows/helpwindow.ui \
    filewidget.ui \
    mainwindow.ui \
    propertywidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
