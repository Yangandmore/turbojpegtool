package com.jpeg.turbo.tool;

public class TurboJpegTool {

    static {
        System.loadLibrary("turbojpegtool");
    }

    public static final int FLAG_FASTUPSAMPLE = 256;
    public static final int FLAG_FASTDCT = 2048;
    public static final int FLAG_ACCURATEDCT = 4096;

    public static final int SAMP_I444 = 0;
    public static final int SAMP_I422 = 1;
    public static final int SAMP_I420 = 2;
    public static final int SAMP_GRAY = 3;
    public static final int SAMP_I440 = 4;
    public static final int SAMP_I411 = 5;

    public static final int FORMAT_RGB = 0;
    public static final int FORMAT_BGR = 1;
    public static final int FORMAT_RGBX = 2;
    public static final int FORMAT_BGRX = 3;
    public static final int FORMAT_XBGR = 4;
    public static final int FORMAT_XRGB = 5;
    public static final int FORMAT_GRAY = 6;
    public static final int FORMAT_RGBA = 7;
    public static final int FORMAT_BGRA = 8;
    public static final int FORMAT_ABGR = 9;
    public static final int FORMAT_ARGB = 10;
    public static final int FORMAT_CMYK = 11;


    public native void init();

    /**
     *
     * @param yuv 原数据
     * @param yuvSize 原数据大小
     * @param width 图片宽
     * @param height 图片高
     * @param sampType: I444-0, I422-1, I420-2, Gray-3, I440-4, I411-5
     * @param quality: 1-100（差-优）
     * @param flag: 0, 256, 2048, 4096
     * @return
     */
    public native byte[] yuvToJpeg(byte[] yuv, int yuvSize, int width, int height, int sampType, int quality, int flag);

    /**
     *
     * @param rgb 原数据
     * @param rgbSize 原数据大小
     * @param width 图片宽
     * @param height 图片高
     * @param pixFormat 原数据格式
     * @param jpegSampType  I444-0, I422-1, I420-2, Gray-3, I440-4, I411-5
     * @param quality 1-100（差-优）
     * @param flag 0, 256, 2048, 4096
     * @return
     */
    public native byte[] rgbToJpeg(byte[] rgb, int rgbSize, int width, int height, int pixFormat, int jpegSampType, int quality, int flag);

    public native byte[] jpegToYuv(byte[] jpeg, int jpegSize, int width, int height, int yuv_size, int sampType, int flag);

    public native byte[] jpegToRgb(byte[] jpeg, int jpegSize, int width, int height, int rgb_size, int pixFormat, int flag);

    public native void close();
}
