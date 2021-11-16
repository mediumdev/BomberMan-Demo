#include "mainwindow.h"

const int TICKS_PER_SECOND = 20;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
int next_game_tick = QDateTime::currentMSecsSinceEpoch();
int cur_tick = QDateTime::currentMSecsSinceEpoch();
int fps=0;
int loop=0;
int aps=0;

MainWindow::MainWindow(QWidget* parent) : QGLWidget(parent)
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_StyledBackground, false);
    setAttribute(Qt::WA_AcceptTouchEvents);
    #if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    setAttribute( Qt::WA_LockLandscapeOrientation, true);
    #endif
    setAutoBufferSwap(false);
    
    keys.resize(7);
    for (int i = 0; i < keys.count(); i++)
    {
        keys[i] = Keyboard::NONE;
    }
    
    press=false;

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(30);
}

void MainWindow::initializeGL()
{
    game = new Game(this);
    game->pause=false;
    game->fps=0;
    game->aps=0;
    game->init(); 
}

void MainWindow::resizeGL(int width, int height) 
{
    game->resize();
}

void MainWindow::paintGL()
{
    if (!game->pause){
        loop = 0;
        int cur_game_tick = QDateTime::currentMSecsSinceEpoch();
        while((cur_game_tick > next_game_tick) && (loop < MAX_FRAMESKIP)) {
            game->update();
            loop++;
            aps++;
            next_game_tick += SKIP_TICKS;
        }
    }
    
    game->draw();
    fps++;
    
    int curms = QDateTime::currentMSecsSinceEpoch();
    if (cur_tick+1000<curms)
    {
        game->fps=fps;
        game->aps=aps;
        aps=0;
        fps=0;
        cur_tick = QDateTime::currentMSecsSinceEpoch();
    }
    
    QPainter drawinfo(this);
    drawinfo.setPen(Qt::white);
    drawinfo.setFont(QFont("Arial", 10));
    drawinfo.drawText(5, 35, QString("%1, %2").arg(game->fps).arg(game->aps));
    
    /*drawinfo.drawText(5, 65, QString("%1").arg(width()));
    drawinfo.drawText(5, 95, QString("%1").arg(height()));
    
    for (int i = 0; i < points.count(); i++)
    {
        drawinfo.drawText(5, 125+i*30, QString("%1, %2").arg(points[i].x).arg(points[i].y));
    }*/

    swapBuffers();
}

bool MainWindow::event(QEvent *e){
    switch (e->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(e);
        if (touchEvent->touchPoints().count()>0)
        {
            points.clear();
            for (int i = 0; i < touchEvent->touchPoints().count(); i++)
            {
                Point pnt;
                pnt.x = touchEvent->touchPoints()[i].pos().x();
                pnt.y = touchEvent->touchPoints()[i].pos().y();
                pnt.state = touchEvent->touchPoints()[i].state();
                points.append(pnt);
            }
            game->touchUpdate(points);
        }
        break;
    }

    default:
        return QGLWidget::event(e);
    }

    return true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    points.clear();

    if (press)
    {
        Point pnt;
        pnt.x = e->x();
        pnt.y = e->y();
        pnt.mouseState = 1;
        points.append(pnt);
    }
    
    game->touchUpdate(points);
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    points.clear();
    
    if (e->button() == Qt::LeftButton)
    {
        Point pnt;
        pnt.x = e->x();
        pnt.y = e->y();
        pnt.mouseState = 2;
        points.append(pnt);
        press=true;
    }
    
    game->touchUpdate(points);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    points.clear();
    
    if (e->button() == Qt::LeftButton)
    {
        Point pnt;
        pnt.x = e->x();
        pnt.y = e->y();
        pnt.mouseState = 3;
        points.append(pnt);
        press=false;
    }
    
    game->touchUpdate(points);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Up)
    {
        keys[0] = Keyboard::UP;
    }
    if (e->key() == Qt::Key_Down)
    {
        keys[1] = Keyboard::DOWN;
    }
    if (e->key() == Qt::Key_Left)
    {
        keys[2] = Keyboard::LEFT;
    }
    if (e->key() == Qt::Key_Right)
    {
        keys[3] = Keyboard::RIGHT;
    }
    if (e->key() == Qt::Key_Z)
    {
        keys[4] = Keyboard::A;
    }
    if (e->key() == Qt::Key_X)
    {
        keys[5] = Keyboard::B;
    }
    if (e->key() == Qt::Key_Escape)
    {
        keys[6] = Keyboard::MENU;
    }
    game->keyUpdate(keys);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
    if (!e->isAutoRepeat())
    {
        if (e->key() == Qt::Key_Up)
        {
            keys[0] = Keyboard::NONE;
        }
        if (e->key() == Qt::Key_Down)
        {
            keys[1] = Keyboard::NONE;
        }
        if (e->key() == Qt::Key_Left)
        {
            keys[2] = Keyboard::NONE;
        }
        if (e->key() == Qt::Key_Right)
        {
            keys[3] = Keyboard::NONE;
        }
        if (e->key() == Qt::Key_Z)
        {
            keys[4] = Keyboard::NONE;
        }
        if (e->key() == Qt::Key_X)
        {
            keys[5] = Keyboard::NONE;
        }
        if (e->key() == Qt::Key_Escape)
        {
            keys[6] = Keyboard::NONE;
        }
        game->keyUpdate(keys);
    }
}
