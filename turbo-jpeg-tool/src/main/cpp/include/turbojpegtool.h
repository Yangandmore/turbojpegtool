//
// Created by 杨世衢 on 2020/7/14.
//

#ifndef LIBJPEGTURBODEMO_TURBOJPEGTOOL_H
#define LIBJPEGTURBODEMO_TURBOJPEGTOOL_H

#include "turbojpeg.h"

class Pic {
public:
    unsigned char **pic_data;
    long pic_len;
    Pic(unsigned char **pic_data, long pic_len);
    ~Pic();
};

class Tool {
public:
    Tool();
    ~Tool();
    Pic *yuvToJpeg(unsigned char *yuv, int yuv_size, int width, int height, TJSAMP samp_type, int quality, int flag);
    Pic *rgbToJpeg(unsigned char *rgb, int rgb_size, int width, int height, TJPF pix_format, TJSAMP jpeg_samp_type, int quality, int flag);
    unsigned char *jpegToYuv(unsigned char *jpeg, int jpeg_size, int width, int height, int yuv_size, TJSAMP samp_type, int flag);
    unsigned char *jpegToRgb(unsigned char *jpeg, int jpeg_size, int width, int height, int rgb_size, TJPF pix_format, int flag);
private:
    // 压缩器
    tjhandle tjCompress = NULL;
    // 解压器
    tjhandle tjDecompress = NULL;
    // 转换器
    tjhandle tjTransform = NULL;
};
Tool *tool;

#endif //LIBJPEGTURBODEMO_TURBOJPEGTOOL_H
