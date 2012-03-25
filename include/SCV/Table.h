/*!
\file       Table.h
\brief      Implementation of a Table.
\author     SCV Team
*/

#ifndef __SCV_TABLE_H__
#define __SCV_TABLE_H__

#include "MatrixTemplate.h"
#include "Panel.h"
#include "TextBox.h"
#include "Button.h"
#include "GroupLayout.h"

namespace scv {

class Table : public Panel {
public:
   Table(const scv::Point &p, int nRows = 4, int nColumns = 4, int nCellLines = 1, int CellWidth = 1);
   virtual void display(void);

   void addRow(void);
   void addRow(int number);

   void addColumn(void);
   void addColumn(int number);

   void align(int column);

   void remakeLayout(void);
   
   void setString(int row, int column, std::string str);
   std::string getString(int row, int column);

   std::vector<std::string> getRow(int row);
   std::vector<std::string> getColumn(int column);

   void clear(void);
   //void removeRow(int begin, int end); not implemented
   //void removeColumn(int begin, int end); not implemented
   
   int getNumberOfRows(void);   
   int getNumberOfColumns(void);
   
   int getNumberOfLinesPerCell(void);
   
   int getCellWidth(void);

   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);

   void processMouse(const scv::MouseEvent &evt);
   void processKey(const scv::KeyEvent &evt);

private:
   class TableButton : public Button {
   public:
      TableButton(Table *table, const scv::Point &p, unsigned int width, const std::string &str, int column);
      void onMouseUp(const scv::MouseEvent &evt);
      Table *_table;
      int _column;
   };
   void setAlign(bool state);
   bool alphabetical(std::string str1, std::string str2);

   int _nRows, _nColumns;
   int _nCellLines, _cellWidth;
   int character;
   bool _align;
   std::deque<Button *> _buttons;

   GroupLayout *_layout;
   scv::Group *hGroupLayout, *vGroupLayout; 
   bool isTableModified;

protected:
   std::deque<std::deque< TextBox *> > _table;
};

} // namespace scv

#endif // __SCV_TABLE_H__