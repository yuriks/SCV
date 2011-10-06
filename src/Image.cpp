#include "stdafx.h"
#include "Image.h"
#include "Kernel.h"
#include "ImgLoader.h"

namespace scv {

Image::Image(const scv::Point &p1, const std::string &fileName) : Panel(p1, Point(p1.x + 10, p1.y + 10)) {
   data = NULL;
   int width, height;
   location = fileName;

   data = ImgLoader::getInstance()->loadImageToArray(fileName, &width, &height);

   setWidth(width);
   setHeight(height); 

   _realSize.x = width;
   _realSize.y = height;

   _type = image;

   _minSize = Point(1,1);

}

Image::~Image() {}

Image::Image(const scv::Point &p1, const scv::Point &p2, const std::string &fileName) : Panel(p1, p2) {
   data = NULL;
   int width, height;
   location = fileName;

   data = ImgLoader::getInstance()->loadImageToArray(fileName, &width, &height);

   _realSize.x = width;
   _realSize.y = height;

   _minSize = Point(1,1);

   _type = image;
}

void Image::onMouseClick(const scv::MouseEvent &evt) {}
void Image::onMouseHold(const scv::MouseEvent &evt) {}
void Image::onMouseOver(const scv::MouseEvent &evt) {}
void Image::onMouseUp(const scv::MouseEvent &evt) {}
void Image::onKeyPressed(const scv::KeyEvent &evt) {}
void Image::onKeyUp(const scv::KeyEvent &evt) {}
void Image::onMouseWheel(const scv::MouseEvent &evt) {}
void Image::onSizeChange(void) {}
void Image::onPositionChange(void) {}

void Image::display(void) {
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false || data == NULL) return;

   Point currPosition = getAbsolutePosition();

   Scissor::Info scissorInfo(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight());
   scissor->pushScissor(scissorInfo);

   _cTexture->enable();
   scheme->applyDefaultModulate();

   // image display
   _cTexture->display(currPosition.x, currPosition.y, 0, getWidth(), getHeight());

   _cTexture->disable();

   // components
   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }
   scissor->popScissor();
}

void Image::createTexture(void) {
   if (data == NULL) return;
   _cTexture = new ComponentTexture(_realSize.x, _realSize.y);
   _cTexture->setTextureEnvMode(GL_MODULATE);
   _cTexture->addTexture(Point(0,0), _realSize.x, _realSize.y, data);
   _cTexture->createTexture();
}

} // namespace scv
