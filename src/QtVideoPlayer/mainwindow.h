#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPaintEvent>
#include <QWidget>
#include <QtDebug>
#include <QThread>
#include <QPainter>

#include "videoplayer.h"

#define WINDOW_MIN_WIDTH    600
#define INFOBAR_HEIGHT      70

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    VideoPlayer *Player;
    QImage mImage;
    QString url;

    int ImageWidth;
    int ImageHeight;
    bool Connected = false;

private slots:
    void slotGetOneFrame(QImage img);
    void slotGetVideoCodec(int Codec);
    void slotGetAudioCodec(int Codec);
    void slotGetData(int Data);
    QString CodectoString(int Codec);
    void EraseInfo();
    void on_pb_Connect_clicked();
};

#endif // MAINWINDOW_H
