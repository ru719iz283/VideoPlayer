#include "videoplayer.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
}
#include <stdio.h>
#include<iostream>
using namespace std;
VideoPlayer::VideoPlayer()
{

}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::StartPlay(QString VideoUrl)
{
    Url = VideoUrl;
    this->start();
    PlayVideo = true;

}

void VideoPlayer::StopPlay()
{
    PlayVideo = false;
    GopCount = 0;
    return;
}

void VideoPlayer::run()
{
    AVFormatContext *pFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodecContext *pAudioCodecCtx;
    AVCodec *pCodec;
    AVFrame *pFrame, *pFrameRGB;
    AVPacket *packet;
    uint8_t *out_buffer;

    static struct SwsContext *img_convert_ctx;

    int VideoStream, i, numBytes;
    int AudioStream;
    int ret, got_picture;

    avformat_network_init();
    av_register_all();


    //Allocate an AVFormatContext.
    pFormatCtx = avformat_alloc_context();

    AVDictionary *avdic=NULL;
    char option_key[]="rtsp_transport";
    char option_value[]="tcp";
    av_dict_set(&avdic,option_key,option_value,0);
    char option_key2[]="max_delay";
    char option_value2[]="100";
    av_dict_set(&avdic,option_key2,option_value2,0);

    if (avformat_open_input(&pFormatCtx, Url.toLatin1().data(), NULL, &avdic) != 0) {
        printf("can't open the file. \n");
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        printf("Could't find stream infomation.\n");
        return;
    }

    VideoStream = -1;
    AudioStream = -1;

    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            VideoStream = i;
        }
    }
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            AudioStream = i;
        }
    }


    if(AudioStream != -1) {
        pAudioCodecCtx = pFormatCtx->streams[AudioStream]->codec;
        emit sig_GetAudioCodec(pAudioCodecCtx->codec_id);
    }

    if (VideoStream == -1) {
        printf("Didn't find a video stream.\n");
        return;
    }


    pCodecCtx = pFormatCtx->streams[VideoStream]->codec;
    emit sig_GetVideoCodec(pCodecCtx->codec_id);
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    pCodecCtx->bit_rate=0;
    pCodecCtx->time_base.num=1;
    pCodecCtx->time_base.den=10;
    pCodecCtx->frame_number=1;

    if (pCodec == NULL) {
        printf("Codec not found.\n");
        return;
    }

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        printf("Could not open codec.\n");
        return;
    }

    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();

    // Convert YUV to RGB32
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
            pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
            AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

    numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, pCodecCtx->width,pCodecCtx->height);

    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB32,
            pCodecCtx->width, pCodecCtx->height);

    int y_size = pCodecCtx->width * pCodecCtx->height;

    packet = (AVPacket *) malloc(sizeof(AVPacket));
    av_new_packet(packet, y_size);

    while (1)
    {
        if(!PlayVideo) { break; }
        if(av_read_frame(pFormatCtx, packet) < 0) { break; } // end of the video


        if (packet->stream_index == VideoStream) {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);

            if (ret < 0) {
                printf("Decode video error.\n");
                break;
            }

            if (got_picture) {
                if(pFrame->key_frame && GopCount){
                    GopCount++;
                    emit sig_GetData(GopCount);
                    GopCount = 0;
                } else {
                    GopCount++;
                }
                sws_scale(img_convert_ctx,
                        (uint8_t const * const *) pFrame->data,
                        pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                        pFrameRGB->linesize);

                QImage tmpImg((uchar *)out_buffer,pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB32);
                emit sig_GetOneFrame(tmpImg);
            }
        }
        av_free_packet(packet);
    }
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}
