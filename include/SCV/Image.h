/*!
\file       Image.h
\brief      Implementation of a Image Panel.
\author     SCV Team
*/

#ifndef __SCV_IMAGE_INTERFACE_H__
#define __SCV_IMAGE_INTERFACE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Panel.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A simple Panel with a background image.
 * \ingroup widgets
 */

class Image : public Panel {
public:
   /*! Constructor
   \param p1 The initial position of the component.
   \param fileName Location of image in your computer.
   */
   Image(const scv::Point &p1, const std::string &fileName);
   /*! Constructor
   This constructor is used to resize the image panel.
   \param p1 The initial position of the component.
   \param p2 The final position of component.
   \param fileName Location of image in your computer.
   */
   Image(const scv::Point &p1, const scv::Point &p2, const std::string &fileName);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);

   virtual void onResizing(void);
   virtual void onDragging(void);

   /*! Gets image information.
   \return Array with RGBA colors.
   */
   unsigned char * getData(void);
   /*! Gets image information.
   \return Image location on your computer.
   */
   const std::string &getPath(void);
   //! Array with RGBA colors.
   unsigned char * data;

   virtual void display(void);

protected:
   virtual void createTexture(void);

private:

   std::string location;
   scv::Point _realSize;
};

} // namespace scv

#endif // __SCV_IMAGE_INTERFACE_H__