package com.example.libjpegturbodemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.Toast;

import com.jpeg.turbo.tool.TurboJpegTool;
import com.yuv.tool.YuvTool;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    private int yuvWidth = 256;
    private int yuvHeight = 256;

    private String path;
    private TurboJpegTool tool;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        path = Environment.getExternalStorageDirectory().getAbsolutePath();

        tool = new TurboJpegTool();
        tool.init();
    }

    @Override
    protected void onDestroy() {
        tool.close();
        super.onDestroy();
    }

    public void i420ToJpegClick(View view) throws IOException {
        // 获取文件数据
        InputStream is = getResources().getAssets().open("yuv/lena_256x256_nv21.yuv");
        byte[] nv21 = new byte[is.available()];
        is.read(nv21);
        is.close();

        // 开始转码
        byte[] i420 = YuvTool.NV21ToI420(nv21, yuvWidth, yuvHeight);

        byte[] jpeg = tool.yuvToJpeg(i420, i420.length, yuvWidth, yuvHeight, TurboJpegTool.SAMP_I420, 100, TurboJpegTool.FLAG_FASTDCT);

        // 成功失败提示
        File file = new File(path, "lena_256x256_jpeg.jpeg");
        FileOutputStream fos = new FileOutputStream(file);
        fos.write(jpeg);
        fos.flush();
        fos.close();

        Toast.makeText(this, "转码成功", Toast.LENGTH_SHORT).show();
    }

    public void rgbToJpegClick(View view) throws IOException {
        // 获取文件数据
        InputStream is = getResources().getAssets().open("rgb/colorbar_640x360_rgb.rgb");
        byte[] argb = new byte[is.available()];
        is.read(argb);
        is.close();

        // 开始转码
        byte[] jpeg = tool.rgbToJpeg(argb, argb.length, 640, 360, TurboJpegTool.FORMAT_RGB, TurboJpegTool.SAMP_I444, 100, TurboJpegTool.FLAG_FASTDCT);

        // 成功失败提示
        File file = new File(path, "lena_256x256_jpeg.jpeg");
        FileOutputStream fos = new FileOutputStream(file);
        fos.write(jpeg);
        fos.flush();
        fos.close();

        Toast.makeText(this, "转码成功", Toast.LENGTH_SHORT).show();
    }

    public void jpegToI420Click(View view) throws IOException {
        // 获取文件数据
        InputStream is = getResources().getAssets().open("jpeg/lena_256x256_jpeg.jpeg");
        byte[] jpeg = new byte[is.available()];
        is.read(jpeg);
        is.close();

        // 开始转码
        byte[] yuv = tool.jpegToYuv(jpeg, jpeg.length, yuvWidth, yuvHeight, (yuvWidth * yuvHeight * 3)/2, TurboJpegTool.SAMP_I420, TurboJpegTool.FLAG_FASTDCT);

        // 成功失败提示
        File file = new File(path, "lena_256x256_i420.yuv");
        FileOutputStream fos = new FileOutputStream(file);
        fos.write(yuv);
        fos.flush();
        fos.close();

        Toast.makeText(this, "转码成功", Toast.LENGTH_SHORT).show();
    }

    public void jpegToRGBClick(View view) throws IOException {

        // 获取文件数据
        InputStream is = getResources().getAssets().open("jpeg/lena_256x256_jpeg.jpeg");
        byte[] jpeg = new byte[is.available()];
        is.read(jpeg);
        is.close();

        // 开始转码
        byte[] rgb = tool.jpegToRgb(jpeg, jpeg.length, yuvWidth, yuvHeight, (yuvWidth * yuvHeight * 3), TurboJpegTool.FORMAT_RGB, TurboJpegTool.FLAG_FASTDCT);

        // 成功失败提示
        File file = new File(path, "lena_256x256_rgb.rgb");
        FileOutputStream fos = new FileOutputStream(file);
        fos.write(rgb);
        fos.flush();
        fos.close();

        Toast.makeText(this, "转码成功", Toast.LENGTH_SHORT).show();
    }

}
