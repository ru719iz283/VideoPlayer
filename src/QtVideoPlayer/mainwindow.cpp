#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
   ui(new Ui::MainWindow)
{ 
	
    ui->setupUi(this);
    EraseInfo();
    Player = new VideoPlayer;
    connect(Player,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage)));
    connect(Player,SIGNAL(sig_GetVideoCodec(int)), this, SLOT(slotGetVideoCodec(int)));
    connect(Player,SIGNAL(sig_GetAudioCodec(int)), this, SLOT(slotGetAudioCodec(int)));
    connect(Player,SIGNAL(sig_GetData(int)), this, SLOT(slotGetData(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, this->width(), this->height());

    if (mImage.size().width() <= 0) return;

    QSize ScaleSize = this->size();
    ScaleSize.setHeight(ScaleSize.height() - INFOBAR_HEIGHT);
    QImage img = mImage.scaled(ScaleSize, Qt::KeepAspectRatio);

    int x = this->width() - img.width();
    int y = INFOBAR_HEIGHT;

    x /= 2;

    painter.drawImage(QPoint(x,y),img);
}

void MainWindow::slotGetOneFrame(QImage img)
{
    if(!Connected) { return; }
    mImage = img;
    ui->lb_Resolution->setText(QString::number(img.width()) + "x" + QString::number(img.height()));
    if(ImageWidth != img.width() || ImageHeight != img.width()){
        int WindowWidth = img.width();
        ImageWidth = img.width();
        ImageHeight = img.height();
        if(WindowWidth <= WINDOW_MIN_WIDTH) {
            WindowWidth = WINDOW_MIN_WIDTH;
        }
        setFixedSize(WindowWidth, img.height() + INFOBAR_HEIGHT);
    }
    update();
}

void MainWindow::slotGetVideoCodec(int Codec)
{
    ui->lb_VideoCodec->setText("Video codec: " + CodectoString(Codec));
}

void MainWindow::slotGetAudioCodec(int Codec)
{
//    ui->lb_AudioCodec->setText("Audio: " + QString::number(Codec));
    ui->lb_AudioCodec->setText("Audio codec: " + CodectoString(Codec));
}

void MainWindow::slotGetData(int Data)
{
    ui->lb_GOP->setText("GOP: " + QString::number(Data));
}

QString MainWindow::CodectoString(int Codec)
{
    QString VideoCodecArray[] = {"UNKNOWN", "MPEG1VIDEO", "MPEG2VIDEO", "H261", "H263", "RV10",
                                "RV20", "MJPEG", "MJPEGB", "LJPEG", "SP5X", "JPEGLS", "MPEG4",
                                "RAWVIDEO", "MSMPEG4V1", "MSMPEG4V2", "MSMPEG4V3", "WMV1", "WMV2", "H263P", "H263I", "FLV1",
                                "SVQ1", "SVQ3", "DVVIDEO", "HUFFYUV", "CYUV", "H264", "INDEO3", "VP3",
                                "THEORA", "ASV1", "ASV2", "FFV1", "4XM", "VCR1", "CLJR", "MDEC"};
    QString AudioCodecArray[] = { "MP2", "MP3", "AAC", "AC3", "DTS", "VORBIS", "DVAUDIO",
                                "WMAV1", "WMAV2", "MACE3", "MACE6", "VMDAUDIO"};
    QString Ret;
    if(Codec <= 37) { Ret = VideoCodecArray[Codec]; }
    else if (Codec == 173) { Ret = "HEVC (H265)"; }
    else if (Codec >= 0x15000 && Codec <= 0x1500C) { Ret = AudioCodecArray[Codec - 0x15000]; }
    else { Ret = QString::number(Codec); }
    return Ret;
}

void MainWindow::EraseInfo()
{
    ui->pb_Connect->setText("Connect");
    setFixedSize(WINDOW_MIN_WIDTH, INFOBAR_HEIGHT);
    ui->lb_VideoCodec->setText("Video codec: ");
    ui->lb_AudioCodec->setText("Audio codec: ");
    ui->lb_GOP->setText("GOP: ");
    return;
}

void MainWindow::on_pb_Connect_clicked()
{
    if(Connected) {
        Connected = false;
        Player->StopPlay();
        EraseInfo();
    } else {
        Connected = true;
        Player->StartPlay(ui->le_Url->text());
        ui->pb_Connect->setText("Disconnect");
    }
}
