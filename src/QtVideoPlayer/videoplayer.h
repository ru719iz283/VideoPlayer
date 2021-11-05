#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QImage>


class VideoPlayer : public QThread
{
    Q_OBJECT

public:
    explicit VideoPlayer();
    ~VideoPlayer();

    void StartPlay(QString VideoUrl);
    void StopPlay();

signals:
    void sig_GetOneFrame(QImage);
    void sig_GetVideoCodec(int);
    void sig_GetAudioCodec(int);
    void sig_GetData(int);

protected:
    void run();

private:
    int GopCount = 0;
    QString Url;
    bool PlayVideo = false;
};

#endif // VIDEOPLAYER_H
