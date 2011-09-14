#include "stdafx.h"

#include "SCVObject.h"

#include <cassert>
#include <algorithm>

namespace scv {

SCVObject::SCVObject(SCVObject* parent)
   : _parent(NULL), _isComponent(false) {
	setParent(parent);
}

SCVObject::~SCVObject() {
	setParent(NULL);

	for (ObjectList::iterator i = _children.begin(); i != _children.end(); ++i) {
		delete *i;
	}
}

void SCVObject::setParent(SCVObject* parent) {
	if (_parent != NULL) {
		_parent->_children.remove(this);
		_parent = NULL;
	}

	assert(_parent == NULL);

	_parent = parent;

	if (_parent != NULL) {
		_parent->_children.push_back(this);
	}
}

void SCVObject::addChild(SCVObject* child) {
	if (child->getParent ()!= NULL) {
		// TODO: Warn about adding an object with an existing parent
		assert(false);
	} else {
		child->setParent(this);
	}

	assert(std::find(getChildren().begin(), getChildren().end(), child) != getChildren().end());
}

void SCVObject::pullChildToTop(const ObjectList::const_iterator& child) {
   SCVObject* removed_child = *child;
   _children.erase(child);
   _children.push_back(removed_child);
}

} // namespace scv
