#include "CCTexture2D.h"
#include "CCTextureETC.h"
#include "ccMacros.h"
#include "CCConfiguration.h"
#include "support/ccUtils.h"
#include "CCStdC.h"
#include "etc1.h"
#include "platform/CCFileUtils.h"
#include "shaders/ccGLStateCache.h"
#include <ctype.h>

NS_CC_BEGIN

CCTextureETC::CCTextureETC()
: m_uWidth(0)
, m_uHeight(0)
, m_uName(0)
, m_bHasAlpha(false)
, m_bRetainName(false)
{
}

CCTextureETC::~CCTextureETC()
{
    if (m_uName != 0 && ! m_bRetainName)
    {
        ccGLDeleteTexture(m_uName);
    }
}

bool CCTextureETC::unpackETCData(unsigned char* data, unsigned int len)
{
    const etc1_byte* header = static_cast<const etc1_byte*>(data);
    
    //check the data
    if(!etc1_pkm_is_valid(header))
    {
        return  false;
    }
    
    m_uWidth = etc1_pkm_get_width(header);
    m_uHeight = etc1_pkm_get_height(header);
    
    if( 0 == m_uWidth || 0 == m_uHeight )
    {
        return false;
    }
    
    m_bHasAlpha = false;
    
    m_asMipmaps[0].address = data + ETC_PKM_HEADER_SIZE;
    m_asMipmaps[0].len = len - ETC_PKM_HEADER_SIZE;
	
    return true;
}

bool CCTextureETC::createGLTexture()
{
    unsigned int width = m_uWidth;
    unsigned int height = m_uHeight;
    GLenum err;
    
    if (m_uName != 0)
    {
        ccGLDeleteTexture(m_uName);
    }
    
    glGenTextures(1, &m_uName);
    ccGLBindTexture2D(m_uName);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    CHECK_GL_ERROR_DEBUG(); // clean possible GL error
    
	unsigned char *data = m_asMipmaps[0].address;
	GLsizei datalen = m_asMipmaps[0].len;
    
	glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_ETC1_RGB8_OES, width, height, 0, datalen, data);
    
	err = glGetError();
	if (err != GL_NO_ERROR)
	{
		CCLOG("cocos2d: TextureETC: Error uploading compressed texture. glError: 0x%04X", err);
		return false;
	}
        
    return true;
}


bool CCTextureETC::initWithContentsOfFile(const char* path, bool isCreateGLTexture)
{
    etcdata = NULL;
    int etclen = 0;
    
    etcdata = CCFileUtils::sharedFileUtils()->getFileData(path, "rb", (unsigned long *)(&etclen));
    
    if (etclen < 0)
    {
        this->release();
        return false;
    }
    
    m_uName = 0;
    m_uWidth = m_uHeight = 0;
    m_bHasAlpha = false;

    m_bRetainName = false; // cocos2d integration

    if (! (unpackETCData(etcdata, etclen) && (!isCreateGLTexture || (isCreateGLTexture && createGLTexture()) ) )
    {
        CC_SAFE_DELETE_ARRAY(etcdata);
        this->release();
        return false;
    }

    if (isCreateGLTexture) {
        CC_SAFE_DELETE_ARRAY(etcdata);
    }
    
    return true;
}

bool CCTexturePVR::createGLTextureAndDeleteETCData() {
    if (!createGLTexture())
    {
        CC_SAFE_DELETE_ARRAY(etcdata);
        this->release();
        return false;
    }

    CC_SAFE_DELETE_ARRAY(etcdata);

    return true;
}

CCTextureETC * CCTextureETC::create(const char* path)
{
    CCTextureETC * pTexture = new CCTextureETC();
    if (pTexture)
    {
        if (pTexture->initWithContentsOfFile(path))
        {
            pTexture->autorelease();
        }
        else
        {
            delete pTexture;
            pTexture = NULL;
        }
    }

    return pTexture;
}

NS_CC_END

