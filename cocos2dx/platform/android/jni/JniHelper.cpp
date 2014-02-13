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
    static bool getStaticMethodInfo_(cocos2d::JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;

        do 
        {
            if (!cocos2d::JniHelper::getEnv(&pEnv))
            {
                break;
            }

            jclass classID = cocos2d::JniHelper::getClassID(className, pEnv);
            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
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
            if (!cocos2d::JniHelper::getEnv(&pEnv))
            {
                break;
            }

            jclass classID = cocos2d::JniHelper::getClassID(className, pEnv);

            methodID = pEnv->GetMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
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

        if (!cocos2d::JniHelper::getEnv(&env))
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

bool JniHelper::getEnv(JNIEnv **env)
{
    int status = JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4);
    if(status < 0) {    
        status = JAVAVM->AttachCurrentThread(env, NULL);
        if(status < 0) {        
            return false;
        }
    }
    return true;
}

JavaVM* JniHelper::getJavaVM()
{
    return m_psJavaVM;
}

void JniHelper::setJavaVM(JavaVM *javaVM) {
    m_psJavaVM = javaVM;
		
    JNIEnv *env;
	
	getEnv(&env);
	
    //replace with one of your classes in the line below 
    auto randomClass = env->FindClass("org/cocos2dx/lib/Cocos2dxActivity");
    auto classClass = env->FindClass("java/lang/Class");
    auto classLoaderClass = env->FindClass("java/lang/ClassLoader");
    auto getClassLoaderMethod = env->GetMethodID(classClass, "getClassLoader", "()Ljava/lang/ClassLoader;");
											 
    setJavaVMClassLoader(env->CallObjectMethod(randomClass, getClassLoaderMethod));
    setJavaVMFindClassMethod(env->GetMethodID(classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;"));
}

jobject JniHelper::getJavaVMClassLoader() {
	return m_classLoader;
}

void JniHelper::setJavaVMClassLoader(jobject classLoader) {	
    JNIEnv *pEnv = 0;
    cocos2d::JniHelper::getEnv(&pEnv);	
	m_classLoader = pEnv->NewGlobalRef(classLoader);
}

jmethodID JniHelper::getJavaVMFindClassMethod() {
	return m_findClassMethod;
}

void JniHelper::setJavaVMFindClassMethod(jmethodID findClassMethod) {
	m_findClassMethod = findClassMethod;
}

jclass JniHelper::getClassID(const char *className, JNIEnv *env) {	
	if (!env) {
		if (!cocos2d::JniHelper::getEnv(&env)) {
        	return NULL;
    	}	
	}
	
	return static_cast<jclass>(env->CallObjectMethod(getJavaVMClassLoader(), getJavaVMFindClassMethod(), env->NewStringUTF(className)));
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

NS_CC_END
