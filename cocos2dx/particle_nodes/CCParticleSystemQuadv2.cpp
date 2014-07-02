
#include "CCParticleSystemQuadv2.h"

USING_NS_CC;

CCParticleSystemQuadv2::CCParticleSystemQuadv2()
{
    
}

CCParticleSystemQuadv2::~CCParticleSystemQuadv2()
{

}

CCParticleSystemQuadv2 * CCParticleSystemQuadv2::create() {
    CCParticleSystemQuadv2 * pRet = new CCParticleSystemQuadv2();
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

bool CCParticleSystemQuadv2::init() {
    CCParticleSystemQuad::setPositionType(kCCPositionTypeFree);

    return CCParticleSystemQuad::init();
}


void CCParticleSystemQuadv2::setPositionType(tCCPositionType posType) {
    CCParticleSystemQuad::setPositionType(posType);
}

tCCPositionType CCParticleSystemQuadv2::getPositionType() {
    return CCParticleSystemQuad::getPositionType();
}
