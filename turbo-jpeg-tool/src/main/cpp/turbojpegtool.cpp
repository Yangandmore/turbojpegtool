//
// Created by 杨世衢 on 2020/7/14.
//

#include <jni.h>
#include <turbojpegtool.h>
#include <malloc.h>
#include <string.h>


extern "C"
JNIEXPORT void JNICALL
Java_com_jpeg_turbo_tool_TurboJpegTool_init(JNIEnv *env, jobject jobj) {
    if (tool == NULL) {
        tool = new Tool();
    }
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jpeg_turbo_tool_TurboJpegTool_yuvToJpeg(JNIEnv *env, jobject thiz, jbyteArray yuv,
                                                 jint yuv_size, jint width, jint height, int samp_type,
                                                 jint quality, jint flag) {
    if (tool == NULL) {
        return NULL;
    }
    // 获取原数据
    unsigned char* yuv_data = static_cast<unsigned char *>(malloc(yuv_size));
    env->GetByteArrayRegion(yuv, 0, yuv_size, reinterpret_cast<jbyte *>(yuv_data));

    Pic *pic = tool->yuvToJpeg(yuv_data, yuv_size, width, height, (TJSAMP)samp_type, quality, flag);
    if (pic == NULL) {
        delete yuv_data;
        yuv_data = NULL;
        return NULL;
    }
    jbyteArray jpeg = env->NewByteArray(pic->pic_len);
    unsigned char* jpeg_data = static_cast<unsigned char *>(env->GetPrimitiveArrayCritical(jpeg, 0));

    // 拷贝数据
    memcpy(jpeg_data, *pic->pic_data, pic->pic_len);

    delete pic;
    pic = NULL;
    delete yuv_data;
    yuv_data = NULL;

    env->ReleasePrimitiveArrayCritical(jpeg, jpeg_data, 0);
    return jpeg;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jpeg_turbo_tool_TurboJpegTool_rgbToJpeg(JNIEnv *env, jobject thiz, jbyteArray rgb,
                                                 jint rgb_size, jint width, jint height,
                                                 jint pixFormat, jint jpeg_samp_type, jint quality,
                                                 jint flag) {
    if (tool == NULL) {
        return NULL;
    }
    // 获取原数据
    unsigned char* rgb_data = static_cast<unsigned char *>(malloc(rgb_size));
    env->GetByteArrayRegion(rgb, 0, rgb_size, reinterpret_cast<jbyte *>(rgb_data));

    Pic *pic = tool->rgbToJpeg(rgb_data, rgb_size, width, height, (TJPF)pixFormat, (TJSAMP)jpeg_samp_type, quality, flag);
    if (pic == NULL) {
        delete rgb_data;
        rgb_data = NULL;
        return NULL;
    }
    jbyteArray jpeg = env->NewByteArray(pic->pic_len);
    unsigned char* jpeg_data = static_cast<unsigned char *>(env->GetPrimitiveArrayCritical(jpeg, 0));

    // 拷贝数据
    memcpy(jpeg_data, *pic->pic_data, pic->pic_len);

    delete pic;
    pic = NULL;
    delete rgb_data;
    rgb_data = NULL;

    env->ReleasePrimitiveArrayCritical(jpeg, jpeg_data, 0);
    return jpeg;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jpeg_turbo_tool_TurboJpegTool_jpegToYuv(JNIEnv *env, jobject thiz, jbyteArray jpeg,
                                                 jint jpeg_size, jint width, jint height,
                                                 jint yuv_size, jint samp_type, jint flag) {
    if (tool == NULL) {
        return NULL;
    }

    // 获取原数据
    unsigned char* jpeg_data = static_cast<unsigned char *>(malloc(jpeg_size));
    env->GetByteArrayRegion(jpeg, 0, jpeg_size, reinterpret_cast<jbyte *>(jpeg_data));

    unsigned char *yuv_data = tool->jpegToYuv(jpeg_data, jpeg_size, width, height, yuv_size, (TJSAMP)samp_type, flag);
    if (yuv_data == NULL) {
        return NULL;
    }
    jbyteArray yuv = env->NewByteArray(yuv_size);
    unsigned char* yuv_data_j = static_cast<unsigned char *>(env->GetPrimitiveArrayCritical(yuv, 0));

    // 拷贝数据
    memcpy(yuv_data_j, yuv_data, yuv_size);

    delete yuv_data;
    yuv_data = NULL;

    env->ReleasePrimitiveArrayCritical(yuv, yuv_data_j, 0);

    return yuv;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jpeg_turbo_tool_TurboJpegTool_jpegToRgb(JNIEnv *env, jobject thiz, jbyteArray jpeg,
                                                 jint jpeg_size, jint width, jint height,
                                                 jint rgb_size, jint pix_format, jint flag) {
    if (tool == NULL) {
        return NULL;
    }

    // 获取原数据
    unsigned char* jpeg_data = static_cast<unsigned char *>(malloc(jpeg_size));
    env->GetByteArrayRegion(jpeg, 0, jpeg_size, reinterpret_cast<jbyte *>(jpeg_data));

    unsigned char *rgb_data = tool->jpegToRgb(jpeg_data, jpeg_size, width, height, rgb_size, (TJPF)pix_format, flag);

    if (rgb_data == NULL) {
        return NULL;
    }
    jbyteArray rgb = env->NewByteArray(rgb_size);
    unsigned char* rgb_data_j = static_cast<unsigned char *>(env->GetPrimitiveArrayCritical(rgb, 0));

    // 拷贝数据
    memcpy(rgb_data_j, rgb_data, rgb_size);

    delete rgb_data;
    rgb_data = NULL;

    env->ReleasePrimitiveArrayCritical(rgb, rgb_data_j, 0);

    return rgb;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jpeg_turbo_tool_TurboJpegTool_close(JNIEnv *env, jobject thiz) {
    if (tool != NULL) {
        delete tool;
        tool = NULL;
    }
}

Pic::Pic(unsigned char **pic_data, long pic_len) {
    Pic::pic_data = pic_data;
    Pic::pic_len = pic_len;
}

Pic::~Pic() {
    free(*pic_data);
    free(pic_data);
    pic_data = NULL;
    pic_len = NULL;
}

Tool::Tool() {
    if (tjCompress == NULL) {
        tjCompress = tjInitCompress();
    }
    if (tjDecompress == NULL) {
        tjDecompress = tjInitDecompress();
    }
    if (tjTransform == NULL) {
        tjTransform = tjInitTransform();
    }
}

Tool::~Tool() {
    if (tjCompress != NULL) {
        tjDestroy(tjCompress);
        tjCompress = NULL;
    }
    if (tjDecompress != NULL) {
        tjDestroy(tjDecompress);
        tjDecompress = NULL;
    }
    if (tjTransform != NULL) {
        tjDestroy(tjTransform);
        tjTransform = NULL;
    }
}

Pic *Tool::yuvToJpeg(unsigned char *yuv, int yuv_size, int width, int height, TJSAMP samp_type, int quality, int flag) {

    int pad = 1;
    while (1) {
        if (yuv_size == tjBufSizeYUV2(width, pad, height, samp_type)) {
            break;
        } else {
            pad <<= 1;
        }
    }
    // 创建jpeg数据指针
    unsigned char **p_jpeg_data = static_cast<unsigned char **>(malloc(yuv_size));

    // jpeg大小
    u_long* p_jpeg_size = static_cast<u_long *>(malloc(sizeof(u_long)));

    // 开始压缩转码
    int ret = tjCompressFromYUV(tjCompress, yuv, width, pad, height, samp_type, p_jpeg_data, p_jpeg_size, quality, flag);

    if (ret != 0) {
        // 释放内存
        delete p_jpeg_size;
        p_jpeg_size = NULL;
        return NULL;
    }

    // 获取数据
    long jpeg_size = *p_jpeg_size;
    Pic *pic = new Pic(p_jpeg_data, jpeg_size);

    // 释放内存
    delete p_jpeg_size;
    p_jpeg_size = NULL;

    return pic;
}

Pic *Tool::rgbToJpeg(unsigned char *rgb, int rgb_size, int width, int height, TJPF pix_format, TJSAMP jpeg_samp_type,
                     int quality, int flag) {
    // 创建jpeg数据指针
    unsigned char **p_jpeg_data = static_cast<unsigned char **>(malloc(rgb_size));

    // jpeg大小
    u_long* p_jpeg_size = static_cast<u_long *>(malloc(sizeof(u_long)));

    // 开始压缩转码
    int ret = tjCompress2(tjCompress , rgb, width, width * tjPixelSize[pix_format], height, pix_format, p_jpeg_data, p_jpeg_size, jpeg_samp_type, quality, flag);

    if (ret != 0) {
        // 释放内存
        delete p_jpeg_data;
        p_jpeg_data = NULL;
        delete p_jpeg_size;
        p_jpeg_size = NULL;
        return NULL;
    }

    // 获取数据
    long jpeg_size = *p_jpeg_size;
    Pic *pic = new Pic(p_jpeg_data, jpeg_size);

    // 释放内存
    delete p_jpeg_size;
    p_jpeg_size = NULL;

    return pic;
}

unsigned char *Tool::jpegToYuv(unsigned char *jpeg, int jpeg_size, int width, int height, int yuv_size, TJSAMP samp_type, int flag) {
    int pad = 1;
    while (1) {
        if (yuv_size == tjBufSizeYUV2(width, pad, height, samp_type)) {
            break;
        } else {
            pad <<= 1;
        }
    }

    unsigned char * I420 = static_cast<unsigned char *>(malloc(yuv_size));

    int ret = tjDecompressToYUV2(tjDecompress, jpeg, jpeg_size, I420, width, pad, height, flag);

    if (ret != 0) {
        // 释放内存
        delete I420;
        I420 = NULL;
        return NULL;
    }

    return I420;
}

unsigned char *Tool::jpegToRgb(unsigned char *jpeg, int jpeg_size, int width, int height, int rgb_size,
                               TJPF pix_format, int flag) {

    unsigned char * rgb = static_cast<unsigned char *>(malloc(rgb_size));

    int ret = tjDecompress2(tjDecompress, jpeg, jpeg_size, rgb, width, width * tjPixelSize[pix_format], height, pix_format, flag);

    if (ret != 0) {
        // 释放内存
        delete rgb;
        rgb = NULL;
        return NULL;
    }

    return rgb;
}