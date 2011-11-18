#ifndef __SCV_IMAGE_INTERFACE_H__
#define __SCV_IMAGE_INTERFACE_H__

#include "Panel.h"

namespace scv {

class Image : public Panel {
public:
   ///////////////////////////////////////////////////////////
   Image(const scv::Point &p1, const std::string &fileName);
   Image(const scv::Point &p1, const scv::Point &p2, const std::string &fileName);
   virtual ~Image(void);
   ///////////////////////////////////////////////////////////

   //SCVCallbacks
   ///////////////////////////////////////////////////////////
   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold (const scv::MouseEvent &evt);
   virtual void onMouseOver (const scv::MouseEvent &evt);
   virtual void onMouseUp   (const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp     (const scv::KeyEvent &evt);

   virtual void onSizeChange(void);
   virtual void onPositionChange(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline const unsigned char *getData(void) const;
   inline const std::string &getPath(void) const;
   ///////////////////////////////////////////////////////////
   
   virtual void display(void);

protected:
   virtual void createTexture(void);

private:
   unsigned char * data;

   std::string location;
   scv::Point _realSize;
};

///////////////////////////////////////////////////////////
const unsigned char *Image::getData(void) const {
   return data;
}

const std::string &Image::getPath(void) const {
   return location;
}
///////////////////////////////////////////////////////////

} // namespace scv

#endif // __SCV_IMAGE_INTERFACE_H__