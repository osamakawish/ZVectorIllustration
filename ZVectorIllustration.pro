QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    GraphicsItems/Curves/curve.cpp \
    GraphicsItems/Curves/node.cpp \
    GraphicsItems/Curves/vector.cpp \
    GraphicsItems/Shapes/shape.cpp \
    GraphicsItems/graphicsitem.cpp \
    Windows/MainWindow/MainWidgets/filewidget.cpp \
    Windows/MainWindow/MainWidgets/graphicsview.cpp \
    Windows/MainWindow/MainWidgets/propertywidget.cpp \
    Windows/MainWindow/SubWidgets/colorsetter.cpp \
    Windows/MainWindow/SubWidgets/radiobuttongrid.cpp \
    Windows/MainWindow/SubWidgets/valuesetter.cpp \
    Windows/MainWindow/mainwindow.cpp \
    Windows/settingswindow.cpp \
    Windows/helpwindow.cpp \
    main.cpp

HEADERS += \
    ActionMethods/mouseaction.h \
    ActionMethods/mousebehaviour.h \
    ActionMethods/penaction.h \
    ActionMethods/textaction.h \
    ActionMethods/zoomaction.h \
    GraphicsItems/Curves/curve.h \
    GraphicsItems/Curves/node.h \
    GraphicsItems/Curves/vector.h \
    GraphicsItems/Shapes/shape.h \
    GraphicsItems/graphicsitem.h \
    Windows/MainWindow/MainWidgets/filewidget.h \
    Windows/MainWindow/MainWidgets/graphicsview.h \
    Windows/MainWindow/MainWidgets/propertywidget.h \
    Windows/MainWindow/SubWidgets/colorsetter.h \
    Windows/MainWindow/SubWidgets/radiobuttongrid.h \
    Windows/MainWindow/SubWidgets/valuesetter.h \
    Windows/MainWindow/mainwindow.h \
    Windows/settingswindow.h \
    Windows/helpwindow.h

FORMS += \
    Windows/MainWindow/MainWidgets/filewidget.ui \
    Windows/MainWindow/MainWidgets/propertywidget.ui \
    Windows/MainWindow/SubWidgets/colorsetter.ui \
    Windows/MainWindow/SubWidgets/radiobuttongrid.ui \
    Windows/MainWindow/SubWidgets/valuesetter.ui \
    Windows/MainWindow/mainwindow.ui \
    Windows/settingswindow.ui \
    Windows/helpwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Windows/MainWindow/icons.qrc
