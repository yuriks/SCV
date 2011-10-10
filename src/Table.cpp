#include "stdafx.h"
#include "Table.h"
#include "Kernel.h"
#include "util.h"

namespace scv {

Table::Table( const scv::Point &p, int nRows /*= 4*/, int nColumns /*= 4*/, int nCellLines /*= 1*/, int CellWidth /*= 100*/ ) :
   Panel(p, Point(p.x + nColumns * (CellWidth - 1) + 1,20 + p.y + (TextBox::s_lineSpacing * nCellLines + TextBox::s_borderHeight) * nRows + 1)), _nColumns(nColumns), _nRows(nRows), _nCellLines(nCellLines), _cellWidth(CellWidth) {
   _align = _isHResizable = _isVResizable = false;

   std::deque<TextBox *> tmp;

   character = 65;
   for (int i = 0 ; i < _nColumns ; i++ ) {
      _buttons.push_back(new TableButton(this, Point(i * (CellWidth - 1),0),CellWidth,toString(char(character)), i));
      Panel::addChild(_buttons.back());
      character++;
   }

   for (int i = 0 ; i < _nRows ; i++ ) {
      tmp.clear();
      for (int j = 0 ; j <  _nColumns; j++ ) {
         tmp.push_back(new TextBox(Point(j * (CellWidth - 1),20 +  i * (TextBox::s_lineSpacing * nCellLines + TextBox::s_borderHeight)), CellWidth, nCellLines, ""));
         Panel::addChild(tmp.back());
      }
      _table.push_back(tmp);
   }

   _type = TABLE;

   createTexture();

}

void Table::setString(int row, int column, std::string str) {
   if (row >= 0 && row < _nRows && column >= 0 && column < _nColumns) {
      _table[row][column]->setString(str);
   }
}


std::string Table::getString(int row, int column) {
   if (row >= 0 && row < _nRows && column >= 0 && column < _nColumns) {
      return _table[row][column]->getString();
   }
   return "";
}

std::vector<std::string> Table::getRow(int row) {
   std::vector<std::string> vec;
   if (row >= 0 && row < _nRows) {
      for (int i = 0; i < _nColumns; i++)
      	vec.push_back(_table[row][i]->getString());
      }
   return vec;
}

std::vector<std::string> Table::getColumn(int column) {
   std::vector<std::string> vec;
   if (column >= 0 && column < _nColumns) {
      for (int i = 0; i < _nRows; i++)
         vec.push_back(_table[i][column]->getString());
   }
   return vec;
}

void Table::addRow(void) {
   std::deque<TextBox *> tmp;
   int i = _nRows;
   for (int j = 0; j <  _nColumns; j++ ) {
      tmp.push_back(new TextBox(Point(j * (_cellWidth - 1),20 + i * (TextBox::s_lineSpacing * _nCellLines + TextBox::s_borderHeight)), _cellWidth, _nCellLines, ""));
      Panel::addChild(tmp.back());
   }
   _table.push_back(tmp);
   _nRows++;
   Panel::_p2.y += (TextBox::s_lineSpacing * _nCellLines + TextBox::s_borderHeight);
}

void Table::addRow(int number) {
   for (int i = 0; i < number; i++) {
      addRow();
   }
}

void Table::addColumn(void) {
   std::deque<TextBox *> tmp;
   int j = _nColumns;
   for (int i = 0; i < _nRows; i++ ) {
      _buttons.push_back(new TableButton(this, Point(j * (_cellWidth - 1),0),_cellWidth,toString(char(character)), j));
      Panel::addChild(_buttons.back());
      _table[i].push_back(new TextBox(Point(j * (_cellWidth - 1),20 + i * (TextBox::s_lineSpacing * _nCellLines + TextBox::s_borderHeight)), _cellWidth, _nCellLines, ""));
      Panel::addChild(_table[i].back());
   }
   character++;
   _nColumns++;
   Panel::_p2.x += (_cellWidth - 1);
}

void Table::addColumn(int number) {
   for (int i = 0; i < number; i++) {
      addColumn();
   }
}

bool Table::alphabetical(std::string str1, std::string str2) {
   int i = 0;
   while (i < str1.length() && i < str2.length() && i >= 0) {
      int s1 = str1[i]; if (s1>64 && s1<91) s1 += 32;
      int s2 = str2[i]; if (s2>64 && s2<91) s2 += 32;
      if (s1 < s2) return true;
      if (s1 > s2) return false;
      i++;
   }
   if (i == str1.size())
      return true;
   return false;
}

void Table::align(int column) {
   if (column >= 0 && column < _nColumns) {

      std::vector< std::vector< std::string > > tmp_vstr;
      std::vector< std::string > tmp_str;
      int max = 0;
      int _max = 0;
      int index = 0;
      std::vector<bool> checked(_table.size(),false);

      for (int t = 0 ; t < _table.size() ; t++ ) {
         max = 0;
         _max = 0;
         index = -1;
         for (int i = 0 ; i < _table.size() ; i++ ) {
            if (checked[i] == true) continue;
            if (index == -1) {
               index = i;
               continue;
            }
            if (alphabetical(_table[index][column]->getString(),_table[i][column]->getString()))
               index = i;
         }

         for (int j = 0; j < _table[index].size(); j++) {
            tmp_str.push_back(_table[index][j]->getString());
         }

         checked[index] = true;
         tmp_vstr.push_back(tmp_str);
         tmp_str.clear();

      }

      for (int i = 0 ; i < _table.size() ; i++) {
         for (int j = 0; j < _table[i].size() ; j++) {
         	_table[i][j]->setString(tmp_vstr[_nRows-i-1][j]);
         }
      }

      tmp_vstr.clear();
   }
}



void Table::onMouseClick(const scv::MouseEvent &evt) {/**/}
void Table::onMouseHold(const scv::MouseEvent &evt) {/**/}
void Table::onMouseOver(const scv::MouseEvent &evt) {/**/}
void Table::onMouseUp(const scv::MouseEvent &evt) {/**/}
void Table::onKeyPressed(const scv::KeyEvent &evt) {/**/}
void Table::onKeyUp(const scv::KeyEvent &evt) {/**/}
void Table::onMouseWheel(const scv::MouseEvent &evt) {/**/}
void Table::onSizeChange(void) {/**/}
void Table::onPositionChange(void) {/**/}

// void Table::removeRow(int begin, int end) {
//    for (int i = 0; i < (end - begin + 1) ; i++) {
//       _table.size();
//    	_table.erase(_table.begin() + begin);
//       _table.size();
//       std::cout << "haeuhe" << std::endl;
//    }
//    _nRows -= (end - begin + 1);
// }



// void Table::removeColumn(int begin, int end) {
//    for (int i = 0; i < _nRows ; i++) {
//    	for (int j = 0; j < (end - begin + 1) ; j++) {
//          _table[i].erase(_table[i].begin() + begin);
//       }
//    }
//    _nColumns -= (end - begin + 1);
// }


int Table::getNumberOfRows(void) {
   return _nRows;
}

int Table::getNumberOfColumns(void) {
   return _nColumns;
}


void Table::clear(void) {
   for (int i = 0; i < _nRows ; i++ ) {
      for (int j = 0; j <  _nColumns; j++ ) {
            _table[i][j]->setString("");
      }
   }
}

void Table::processKey(const scv::KeyEvent &evt) {
   static Kernel *kernel = Kernel::getInstance();

   Panel::processKey(evt);

   if(!_receivingCallbacks) return;

   if (evt.getKeyString() == "Tab" && evt.getState() == KeyEvent::DOWN) {
      for (int i = 0; i < _nRows ; i++ ) {
         for (int j = 0; j <  _nColumns; j++ ) {
            if (kernel->getFocusedComponent() == _table[i][j]) {
               if (j + 1 < _nColumns) {
                  kernel->requestComponentFocus(_table[i][j + 1]);
               } else if (i + 1 < _nRows) {
                  kernel->requestComponentFocus(_table[i + 1][0]);
               } else {
                  kernel->requestComponentFocus(_table[0][0]);
               }
               return;
            }
         }
      }
   }
}

void Table::setDraggable(bool state) {
   Component::setDraggable(state);
   for (int i = 0; i < _table.size(); i++) {
      for (int j = 0; j < _table[i].size(); j++) {
         _table[i][j]->setDraggable(state);
      }
   }
   for (int i = 0; i < _buttons.size(); i++) {
      _buttons[i]->setDraggable(state);
   }
}

void Table::setResizable(bool state) {
   Component::setResizable(state);
   for (int i = 0; i < _table.size(); i++) {
      for (int j = 0; j < _table[i].size(); j++) {
         _table[i][j]->setResizable(state);
      }
   }
   for (int i = 0; i < _buttons.size(); i++) {
      _buttons[i]->setResizable(state);
   }
}

void Table::processMouse(const scv::MouseEvent &evt) {
   if (!_receivingCallbacks) {
      Component::processMouse(evt);
   } else {
      Panel::processMouse(evt);
   }
}

void Table::setAlign(bool state) {
   _align = state;
}

int Table::getNumberOfLinesPerCell(void) {
   return _nCellLines;
}

int Table::getCellWidth(void) {
   return _cellWidth;
}

Table::TableButton::TableButton(Table *table, const scv::Point &p, unsigned int width, const std::string &str, int column)
   : Button(p,width,str) {
   _column = column;
   _table = table;
}

void Table::TableButton::onMouseUp(const scv::MouseEvent &evt) {
   if (_table->_align)
      _table->align(_column);
}


} // namespace scv