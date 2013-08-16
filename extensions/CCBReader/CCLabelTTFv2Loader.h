#ifndef _CCB_CCLABELTTFV2LOADER_H_
#define _CCB_CCLABELTTFV2LOADER_H_

#include "CCLabelTTFLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCLabelTTFv2Loader : public CCLabelTTFLoader {
    public:
        virtual ~CCLabelTTFv2Loader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCLabelTTFv2Loader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCLabelTTFv2);

        virtual void onHandlePropTypeCheck(CCNode * pNode, CCNode * pParent, const char* pPropertyName, bool pCheck, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
