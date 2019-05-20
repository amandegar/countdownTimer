QT += widgets
CONFIG += static
QMAKE_CXXFLAGS += -static
QMAKE_LFLAGS += -static

HEADERS       = \
    newtimedialog.h \
    analogcountdown.h
SOURCES       = \
                main.cpp \
    newtimedialog.cpp \
    analogcountdown.cpp

QMAKE_PROJECT_NAME = widgets_analogcountdown
RC_FILE = analogcountdown.rc
