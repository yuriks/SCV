#ifndef __SCV_COMPONENT_WITH_TEXTURE_H__
#define __SCV_COMPONENT_WITH_TEXTURE_H__

///////////////////////////////////////////////////////////
#include "Component.h"
#include "ComponentTexture.h"
///////////////////////////////////////////////////////////

namespace scv {

class ComponentWithTexture : public Component {
public:
   ComponentWithTexture(const scv::Point &p1, const scv::Point &p2);
   virtual ~ComponentWithTexture(void);

   ///////////////////////////////////////////////////////////
   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);
   virtual void setVisible(bool state);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void processMouse(const scv::MouseEvent &evt);
   virtual void processKey(const scv::KeyEvent &evt);
   ///////////////////////////////////////////////////////////

   virtual void display(void) = 0;

   ///////////////////////////////////////////////////////////
   virtual int getWidth(void) const;
   virtual void setWidth(int width);

   virtual int getHeight(void) const;   
   virtual void setHeight(int height);

   virtual Point getSize(void) const;

   virtual Point getMinimumSize(void) const;
   virtual Point getPreferredSize(void) const;
   virtual Point getMaximumSize(void) const;
   ///////////////////////////////////////////////////////////

   virtual void setRelativePosition(const Point &position);


   //Memory Management
   ///////////////////////////////////////////////////////////
   virtual void addChild(Component *object);
   virtual void removeChild(Component *object);
   ///////////////////////////////////////////////////////////

protected:
   virtual void createTexture(void) = 0;
   ComponentTexture *_cTexture;
};

} // namespace scv

#endif // __SCV_COMPONENT_WITH_TEXTURE_H__
