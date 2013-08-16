#include "CCLabelTTFv2Loader.h"

#define PROPERTY_FIT_HORIZONTALLY "shrink"

NS_CC_EXT_BEGIN

void CCLabelTTFv2Loader::onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char * pPropertyName, bool pCheck, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_FIT_HORIZONTALLY) == 0) {
		((CCLabelTTFv2*)pNode)->setShrink(true);
    }
}

NS_CC_EXT_END