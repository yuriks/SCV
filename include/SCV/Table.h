/*!
\file       Table.h
\brief      Implementation of a Table widget.
\author     SCV Team
*/

#ifndef __SCV_TABLE_H__
#define __SCV_TABLE_H__

#ifndef DOXYGEN_SKIP_THIS
#include "MatrixTemplate.h"
#include "Panel.h"
#include "TextBox.h"
#include "Button.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! A table is a set of data elements (values) that is organized using a model of vertical columns and horizontal rows.
 * \ingroup widgets
 */

class Table : public Panel {
public:

   //! Constructor
   /*!
   \param p The upper left corner of the component.
   \param nRows Number of rows.
   \param nColumns Number of columns
   \param nCellLines Number of lines per each cell.
   \param CellWidth Width of each cell.
   */
   Table(const scv::Point &p, int nRows = 4, int nColumns = 4, int nCellLines = 1, int CellWidth = 100);


   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onSizeChange(void);
   virtual void onPositionChange(void);

   //! Adds a new row to the table.
   void addRow(void);
   //! Adds a new column to the table.
   void addColumn(void);
   //! Adds new rows to the table.
   /*!
   \param number Number of new rows.
   */
   void addRow(int number);
   //! Adds new columns to the table.
   /*!
   \param number Number of new columns.
   */
   void addColumn(int number);
   //! Sort a column.
   /*!
   \param column Column to be sorted.
   */
   void align(int column);
   void clear(void);
   void setString(int row, int column, std::string str);
   std::string getString(int row, int column);
   std::vector<std::string> getRow(int row);
   std::vector<std::string> getColumn(int column);

   //void removeRow(int begin, int end); not implemented
   //void removeColumn(int begin, int end); not implemented

   //! Gets the current number of rows.
   int getNumberOfRows(void);
   //! Gets the current number of columns.
   int getNumberOfColumns(void);
   //! Gets the current number of lines per cell.
   int getNumberOfLinesPerCell(void);
   //! Gets the current width of the cells.
   int getCellWidth(void);

   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);

   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   //! Key function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
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

protected:
   std::deque<std::deque< TextBox *> > _table;
};

} // namespace scv

#endif // __SCV_TABLE_H__