/*!
\file       ComboBox.h
\brief      Implementation of a ComboBox widget.
\author     SCV Team
*/

#ifndef __SCV_COMBOBOX_H__
#define __SCV_COMBOBOX_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Button.h"
#include "ContextMenu.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A widget that allows the user to select one value from a list.
 *
 * \ingroup widgets
 */
class ComboBox : public Button {
public:
   /*! Constructor
    *
    * \param p1 The initial position of the component.
    * \param p2 The final position of component.
    */
   ComboBox(const scv::Point &p1, const scv::Point &p2);
   /*! Constructor
    *
    * \param p Initial position of the component.
    * \param width Width of the component.
    */
   ComboBox(const scv::Point &p, unsigned int width);
   /*! Constructor
    *
    * \param p Initial point of the component.
    * \param width Width of the component.
    * \param items The items vector of the Combobox.
    * \param defaultIndex The initial id active.
    */
   ComboBox(const scv::Point &p, unsigned int width, std::vector <std::string> items, unsigned int defaultIndex);

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);

   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);

   virtual void onResizing(void);
   virtual void onDragging(void);

   /*! Callback called when the active item of the ComboBox is changed.
    *
    * \param address Name of the item.
    * \param id ID of the item.
    */
   virtual void onSelectionChanged(std::string address, int id);
   /*! Gets the currently selected value.
    *
    * \return std::string value of selected item.
    */
   std::string getValue(void);
   /*! Gets the currently selected value.
    *
    * \return Returns the index of the selected item.
    */
   int getIndex(void);
   /*! Changes the currently selected value.
    *
    * \param offset The ID of the new value.
    */
   void setIndex(int offset);

   virtual void display(void);

   /*! Sets the list of items in the text box.
    *
    * \param items The new items vector of the Combobox.
    */
   void setItems(const std::vector<std::string>& items);
   /*! Adds the item to the list of items in the text box.
    *
    * \param str The new items of the Combobox.
    */
   void addItem(const std::string& str);
   /*! Pops up the ComboBox menu. */
   void popupMenu(void);

private:

   class ComboBoxMenu : public ContextMenu {
   public:
      ComboBoxMenu(ComboBox& combo);
      void onMenuAccessed(const std::deque<std::string> &address);
      void setItems(const std::vector<std::string>& items);
      void addItem(const std::string item);

      ComboBox& combo;
   };

   void createTexture(void);
   void processMouse(const scv::MouseEvent &evt);
   void select(const std::string& value);

   ComboBoxMenu* menu;
   bool _active;
   class ComboBoxContextMenu;
   std::vector<std::string> _values;
   int _currentValue;
   friend class ComboBoxMenuStyle;
};

} // namespace scv

#endif // __SCV_COMBOBOX_H__