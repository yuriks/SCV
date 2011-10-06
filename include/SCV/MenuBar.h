/*!
\file       MenuBar.h
\brief      Implementation of a menu with drop down menus.
\author     SCV Team
*/

#ifndef __SCV_MENU_BAR_H__
#define __SCV_MENU_BAR_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Panel.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A region of application interface where drop down menus are displayed.
 * \ingroup widgets
 */

class MenuBar : public Panel {
public:

   /*! Constructor
    * The menu bar will always be in the top of its container.
   \param width The width of the component.
   */
   MenuBar(int width);


   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   /*! Adds a button to a new drop down menu.
   */
   void addMenu(ContextMenu *menu);
   /*! Returns a boolean that shows if have some menu active.
   */
   bool hasActiveMenu(void) const;
   /*! Close all menus and sub menus.
   */
   void closeAllMenus(void);
   /*! Activates a menu for your ID.
   */
   void activeMenu(int id);


protected:
   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void processMouse(const scv::MouseEvent &evt);
   //! Keyboard function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   virtual void processKey(const scv::KeyEvent &evt);
    /*! Called to create the texture of the component.
    * This should only be re-implemented if you're creating a new type of component.
    */
   virtual void createTexture(void);
    /*! Display function of the component.
    * This should only be re-implemented if you're creating a new type of component.
    */
   virtual void display(void);

private:

   static const int s_menuHeight;
   static const int s_menuSpacing;
   static const int s_borderWidth;
   static const int s_borderHeight;

   int _currSelectedMenu;
   int _currecOverMenu;
   bool _active;

   std::vector<int> _index;
   std::vector<ContextMenu*> _menus;
};

} // namespace scv


#endif // __SCV_MENU_BAR_H__
