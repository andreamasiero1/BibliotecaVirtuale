TEMPLATE = app
TARGET = Prog
INCLUDEPATH += .

HEADERS += view/Biblioteca.h \
           model/Book.h \
           model/Film.h \
           model/MagazineArticle.h \
           model/Media.h \
           persistence/JsonSerializer.h \
           view/AddMediaDialog.h \
           view/EditMediaDialog.h \
           view/LoginDialog.h \
           view/MainWindow.h \
           view/MediaCollectorVisitor.h \
           view/MediaFactory.h \
           view/MediaVisitor.h \
           view/MediaWidgetVisitor.h \
           view/User.h \
           view/UserAuthenticator.h
SOURCES += main.cpp \
           view/Biblioteca.cpp \
           model/Book.cpp \
           model/Film.cpp \
           model/MagazineArticle.cpp \
           model/Media.cpp \
           persistence/JsonSerializer.cpp \
           view/AddMediaDialog.cpp \
           view/EditMediaDialog.cpp \
           view/LoginDialog.cpp \
           view/MainWindow.cpp \
           view/MediaCollectorVisitor.cpp \
           view/MediaFactory.cpp \
           view/MediaWidgetVisitor.cpp \
           view/User.cpp \
           view/UserAuthenticator.cpp

QT +=  widgets
