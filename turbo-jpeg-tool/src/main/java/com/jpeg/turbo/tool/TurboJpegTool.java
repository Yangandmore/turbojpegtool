package com.jpeg.turbo.tool;

public class TurboJpegTool {

    static {
        System.loadLibrary("turbojpegtool");
    }

    public native int init();
}
