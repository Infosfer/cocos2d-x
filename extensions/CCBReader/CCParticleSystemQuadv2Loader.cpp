#include "CCParticleSystemQuadv2Loader.h"



#define PROPERTY_POSITION_TYPE "positionType"

NS_CC_EXT_BEGIN

void CCParticleSystemQuadv2Loader::onHandlePropTypeIntegerLabeled(CCNode * pNode, CCNode * pParent, const char * pPropertyName, int pIntegerLabeled, CCBReader * pCCBReader) {
    if(strcmp(pPropertyName, PROPERTY_POSITION_TYPE) == 0) {
		((CCParticleSystemQuadv2 *)pNode)->setPositionType(static_cast<tCCPositionType>(pIntegerLabeled));
    } else {
        CCParticleSystemQuadLoader::onHandlePropTypeIntegerLabeled(pNode, pParent, pPropertyName, pIntegerLabeled, pCCBReader);
    }
}

NS_CC_EXT_END