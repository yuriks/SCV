#ifndef __SCV_COMBOBOX_H__
#define __SCV_COMBOBOX_H__

#include "Button.h"
#include "ContextMenu.h"

namespace scv {

class ComboBox : public Button {
friend class ComboBoxMenuStyle;
public:
   ///////////////////////////////////////////////////////////
   ComboBox(const scv::Point &p1, const scv::Point &p2);
   ComboBox(const scv::Point &p, unsigned int width);
   ComboBox(const scv::Point &p, unsigned int width, std::vector <std::string> items, unsigned int defaultIndex);
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

   virtual void onSelectionChanged(std::string address, int id);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   std::string getValue(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   int getIndex(void);
   void setIndex(int offset);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setItems(const std::vector<std::string>& items);

   void addItem(const std::string& str);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void popupMenu(void);
   ///////////////////////////////////////////////////////////

   virtual void display(void);

private:
   ///////////////////////////////////////////////////////////
   class ComboBoxMenu : public ContextMenu {
   public:
      ComboBoxMenu(ComboBox& combo);
      void onMenuAccessed(const std::deque<std::string> &address);
      void setItems(const std::vector<std::string>& items);
      void addItem(const std::string item);
      ComboBox& combo;
   };
   ///////////////////////////////////////////////////////////

   void createTexture(void);
   void processMouse(const scv::MouseEvent &evt);
   void select(const std::string& value);

   ComboBoxMenu* menu;
   bool _active;
   class ComboBoxContextMenu;
   std::vector<std::string> _values;
   int _currentValue;   
};

} // namespace scv

#endif // __SCV_COMBOBOX_H__