/*!
\file       SCVObject.h
\brief      Base SCV object implementation.
\author     SCV Team
*/

#ifndef __SCV_SCVOBJECT_H__
#define __SCV_SCVOBJECT_H__

namespace scv {

/*! Base Class of SCV Objects
 * This class creates reference to all children and to the father of this object.
 * This allows objects to be deleted without leaving invalid pointers in its parents.
 *\ingroup internal
 */

class SCVObjectOLD {
public:
	typedef std::list<SCVObjectOLD*> ObjectList;

	SCVObjectOLD(SCVObjectOLD* parent = NULL);
	virtual ~SCVObjectOLD();

   bool              isComponent() const;
	void              setParent  (SCVObjectOLD* parent);
	SCVObjectOLD *       getParent  () const;
	const ObjectList& getChildren() const;


protected:

	void              addChild      (SCVObjectOLD* child);
   void              pullChildToTop(const ObjectList::const_iterator& child);

private:
	SCVObjectOLD* _parent;
	ObjectList _children;

   bool _isComponent;

   friend class SCVObject;
};


inline SCVObjectOLD* SCVObjectOLD::getParent() const {
	return _parent;
}

inline const SCVObjectOLD::ObjectList& SCVObjectOLD::getChildren() const {
	return _children;
}

inline bool SCVObjectOLD::isComponent() const {
   return _isComponent;
}

} // namespace scv

#endif //  __SCV_SCVOBJECT_H__
