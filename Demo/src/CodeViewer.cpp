#include "stdafx.h"
#include "CodeViewer.h"
#include "CodeGenerator.h"

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

CodeViewer::CodeViewer(void) : scv::Panel(scv::Point(), scv::Point()) {
   _textbox = new scv::TextBox(scv::Point(0,0),scv::Point(0,0),"CodeViewer");
   _textbox->setEditable(false);
   addChild(_textbox);

   scv::GroupLayout *layout = new scv::GroupLayout(this);
   setLayout(layout);

   hGroupLayout = scv::GroupLayout::createParallelGroup();
   vGroupLayout = scv::GroupLayout::createParallelGroup();

   layout->setHorizontalGroup(scv::GroupLayout::createSequentialGroup()->addGap(15, 15, -1)->addGroup(hGroupLayout)->addGap(15, 15, -1));
   layout->setVerticalGroup(scv::GroupLayout::createSequentialGroup()->addGap(15, 15, -1)->addGroup(vGroupLayout)->addGap(15, 15, -1));

   setFrameSize(400, 300);
}

CodeViewer::~CodeViewer(void) {
}

void CodeViewer::setFrameSize(int width, int height) {
   vGroupLayout->removeComponent(_textbox);
   vGroupLayout->removeComponent(_textbox);

   hGroupLayout->addComponent(_textbox, width);
   vGroupLayout->addComponent(_textbox, height);

   _textbox->setSize(width, height);

}

void CodeViewer::setText(std::string text)
{
    _textbox->setString(text);
}

void CodeViewer::display(void) {
   scv::Panel::display();
}

