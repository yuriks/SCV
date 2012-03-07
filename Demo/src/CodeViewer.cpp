#include "stdafx.h"
#include "CodeViewer.h"
#include "CodeGenerator.h"

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

CodeViewer::CodeViewer(void) : scv::Panel(scv::Point(), scv::Point()) {
   _textbox = new scv::TextBox(scv::Point(),scv::Point(),"CodeViewer");
   _textbox->setEditable(false);
   addChild(_textbox);

   scv::GroupLayout *layout = new scv::GroupLayout(this);
   setLayout(layout);

   hGroupLayout = scv::GroupLayout::createParallelGroup();
   vGroupLayout = scv::GroupLayout::createParallelGroup();

   hGroupLayout->addComponent(_textbox);
   vGroupLayout->addComponent(_textbox);

   layout->setHorizontalGroup(hGroupLayout);
   layout->setVerticalGroup(vGroupLayout);
}

CodeViewer::~CodeViewer(void) {
}

void CodeViewer::setText(std::string text)
{
    _textbox->setString(text);
}

void CodeViewer::display(void) {
   scv::Panel::display();
}

