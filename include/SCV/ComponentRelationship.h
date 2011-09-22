#ifndef __SCV_COMPONENT_RELATIONSHIP_H__
#define __SCV_COMPONENT_RELATIONSHIP_H__

namespace scv {

class ComponentRelationship {
public:
   //////////////////////////////////////////////////////////
   typedef std::list<ComponentRelationship> List;
   //////////////////////////////////////////////////////////

   void setParent(ComponentRelationship *parent);   
   inline const ComponentRelationship *getParent(void) const;

   inline const ComponentRelationship::List &getChildren(void) const;

   void addChild(ComponentRelationship *object);
   void removeChild(ComponentRelationship *object);

   void pullChildToTop(ComponentRelationship *child);

   bool hasChild(ComponentRelationship *child) const;

protected:
   ComponentRelationship *_parent;
   ComponentRelationship::List _children;   
private:
};

} //namespace scv

#endif //__SCV_COMPONENT_RELATIONSHIP_H__