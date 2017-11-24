package com.channelst.myndk;

import android.util.Log;

/**
 * Created by Luojingjing on 2017/11/23.
 */

public class MyNdk {
    static {
        System.loadLibrary("MyLibrary");
    }

    public static native String getString();
}
