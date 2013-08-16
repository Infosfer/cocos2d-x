/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

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
#include "CCLabelTTFv2.h"

NS_CC_BEGIN

#if CC_USE_LA88_LABELS
#define SHADER_PROGRAM kCCShader_PositionTextureColor
#else
#define SHADER_PROGRAM kCCShader_PositionTextureA8Color
#endif

//
//CCLabelTTFv2
//
CCLabelTTFv2::CCLabelTTFv2()
{
	_defaultFontSize = -1;
}

CCLabelTTFv2::~CCLabelTTFv2()
{
    
}

CCLabelTTFv2 * CCLabelTTFv2::create()
{
	CCLabelTTFv2 * pRet = new CCLabelTTFv2();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CCLabelTTFv2::init()
{
	return this->initWithString("", "Helvetica", 12);
}


void CCLabelTTFv2::setString(const char *string)
{
    this->CCLabelTTF::setString(string);

	if(strcmp(string, "")){
		updateFontSize();
	}
}

void CCLabelTTFv2::setDimensions(const CCSize &dim)
{
	this->CCLabelTTF::setDimensions(dim);
}

float CCLabelTTFv2::getDefaultFontSize() {
	if(_defaultFontSize == -1) {
		_defaultFontSize = getFontSize();
	}
	
	return _defaultFontSize;
}

bool CCLabelTTFv2::getShrink()
{
	return _shrink;
}

void CCLabelTTFv2::setShrink(const bool shrink)
{
	_shrink = shrink;

	updateFontSize();
}

void CCLabelTTFv2::updateFontSize() {
	if (_shrink) {
		float currentFontSize = getDefaultFontSize();
		
		setFontSize(currentFontSize);
		CCSize realTextSize = calculateRealTextSize();

		while (realTextSize.width > getDimensions().width) {
			currentFontSize--;

			if(currentFontSize < 5){
				break;
			}

			setFontSize(currentFontSize);
			realTextSize = calculateRealTextSize();
		}


	}
}

CCSize CCLabelTTFv2::calculateRealTextSize() {
	float dimensionWidth = getDimensions().width;
	float dimensionHeight = getDimensions().height;

	setDimensions(CCSizeZero);

	CCSize realTextSize = CCSizeMake(getContentSize().width, getContentSize().height);

	setDimensions(CCSizeMake(dimensionWidth, dimensionHeight));

	return realTextSize;
}

NS_CC_END
