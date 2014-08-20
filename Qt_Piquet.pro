#-------------------------------------------------
#
# Project created by QtCreator 2014-07-17T12:28:05
#
#-------------------------------------------------

QT       += core gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Piquet
TEMPLATE = app


SOURCES +=\
    Main.cpp \
    Managers/GameManager.cpp \
    Managers/StateManager.cpp \
    Managers/ScoreManager.cpp \
    Managers/CardManager.cpp \
    Cards/CardArray.cpp \
    Cards/Card.cpp \
    View/View.cpp \
    Scene/Scene.cpp \
    State/TrickPhaseState.cpp \
    State/DealPhase.cpp \
    State/DeclarationPhase.cpp \
    State/ExchangePhase.cpp

HEADERS  += \
    Managers/GameManager.h \
    Managers/StateManager.h \
    Managers/ScoreManager.h \
    Managers/CardManager.h \
    Cards/CardArray.h \
    Cards/Card.h \
    View/View.h \
    Scene/Scene.h \
    State/CardStates.h \
    State/TrickPhaseState.h \
    State/DealPhase.h \
    State/DeclarationPhase.h \
    State/ExchangePhase.h

#FORMS    += MainWindow.ui

RESOURCES += \
    PiquetResources.qrc
