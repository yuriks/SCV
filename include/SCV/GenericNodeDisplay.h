#ifndef _GENERIC_NODE_DISPLAY_
#define _GENERIC_NODE_DISPLAY_

namespace scv {

struct GenericNodeDisplay
{
    GenericNodeDisplay(std::string& label, bool open, int spaces, bool selected = false)
        : label(label), selected(selected), spaces(spaces), open(open) 
    {}

    GenericNodeDisplay(std::string& label, int spaces)
        : label(label), spaces(spaces), selected(false), open(false)
    {}

    GenericNodeDisplay(std::string& label)
        : label(label), spaces(0), selected(false), open(false)
    {}
    ~GenericNodeDisplay(){}

   std::string label;
   bool selected;
   bool open;
   int spaces;
};

}

#endif