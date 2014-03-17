/****************************************************************************
Copyright (c) 2011 Jirka Fajfr for cocos2d-x
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

#ifndef __CCETCTEXTURE_H__
#define __CCETCTEXTURE_H__

#include "CCStdC.h"
#include "CCGL.h"
#include "cocoa/CCObject.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN

struct CCETCMipmap {
    unsigned char *address;
    unsigned int len;
};

class CCTextureETC : public CCObject
{
public:
    CCTextureETC();
    virtual ~CCTextureETC();

    /** initializes a CCTextureETC with a path */
    bool initWithContentsOfFile(const char* path);

    /** creates and initializes a CCTextureETC with a path */
    static CCTextureETC* create(const char* path);
    
    // properties 
    
    /** texture id name */
    inline unsigned int getName() { return m_uName; }
    /** texture width */
    inline unsigned int getWidth() { return m_uWidth; }
    /** texture height */
    inline unsigned int getHeight() { return m_uHeight; }
    /** whether or not the texture has alpha */
    inline bool hasAlpha() { return m_bHasAlpha; }
    inline bool isRetainName() { return m_bRetainName; }
    inline void setRetainName(bool retainName) { m_bRetainName = retainName; }

private:
    bool unpackETCData(unsigned char* data, unsigned int len);
    bool createGLTexture();
    
protected:
    struct CCETCMipmap m_asMipmaps[1];
    
    unsigned int m_uWidth, m_uHeight;
    GLuint m_uName;
    bool m_bHasAlpha;
    
    // cocos2d integration
    bool m_bRetainName;
};

NS_CC_END

#endif