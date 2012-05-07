#include "stdafx.h"
#include "Image.h"
#include "Kernel.h"
#include "ImgLoader.h"

namespace scv {

Image::Image(const scv::Point &p1, const std::string &fileName) : Panel(p1, Point(p1.x + 10, p1.y + 10)) {
   _data = NULL;
   loadImage(fileName);
   
   setWidth(_realSize.x);
   setHeight(_realSize.y); 

   _type = IMAGE;
   _minimumSize = Point(1,1);
}

Image::Image(const scv::Point &p1, const scv::Point &p2, const std::string &fileName) : Panel(p1, p2) {
   _data = NULL;
   loadImage(fileName);
   
   _minimumSize = Point(1,1);
   _type = IMAGE;
}

Image::~Image() {
   if (_data != NULL) {
      freeImageData(_data);
   }
}

void Image::loadImage(const std::string &fileName) {
   if (_data != NULL) {
      delete _cTexture;
      _cTexture = NULL;

      freeImageData(_data);
      _data = NULL;
   }

   _path = fileName;
   _data = loadImageToArray(fileName, &_realSize.x, &_realSize.y);
   
   createTexture();
}

void Image::display(void) {
   static Kernel *kernel = Kernel::getInstance();
   static Scissor *scissor = Scissor::getInstance();
   static ColorScheme *scheme = ColorScheme::getInstance();

   if (_cTexture == NULL || _isVisible == false || _data == NULL) return;

   Point currPosition = getAbsolutePosition();

   Scissor::Info scissorInfo(currPosition.x, kernel->getHeight() - (getHeight() + currPosition.y), getWidth(), getHeight());
   scissor->pushScissor(scissorInfo);

   //mantem o estado atual da textura, para dois casos: 
   //1) render dentro de uma canvas - a textura esta desabilitada
   //2) render de componentes do scv - a textura ja deve estar habilitada
   glPushAttrib(GL_ALL_ATTRIB_BITS); 
   
   //habilita a textura para que a imagem possa ser desenhada
   glEnable(GL_TEXTURE_2D);
   
   _cTexture->enable();
   scheme->applyDefaultModulate();

   // image display
   _cTexture->display(currPosition.x, currPosition.y, 0, getWidth(), getHeight());

   _cTexture->disable();

   //restaura a situacao inicial da textura: canvas ou scv
   glPopAttrib();


   // components
   for (List::const_iterator iter = getChildren().begin(); iter != getChildren().end(); ++iter) {
      if (kernel->willAppearOnScreen(*iter))
         (*iter)->display();
   }
   scissor->popScissor();
}

void Image::createTexture(void) {
   if (_data == NULL) return;

   _cTexture = new ComponentTexture(_realSize.x, _realSize.y);
   _cTexture->setTextureEnvMode(GL_MODULATE);
   _cTexture->addTexture(Point(0,0), _realSize.x, _realSize.y, _data);
   _cTexture->createTexture();
}

} // namespace scv
