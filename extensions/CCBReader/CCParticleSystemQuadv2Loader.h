#ifndef _CCB_CCPARTICLESYSTEMQUADV2LOADER_H_
#define _CCB_CCPARTICLESYSTEMQUADV2LOADER_H_

#include "CCParticleSystemQuadLoader.h"

NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class CCParticleSystemQuadv2Loader : public CCParticleSystemQuadLoader {
    public:
        virtual ~CCParticleSystemQuadv2Loader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCParticleSystemQuadv2Loader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CCParticleSystemQuadv2);

        virtual void onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader);
};

NS_CC_EXT_END

#endif
