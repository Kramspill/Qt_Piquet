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
    Managers/AnimationManager.cpp \
    Animation/PhaseAnimation.cpp \
    Animation/DealPhaseAnimation.cpp \
    Animation/ExchangePhaseAnimation.cpp \
    Animation/DeclarationPhaseAnimation.cpp \
    Animation/TrickPhaseAnimation.cpp \
    Managers/WindowManager.cpp \
    Managers/ScoreManager.cpp \
    Managers/CardManager.cpp \
    Cards/CardArray.cpp \
    Cards/Card.cpp \
    AppWindows/MainWindow.cpp \
    View/View.cpp \
    Scene/Scene.cpp \
    State/DealPhaseState.cpp \
    State/DeclarationPhaseState.cpp \
    State/ExchangePhaseState.cpp \
    State/TrickPhaseState.cpp

HEADERS  += \
    Managers/GameManager.h \
    Managers/StateManager.h \
    Managers/AnimationManager.h \
    Animation/PhaseAnimation.h \
    Animation/DealPhaseAnimation.h \
    Animation/ExchangePhaseAnimation.h \
    Animation/DeclarationPhaseAnimation.h \
    Animation/TrickPhaseAnimation.h \
    Managers/WindowManager.h \
    Managers/ScoreManager.h \
    Managers/CardManager.h \
    Cards/CardArray.h \
    Cards/Card.h \
    AppWindows/MainWindow.h \
    View/View.h \
    Scene/Scene.h \
    State/CardStates.h \
    State/DealPhaseState.h \
    State/DeclarationPhaseState.h \
    State/ExchangePhaseState.h \
    State/TrickPhaseState.h

#FORMS    += MainWindow.ui

RESOURCES += \
    PiquetResources.qrc
