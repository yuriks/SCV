#ifndef _GENERIC_NODE_DISPLAY_
#define _GENERIC_NODE_DISPLAY_

namespace scv {

struct GenericNodeDisplay
{
    GenericNodeDisplay(std::string& label, bool selected, bool open = false)
        : label(label), selected(selected), open(open)
    {}

    GenericNodeDisplay(std::string& label)
        : label(label), selected(false), open(false)
    {}
    ~GenericNodeDisplay(){}

   std::string label;
   bool selected;
   bool open;
};

}

#endif