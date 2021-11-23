QT += core gui sql #Define QT utilization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets #Define QT minimum version

CONFIG += c++11 #Define QT C++ environnement

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # Disables all the APIs deprecated before Qt 6.0.0

TARGET = Application #Executable name

SOURCES += \ #Define QT project source files
    Main.cpp \
    ./source/Database.cpp \
    ./source/Signin.cpp \
    ./source/Signup.cpp \
    ./source/Log.cpp \
    ./source/Table.cpp \
    ./source/Add.cpp \
    ./source/Delete.cpp \
    ./source/Update.cpp \
    ./source/View.cpp

HEADERS += \ #Define QT project include files
    ./include/Database.h \
    ./include/Signin.h \
    ./include/Signup.h \
    ./include/Log.h \
    ./include/Table.h \
    ./include/Add.h \
    ./include/Delete.h \
    ./include/Update.h \
    ./include/View.h

FORMS += \  #Define QT project ui files
    ./form/Signin.ui \
    ./form/Signup.ui \
    ./form/Table.ui \
    ./form/Add.ui \
    ./form/Delete.ui \
    ./form/Update.ui \
    ./form/View.ui
