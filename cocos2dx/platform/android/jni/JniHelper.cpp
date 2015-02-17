/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "JniHelper.h"
#include <android/log.h>
#include <string.h>

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif

#define JAVAVM    cocos2d::JniHelper::getJavaVM()

using namespace std;

extern "C"
{
    //////////////////////////////////////////////////////////////////////////
    // java vm helper function
    //////////////////////////////////////////////////////////////////////////

    static pthread_key_t s_threadKey;

    static void detach_current_thread (void *env) {
        JAVAVM->DetachCurrentThread();
    }

    static bool getEnv_Standard(JNIEnv **env) {
        int status = JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4);
        if(status < 0) {
            status = JAVAVM->AttachCurrentThread(env, NULL);
            if(status < 0) {
                return false;
            }
        }
        return true;
    }

    static bool getEnv_G900F(JNIEnv **env) {
        bool bRet = false;

        switch(JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4))
        {
        case JNI_OK:
            bRet = true;
            break;
        case JNI_EDETACHED:
            pthread_key_create (&s_threadKey, detach_current_thread);
            if (JAVAVM->AttachCurrentThread(env, 0) < 0)
            {
                break;
            }
            if (pthread_getspecific(s_threadKey) == NULL)
                pthread_setspecific(s_threadKey, env);
            bRet = true;
            break;
        default:
            LOGD("%s", "Failed to get the environment using GetEnv()");
            break;
        }

        return bRet;
    }

    static bool getEnv(JNIEnv **env) {
        bool bRet = getEnv_G900F(env);
        if ((*env)->ExceptionOccurred()) { (*env)->ExceptionClear(); }

        if (!bRet) {
            bRet = getEnv_Standard(env);
            if ((*env)->ExceptionOccurred()) { (*env)->ExceptionClear(); }
        }

        return bRet;
    }

    static jclass getClassID_Standard_(const char *className, JNIEnv *env) {
    	if (!env) {
   	       if (!getEnv(&env)) {
        	   return NULL;
    	   }
	    }

    	return static_cast<jclass>(env->CallObjectMethod(cocos2d::JniHelper::getJavaVMClassLoader(), cocos2d::JniHelper::getJavaVMFindClassMethod(), env->NewStringUTF(className)));
    }

    static jclass getClassID_G900F_(const char *className, JNIEnv *env)
    {
        JNIEnv *pEnv = env;
        jclass ret = 0;

        do
        {
            if (! pEnv)
            {
                if (! getEnv(&pEnv))
                {
                    break;
                }
            }

            ret = pEnv->FindClass(className);
            if (! ret)
            {
                 LOGD("Failed to find class of %s", className);
                break;
            }
        } while (0);

        return ret;
    }

    static jclass getClassID_(const char *className, JNIEnv *env) {
        jclass cls = getClassID_G900F_(className, env);
        if (env->ExceptionOccurred()) { env->ExceptionClear(); }

        if (!cls) {
            cls = getClassID_Standard_(className, env);
            if (env->ExceptionOccurred()) { env->ExceptionClear(); }
        }

        return cls;
    }

    static bool getStaticMethodInfo_(cocos2d::JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;

        do
        {
            if (!getEnv(&pEnv))
            {
                break;
            }

            jclass classID = getClassID_(className, pEnv);

            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find static method id of %s", methodName);
                break;
            }

            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;

            bRet = true;
        } while (0);

        return bRet;
    }

    static bool getMethodInfo_(cocos2d::JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;

        do
        {
            if (!getEnv(&pEnv))
            {
                break;
            }

            jclass classID = getClassID_(className, pEnv);

            methodID = pEnv->GetMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find method id of %s", methodName);
                break;
            }

            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;

            bRet = true;
        } while (0);

        return bRet;
    }

    static string jstring2string_(jstring jstr)
    {
        if (jstr == NULL)
        {
            return "";
        }

        JNIEnv *env = 0;

        if (!getEnv(&env))
        {
            return 0;
        }

        const char* chars = env->GetStringUTFChars(jstr, NULL);
        string ret(chars);
        env->ReleaseStringUTFChars(jstr, chars);

        return ret;
    }
}

NS_CC_BEGIN

JavaVM* JniHelper::m_psJavaVM = NULL;
jobject JniHelper::m_classLoader = NULL;
jmethodID JniHelper::m_findClassMethod = NULL;

JavaVM* JniHelper::getJavaVM()
{
    return m_psJavaVM;
}

void JniHelper::setJavaVM(JavaVM *javaVM) {
    m_psJavaVM = javaVM;

    JNIEnv *env;

    getEnv(&env);

    //replace with one of your classes in the line below
    auto randomClass = env->FindClass("org/cocos2dx/lib/Cocos2dxHelper");
    auto classClass = env->FindClass("java/lang/Class");
    auto classLoaderClass = env->FindClass("java/lang/ClassLoader");
    auto getClassLoaderMethod = env->GetMethodID(classClass, "getClassLoader", "()Ljava/lang/ClassLoader;");

    setJavaVMClassLoader(env->CallObjectMethod(randomClass, getClassLoaderMethod));
    setJavaVMFindClassMethod(env->GetMethodID(classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;"));
}

jclass JniHelper::getClassID(const char *className, JNIEnv *env) {
    return getClassID_(className, env);
}

bool JniHelper::getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode) {
    return getStaticMethodInfo_(methodinfo, className, methodName, paramCode);
}

bool JniHelper::getMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode) {
    return getMethodInfo_(methodinfo, className, methodName, paramCode);
}

string JniHelper::jstring2string(jstring str) {
    return jstring2string_(str);
}

jmethodID JniHelper::getJavaVMFindClassMethod() {
	return m_findClassMethod;
}

void JniHelper::setJavaVMFindClassMethod(jmethodID findClassMethod) {
	m_findClassMethod = findClassMethod;
}

void JniHelper::setJavaVMClassLoader(jobject classLoader) {
    JNIEnv *pEnv = 0;
    getEnv(&pEnv);
	m_classLoader = pEnv->NewGlobalRef(classLoader);
}

jobject JniHelper::getJavaVMClassLoader() {
	return m_classLoader;
}

NS_CC_END
