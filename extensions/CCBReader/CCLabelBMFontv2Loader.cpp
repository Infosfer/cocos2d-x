#include "CCLabelBMFontv2Loader.h"

NS_CC_EXT_BEGIN

#define PROPERTY_COLOR "color"
#define PROPERTY_OPACITY "opacity"
#define PROPERTY_BLENDFUNC "blendFunc"
#define PROPERTY_FNTFILE "fntFile"
#define PROPERTY_STRING "string"
#define PROPERTY_FONT_SCALE "fontScale"
#define PROPERTY_HORIZONTALALIGNMENT "horizontalAlignment"
#define PROPERTY_VERTICALALIGNMENT "verticalAlignment"
#define PROPERTY_SHRINK "shrink"

void CCLabelBMFontv2Loader::onHandlePropTypeColor3(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccColor3B pCCColor3B, CCBReader * pCCBReader) {
		if(strcmp(pPropertyName, PROPERTY_COLOR) == 0) {
			((CCLabelBMFontv2 *)pNode)->setColor(pCCColor3B);
		} else {
			CCNodeLoader::onHandlePropTypeColor3(pNode, pParent, pPropertyName, pCCColor3B, pCCBReader);
		}
}

void CCLabelBMFontv2Loader::onHandlePropTypeByte(CCNode * pNode, CCNode * pParent, const char * pPropertyName, unsigned char pByte, CCBReader * pCCBReader) {
	if(strcmp(pPropertyName, PROPERTY_OPACITY) == 0) {
		((CCLabelBMFontv2 *)pNode)->setOpacity(pByte);
	} else {
		CCNodeLoader::onHandlePropTypeByte(pNode, pParent, pPropertyName, pByte, pCCBReader);
	}
}

void CCLabelBMFontv2Loader::onHandlePropTypeBlendFunc(CCNode * pNode, CCNode * pParent, const char * pPropertyName, ccBlendFunc pCCBlendFunc, CCBReader * pCCBReader) {
	if(strcmp(pPropertyName, PROPERTY_BLENDFUNC) == 0) {
		((CCLabelBMFontv2 *)pNode)->setBlendFunc(pCCBlendFunc);
	} else {
		CCNodeLoader::onHandlePropTypeBlendFunc(pNode, pParent, pPropertyName, pCCBlendFunc, pCCBReader);
	}
}

void CCLabelBMFontv2Loader::onHandlePropTypeFntFile(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pFntFile, CCBReader * pCCBReader) {
	if(strcmp(pPropertyName, PROPERTY_FNTFILE) == 0) {
		((CCLabelBMFontv2 *)pNode)->setFntFile(pFntFile);
	} else {
		CCNodeLoader::onHandlePropTypeFntFile(pNode, pParent, pPropertyName, pFntFile, pCCBReader);
	}
}

void CCLabelBMFontv2Loader::onHandlePropTypeText(CCNode * pNode, CCNode * pParent, const char * pPropertyName, const char* pText, CCBReader * pCCBReader) {
	if(strcmp(pPropertyName, PROPERTY_STRING) == 0) {
		((CCLabelBMFontv2 *)pNode)->setString(pText);
	} else {
		CCNodeLoader::onHandlePropTypeText(pNode, pParent, pPropertyName, pText, pCCBReader);
	}
}

void CCLabelBMFontv2Loader::onHandlePropTypeFloat(CCNode * pNode, CCNode * pParent, const char* pPropertyName, float pFloat, CCBReader * pCCBReader) {
	if(strcmp(pPropertyName, PROPERTY_FONT_SCALE) == 0) {
		((CCLabelBMFontv2 *)pNode)->setFontScale(pFloat);
	} else {
		CCNodeLoader::onHandlePropTypeFloat(pNode, pParent, pPropertyName, pFloat, pCCBReader);
	}
}

void CCLabelBMFontv2Loader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
		if(strcmp(pPropertyName, PROPERTY_HORIZONTALALIGNMENT) == 0) {
			((CCLabelBMFontv2 *)pNode)->setHorizontalAlignment(CCTextAlignment(pIntegerLabeled));
		} else if(strcmp(pPropertyName, PROPERTY_VERTICALALIGNMENT) == 0) {
			((CCLabelBMFontv2 *)pNode)->setVerticalAlignment(CCVerticalTextAlignment(pIntegerLabeled));
		} else {
			CCNodeLoader::onHandlePropTypeFloatScale(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
		}
}

void CCLabelBMFontv2Loader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
	if(strcmp(pPropertyName, PROPERTY_SHRINK) == 0) {
		((CCLabelBMFontv2*)pNode)->setShrink(true);
	}
}


NS_CC_EXT_END