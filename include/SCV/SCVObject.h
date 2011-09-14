/*!
\file       SCVObject.h
\brief      Base SCV object implementation.
\author     SCV Team
*/

#ifndef __SCV_SCVOBJECT_H__
#define __SCV_SCVOBJECT_H__

#include <list>

namespace scv {

/*! Base Class of SCV Objects
 * This class creates reference to all children and to the father of this object.
 * This allows objects to be deleted without leaving invalid pointers in its parents.
 *\ingroup internal
 */

class SCVObject {
public:
	typedef std::list<SCVObject*> ObjectList;

	SCVObject(SCVObject* parent = NULL);
	virtual ~SCVObject();

   bool              isComponent() const;
	void              setParent  (SCVObject* parent);
	SCVObject *       getParent  () const;
	const ObjectList& getChildren() const;


protected:

	void              addChild      (SCVObject* child);
   void              pullChildToTop(const ObjectList::const_iterator& child);

private:
	SCVObject* _parent;
	ObjectList _children;

   bool _isComponent;

   friend class ComponentInterface;
};


inline SCVObject* SCVObject::getParent() const {
	return _parent;
}

inline const SCVObject::ObjectList& SCVObject::getChildren() const {
	return _children;
}

inline bool SCVObject::isComponent() const {
   return _isComponent;
}

} // namespace scv

#endif //  __SCV_SCVOBJECT_H__
