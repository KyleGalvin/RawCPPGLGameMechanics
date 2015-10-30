
QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
lessThan(QT_MAJOR_VERSION, 5): error(This project requires Qt 5 or later)

unix: !macx {
    INCLUDEPATH +=  /usr/include
    LIBS += /usr/lib/libassimp.so
}

macx {
    INCLUDEPATH +=  /usr/local/include
    LIBS += /usr/local/lib/libassimp.dylib
}

win32 {
    INCLUDEPATH += "C:/Assimp3/include"
    LIBS += -L"C:/Assimp3/lib/Release" -lassimp
}


OTHER_FILES += ads_fragment.vert \
    ads_fragment.frag \
    es_ads_fragment.frag \
    es_ads_fragment.vert

CONFIG      += C++11
HEADERS += keypress.h \
	openglwindow.h \
	modelloader.h \
	modelwindow.h \
	modelwindow_gl_2.h \
	modelwindow_gl_3_3.h 

SOURCES += main.cpp \
	keypress.cpp \
	openglwindow.cpp \
	modelloader.cpp \ 
	modelwindow.cpp \ 
	modelwindow_gl_2.cpp \
	modelwindow_gl_3_3.cpp

