#ifndef __SCV_IMAGE_INTERFACE_H__
#define __SCV_IMAGE_INTERFACE_H__

#include "Panel.h"

namespace scv {

class Image : public Panel {
public:
   Image(const scv::Point &p1, const std::string &fileName);
   Image(const scv::Point &p1, const scv::Point &p2, const std::string &fileName);

   inline const unsigned char *getData(void) const;
   inline const std::string &getPath(void) const;
   
   void loadImage(const std::string &fileName);
   inline scv::Point getImageSize(void) const;

   virtual void display(void);

protected:
   virtual void createTexture(void);

private:
   unsigned char * _data;

   std::string _path;
   scv::Point _realSize;
};

///////////////////////////////////////////////////////////
const unsigned char *Image::getData(void) const {
   return _data;
}

const std::string &Image::getPath(void) const {
   return _path;
}

scv::Point Image::getImageSize(void) const {
   return _realSize;
}

} // namespace scv

#endif // __SCV_IMAGE_INTERFACE_H__