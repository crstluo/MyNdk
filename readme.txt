jni入门案例
    所谓jni就是java native interface,即java本地接口
    jni就是在java里面调用c的实现
    在java类中定义方法,其方法实现是在c中.

    NDK:即Native Development Kit,也就是本地开发工具包,这个工具包就是用来开发jni的

jni 简易demo实现步骤--使用android studio开发
 1:通过SDK manager-->SDK tools 下载NDK
 2:新建一个安卓项目MyNdk
    右键项目 -> Open Module Setting -> SDK Location ->
     Android NDK Location 中已经配置好了路径之后-> OK -> 等待编译
 3:查看根目录local.properties,
    查看是否有这一句:ndk.dir=D\:\\AndroidSDK\\ndk-bundle(这里的路径是我的ndk路径)
    如果没有则加上

 4:在根目录gradle.properties加入
    android.useDeprecatedNdk=true

 5:在app下面的build.gradle下面加上ndk节点如下图：
    ndk {
       moduleName "MyLibrary"
       abiFilters "armeabi", "armeabi-v7a"
    }
 6:编写jni接口
    创建一个MyNdk的类，
    编写一个native方法并加载库文件 如下:
    public class MyNdk {
        static {
            System.loadLibrary("MyLibrary");
        }

        public static native String getString();
    }
 7:命令生成.h文件
    打开Terminal,使用CD命令进入MyNdk/app/src/main/java目录
    在项目的java目录下,执行 javah -jni com.channelst.myndk.MyNdk
    这是会在java目录中生成一个com.channelst.myndk.MyNdk.h文件

 8:在MyNdk.java文件中,鼠标点击getString这个标红的方法,使用快捷键Alt+Enter组合键
    即会在main目录下生成jni目录,里面有一个MyLibrary.c文件
    我们将第7步生成的com.channelst.myndk.MyNdk.h文件移动到jni目录
    然后修改MyLibrary.c,实现头文件里定义的方法:
    /* include MyNdk.h */
    #include <com_channelst_myndk_MyNdk.h>

    JNIEXPORT jstring JNICALL Java_com_channelst_myndk_MyNdk_getString(JNIEnv *env, jobject obj)
    {
        return (*env)->NewStringUTF(env, "this string return from c file");
    }

 9:我们Build -> Make Project一下，我们会发现在/MyNdk/app/build/intermediates/下面多了一个ndk文件夹.
 我们进入debug/lib,可以看到有armeabi和armeabi-v7a,里面有两个libMyLibrary.so文件
 这样就说明成功生成了库文件了

 10:在MainActivity显示通过jni获取到的字符:
    TextView textView = (TextView) findViewById(R.id.tv);
    String s = MyNdk.getString();
    textView.setText(s);

 11.运行apk,在mainActivity上正确显示了this string return from c file这句,表明jni调用成功

