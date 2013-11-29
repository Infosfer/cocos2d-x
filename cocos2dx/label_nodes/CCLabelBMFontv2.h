#pragma once

#include "cocos2d.h"

NS_CC_BEGIN

class CC_DLL CCLabelBMFontv2 : public CCNodeRGBA
{
public:
	CCLabelBMFontv2();
	virtual ~CCLabelBMFontv2();

	static CCLabelBMFontv2 *	create();

	bool						init();
	void						setString(const char *newString);
	const char*					getString();

	void						setHorizontalAlignment(CCTextAlignment alignment);
	void						setVerticalAlignment(CCVerticalTextAlignment alignment);
	void						setShrink(bool value);
	void						setFontScale(float fontSc);


	// CCNode
	virtual void				setContentSize(const CCSize &size);
	virtual void				setAnchorPoint(const CCPoint& point);
	virtual void				setScale(float scale);
	virtual void				setScaleX(float fScaleX);
	virtual void				setScaleY(float fScaleY);

	// CCRGBAProtocol
	virtual const ccColor3B&	getColor(void);
	virtual void				setColor(const ccColor3B& color);
	virtual GLubyte				getOpacity();
	virtual void				setOpacity(GLubyte opacity);
    virtual const ccColor3B&	getDisplayedColor(void);
    virtual GLubyte				getDisplayedOpacity(void);
    virtual void				setOpacityModifyRGB(bool bValue);
	virtual bool				isOpacityModifyRGB(void);
    virtual bool				isCascadeColorEnabled(void);
    virtual void				setCascadeColorEnabled(bool cascadeColorEnabled);
    virtual void				updateDisplayedColor(const ccColor3B& color);
    virtual bool				isCascadeOpacityEnabled(void);
    virtual void				setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    virtual void				updateDisplayedOpacity(GLubyte opacity);

	// CCLabelProtocol
	void						setFntFile(const char *fntFile);
	const char*					getFntFile();
	void						setBlendFunc(ccBlendFunc bldFunc);
	ccBlendFunc					getBlendFunc();

private:
	void						refresh();
	void						updateTexture();

private:
	CCString*					_string;
	CCLabelBMFont*				_helperLabel;
	CCTextAlignment				_horizontalAlignment;
	CCVerticalTextAlignment		_verticalAlignment;
	bool						_shrink;
	float						_shrinkScale;
	float						_fontScale;
};

NS_CC_END
