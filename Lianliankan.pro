greaterThan(QT_MAJOR_VERSION,4):QT+=widgets

FORMS += \
    game.ui \
    home.ui

HEADERS += \
    game.h \
    home.h \
    manage.h \
    enter.h \
    class.h \
    button.h \
    displaytime.h \
    player.h \
    show.h

SOURCES += \
    game.cpp \
    main.cpp \
    home.cpp \
    manage.cpp \
    enter.cpp \
    button.cpp \
    displaytime.cpp \
    player.cpp \
    show.cpp

RC_ICONS = F:/Lianliankan/pic_manage/myico.ico
QT += multimedia

