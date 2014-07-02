#pragma once

#include "cocos2d.h"

NS_CC_BEGIN;

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

NS_CC_END;
