#include "GenericNode.h"

namespace scv {

GenericNode::GenericNode(std::string data, int nodeFunction, std::vector<GenericNode> childs)
{
    _data = data;
    _nodeFunction = nodeFunction;
    _childs = childs;
    _opened = false;
}

GenericNode::GenericNode(std::string data, int nodeFunction)
{
    _data = data;
    _nodeFunction = nodeFunction;
    _childs.clear();
    _opened = false;
}

GenericNode::GenericNode(std::string data)
{
    _data = data;
    _nodeFunction = -1;
    _childs.clear();
    _opened = false;
}

GenericNode::~GenericNode(){/**/}



std::string GenericNode::getName()
{
    return _data;
}

int GenericNode::getNodeFunction()
{
    return _nodeFunction;
}

std::vector<GenericNode> GenericNode::getAllChilds()
{
    return _childs;
}

GenericNode* GenericNode::getChild(int pos)
{
    if(pos < _childs.size() && pos >= 0){
        return &_childs[pos];
    }else{
        return NULL;
    }
}

bool GenericNode::isOpened()
{
    return _opened;
}

void GenericNode::changeOpened()
{
    _opened = !_opened;
}

void GenericNode::setOpened(bool b)
{
    _opened = b;
}

void GenericNode::addChildNodeOnBack(GenericNode g)
{
    _childs.push_back(g);
}

void GenericNode::addChildNodeOnBegin(GenericNode g)
{
    std::vector<GenericNode> v;
    v.push_back(g);
    for(int i = 0 ; i < _childs.size();i++)
    {
        v.push_back(_childs[i]);
    }
    _childs = v;
}

}