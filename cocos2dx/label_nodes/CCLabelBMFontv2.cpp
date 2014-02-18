
#include "CCLabelBMFontv2.h"

CCLabelBMFontv2::CCLabelBMFontv2()
{
	
}

CCLabelBMFontv2::~CCLabelBMFontv2()
{
}

CCLabelBMFontv2 * CCLabelBMFontv2::create() {
	CCLabelBMFontv2 * pRet = new CCLabelBMFontv2();
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

bool CCLabelBMFontv2::init() {
	_shrink = false;
	_shrinkScale = 1;
	_fontScale = 1;

	_helperLabel = CCLabelBMFont::create();
	_helperLabel->ignoreAnchorPointForPosition(true);
	_helperLabel->setAnchorPoint(CCPointMake(0,0));
    ccBlendFunc bldFunc = {CC_BLEND_SRC, CC_BLEND_DST};
    _helperLabel->setBlendFunc(bldFunc);
    _helperLabel->setOpacityModifyRGB(true);

	addChild(_helperLabel);

	setHorizontalAlignment(kCCTextAlignmentCenter);
	setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	setAnchorPoint(CCPointMake(0.5, 0.5));
	
	return CCNode::init();
}

void CCLabelBMFontv2::setString(const char *newString) {
	_helperLabel->setString(newString);

	refresh();
}

const char* CCLabelBMFontv2::getString() {
	return _helperLabel->getString();
}

void CCLabelBMFontv2::setHorizontalAlignment(CCTextAlignment alignment) {
	_horizontalAlignment = alignment;

	_helperLabel->setAlignment(_horizontalAlignment);

	switch (_horizontalAlignment) {
	case kCCTextAlignmentLeft:
		_helperLabel->setPosition(CCPointMake(0, _helperLabel->getPositionY()));
		break;
	case kCCTextAlignmentCenter:
		_helperLabel->setPosition(CCPointMake(getContentSize().width / 2 - (_helperLabel->getContentSize().width * _helperLabel->getScale() / 2), _helperLabel->getPositionY()));
		break;
	case kCCTextAlignmentRight:
		_helperLabel->setPosition(CCPointMake((getContentSize().width - (_helperLabel->getContentSize().width * _helperLabel->getScale())), _helperLabel->getPositionY()));
		break;
	default:
		break;
	}
}

void CCLabelBMFontv2::setVerticalAlignment(CCVerticalTextAlignment alignment) {
	_verticalAlignment = alignment;

	switch (_verticalAlignment) {
	case kCCVerticalTextAlignmentBottom:
		_helperLabel->setPosition(CCPointMake(_helperLabel->getPositionX(), 0));
		break;
	case kCCVerticalTextAlignmentCenter:
		_helperLabel->setPosition(CCPointMake(_helperLabel->getPositionX(), getContentSize().height / 2 - (_helperLabel->getContentSize().height * _helperLabel->getScale()) / 2));
		break;
	case kCCVerticalTextAlignmentTop:
		_helperLabel->setPosition(CCPointMake(_helperLabel->getPositionX(), getContentSize().height - (_helperLabel->getContentSize().height * _helperLabel->getScale())));
		break;
	default:
		break;
	}
}

void CCLabelBMFontv2::setShrink(bool value) {
	if(_shrink != value) {
		_shrink = value;

		if(_shrink){
			_helperLabel->setWidth(0);
		}

		refresh();
	}
}

void CCLabelBMFontv2::refresh() {
	updateTexture();
	setHorizontalAlignment(_horizontalAlignment);
	setVerticalAlignment(_verticalAlignment);
}

void CCLabelBMFontv2::updateTexture() {
	if(_shrink){
		float scaleFactor = getContentSize().width / (_helperLabel->getContentSize().width * _fontScale);

		if(scaleFactor < 1){
			_shrinkScale = scaleFactor;
		}
		else if(_fontScale != 1){
			_shrinkScale = 1;
		}

		_helperLabel->setScale(_fontScale * _shrinkScale);

	}
	else {
		_helperLabel->setScale(_fontScale);
	}
}


void CCLabelBMFontv2::setFontScale(float fontSc) {
	_fontScale = fontSc;
	refresh();
}

void CCLabelBMFontv2::setFntFile(const char *fntFile) {
	_helperLabel->setFntFile(fntFile);
	refresh();
}

const char* CCLabelBMFontv2::getFntFile() {
	return _helperLabel->getFntFile();
}

void CCLabelBMFontv2::setBlendFunc(ccBlendFunc bldFunc) {
	_helperLabel->setBlendFunc(bldFunc);
}

ccBlendFunc CCLabelBMFontv2::getBlendFunc() {
	return _helperLabel->getBlendFunc();
}

// CCNode
void CCLabelBMFontv2::setContentSize(const CCSize &size) {
	CCNode::setContentSize(size);

	if(!_shrink){
		_helperLabel->setWidth(size.width);
	}

	refresh();
}

void CCLabelBMFontv2::setAnchorPoint(const CCPoint& point) {
	CCNode::setAnchorPoint(point);
//	_helperLabel->setAnchorPoint(point);
}

void CCLabelBMFontv2::setScale( float scale ) {
	CCNode::setScale(scale);
//	_helperLabel->setScale(scale);
}

void CCLabelBMFontv2::setScaleX( float fScaleX ) {
	CCNode::setScaleX(fScaleX);
//	_helperLabel->setScaleX(fScaleX);
}

void CCLabelBMFontv2::setScaleY( float fScaleY ) {
	CCNode::setScaleY(fScaleY);
//	_helperLabel->setScaleY(fScaleY);
}


// CCRGBAProtocol
const ccColor3B& CCLabelBMFontv2::getColor() {
	return _helperLabel->getColor();
}
void CCLabelBMFontv2::setColor(const ccColor3B& color) {
	_helperLabel->setColor(color);
}
GLubyte CCLabelBMFontv2::getOpacity() {
	return _helperLabel->getOpacity();
}

void CCLabelBMFontv2::setOpacity(GLubyte opacity) {
	_helperLabel->setOpacity(opacity);
}
const ccColor3B& CCLabelBMFontv2::getDisplayedColor(void) {
	return _helperLabel->getDisplayedColor();
}
GLubyte	CCLabelBMFontv2::getDisplayedOpacity(void){
	return _helperLabel->getDisplayedOpacity(); 
}
void CCLabelBMFontv2::setOpacityModifyRGB(bool bValue){
	_helperLabel->setOpacityModifyRGB(bValue);
}
bool CCLabelBMFontv2::isOpacityModifyRGB(void){
	return _helperLabel->isOpacityModifyRGB();
}
bool CCLabelBMFontv2::isCascadeColorEnabled(void){
	return _helperLabel->isCascadeColorEnabled();
}
void CCLabelBMFontv2::setCascadeColorEnabled(bool cascadeColorEnabled){
	_helperLabel->setCascadeColorEnabled(cascadeColorEnabled);
}
void CCLabelBMFontv2::updateDisplayedColor(const ccColor3B& color){
	_helperLabel->updateDisplayedColor(color);
}
bool CCLabelBMFontv2::isCascadeOpacityEnabled(void){
	return _helperLabel->isCascadeOpacityEnabled();
}
void CCLabelBMFontv2::setCascadeOpacityEnabled(bool cascadeOpacityEnabled){
	_helperLabel->setCascadeOpacityEnabled(cascadeOpacityEnabled);
}
void CCLabelBMFontv2::updateDisplayedOpacity(GLubyte opacity){
	_helperLabel->updateDisplayedOpacity(opacity);
}
