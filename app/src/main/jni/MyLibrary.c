/* include MyNdk.h */
#include <com_channelst_myndk_MyNdk.h>

JNIEXPORT jstring JNICALL Java_com_channelst_myndk_MyNdk_getString(JNIEnv *env, jobject obj)
{
    return (*env)->NewStringUTF(env, "this string return from c file");
}


