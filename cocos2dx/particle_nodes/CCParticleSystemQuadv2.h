#pragma once

#include "cocos2d.h"

USING_NS_CC;

/** CCParticleSystemQuadv2 is a subclass of CCParticleSystemQuad */

class CC_DLL CCParticleSystemQuadv2 : public CCParticleSystemQuad
{
public:
	CCParticleSystemQuadv2();
	virtual ~CCParticleSystemQuadv2();

	static CCParticleSystemQuadv2 *	create();

	void			setPositionType(tCCPositionType posType);
	tCCPositionType getPositionType();

protected:
	bool	init();
};


