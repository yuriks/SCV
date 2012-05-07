/*!
\file       ComboBox.h
\brief      Implementation of a ComboBox.
\author     SCV Team
*/

#ifndef __SCV_COMBOBOX_H__
#define __SCV_COMBOBOX_H__

#include "Button.h"
#include "ContextMenu.h"

namespace scv {

class ComboBox : public Button {
friend class ComboBoxMenuStyle;
public:
   ComboBox(const scv::Point &p1, const scv::Point &p2);
   ComboBox(const scv::Point &p, unsigned int width);
   virtual ~ComboBox(void);

   virtual void onSelectionChanged(std::string address, int id);

   std::string getValue(void);

   int getIndex(void);
   void setIndex(int offset);

   void setItems(const std::vector<std::string>& items);
   void addItem(const std::string& str);

   void popupMenu(void);
   void popMenu(void);

   virtual void display(void);

protected:
   class ComboBoxMenu : public ContextMenu {
   public:
      ComboBoxMenu(scv::ComboBox *host);
      
      void onMenuAccessed(const std::deque<std::string> &address);
      void onStatusChange(void);

      void setItems(const std::vector<std::string>& items);
      void addItem(const std::string item);

      scv::ComboBox *_host;
   };

   void createTexture(void);
   void processMouse(const scv::MouseEvent &evt);

   void select(const std::string& value);

   ComboBoxMenu* _comboBoxMenu;
      
   bool _active;
   int _currentValue;
   std::vector<std::string> _values;
};

} // namespace scv

#endif // __SCV_COMBOBOX_H__