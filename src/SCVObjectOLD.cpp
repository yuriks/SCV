#include "stdafx.h"

#include "SCVObjectOLD.h"

namespace scv {

DummyClass::DummyClass(DummyClass* parent) : _parent(NULL), _isComponent(false) {
	setParent(parent);
}

DummyClass::~DummyClass() {
	setParent(NULL);

	for (ObjectList::iterator iter = _children.begin(); iter != _children.end(); ++iter) {
		delete *iter;
	}
}

void DummyClass::setParent(DummyClass* parent) {
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

void DummyClass::addChild(DummyClass* child) {
	if (child->getParent ()!= NULL) {
		// TODO: Warn about adding an object with an existing parent
		assert(false);
	} else {
		child->setParent(this);
	}

	assert(std::find(getChildren().begin(), getChildren().end(), child) != getChildren().end());
}

void DummyClass::pullChildToTop(const ObjectList::const_iterator& child) {
   DummyClass* removed_child = *child;
   _children.erase(child);
   _children.push_back(removed_child);
}

} // namespace scv
