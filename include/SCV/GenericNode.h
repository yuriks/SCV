#ifndef _SCV_GENERIC_NODE_H_
#define _SCV_GENERIC_NODE_H_

/*!
\file       GenericNode.h
\brief      Implementation of GenericNode.
\author     SCV Team
*/

namespace scv {

class GenericNode
{
public:
    GenericNode(std::string data, int nodeFunction, std::vector<GenericNode> childs);
    GenericNode(std::string data, int nodeFunction);
    GenericNode(std::string data);
    ~GenericNode();

    std::string getName();
    int getNodeFunction();
    std::vector<GenericNode> getAllChilds();
    GenericNode* getChild(int pos);
    bool isOpened();
    void changeOpened();
    void setOpened(bool b);
    void addChildNodeOnBack(GenericNode);
    void addChildNodeOnBegin(GenericNode);

private:
   std::string _data;
   int _nodeFunction;
   std::vector<GenericNode> _childs;
   bool _opened;
};

}

#endif