# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xE470016E

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

QT += opengl

SOURCES += main.cpp mainwindow.cpp \
    touch.cpp \
    texture.cpp \
    mesh.cpp \
    level.cpp \
    game.cpp \
    control.cpp \
    camera.cpp \
    shader.cpp \
    objects.cpp \
    player.cpp \
    bomb.cpp \
    model.cpp \
    explosion.cpp \
    zombie.cpp \
    enemy.cpp \
    image.cpp \
    trackball.cpp
HEADERS += mainwindow.h \
    touch.h \
    texture.h \
    level.h \
    game.h \
    control.h \
    camera.h \
    mesh.h \
    shader.h \
    objects.h \
    player.h \
    bomb.h \
    model.h \
    explosion.h \
    zombie.h \
    enemy.h \
    image.h \
    trackball.h
FORMS +=

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    shaders/textured.vsh \
    shaders/textured.fsh \
    shaders/image.vsh \
    shaders/image.fsh
