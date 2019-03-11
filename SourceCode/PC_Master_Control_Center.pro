QT += quick
CONFIG += c++11
QT += serialport
QT += concurrent
QT += widgets
QT += qml
QT += quick qml
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    main.cpp \
    main.cpp \
    FrontEnd.cpp \
    FrontEnd.cpp \
    BackEnd.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
TARGET = STEAMAPI

HEADERS += \
    BackEnd.h \
    BackEnd.h \
    BackEnd.h \
    isteamapplist.h \
    isteamapps.h \
    isteamappticket.h \
    isteamclient.h \
    isteamcontroller.h \
    isteamfriends.h \
    isteamgamecoordinator.h \
    isteamgameserver.h \
    isteamgameserverstats.h \
    isteamhtmlsurface.h \
    isteamhttp.h \
    isteaminventory.h \
    isteammasterserverupdater.h \
    isteammatchmaking.h \
    isteammusic.h \
    isteammusicremote.h \
    isteamnetworking.h \
    isteamparentalsettings.h \
    isteamps3overlayrenderer.h \
    isteamremotestorage.h \
    isteamscreenshots.h \
    isteamugc.h \
    isteamunifiedmessages.h \
    isteamuser.h \
    isteamuserstats.h \
    isteamutils.h \
    isteamvideo.h \
    matchmakingtypes.h \
    steam_api.h \
    steam_api_flat.h \
    steam_api_internal.h \
    steam_gameserver.h \
    steamclientpublic.h \
    steamencryptedappticket.h \
    steamhttpenums.h \
    steamps3params.h \
    steamtypes.h \
    steamuniverse.h \
    FrontEnd.h \
    FrontEnd.h \
    librarycollection.h \
    BackEnd.h

win32: LIBS += -L$$PWD/../lib2/ -lsteam_api64

INCLUDEPATH += $$PWD/../lib2
DEPENDPATH += $$PWD/../lib2

win32: LIBS += -L$$PWD/../lib2/ -lsteam_api

INCLUDEPATH += $$PWD/../lib2
DEPENDPATH += $$PWD/../lib2

DISTFILES += \
    steam_api.json \
    steam_api_interop.cs


