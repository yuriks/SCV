#ifndef __SCV_DYNAMIC_CAST_ITERATOR_H__
#define __SCV_DYNAMIC_CAST_ITERATOR_H__

#ifndef DOXYGEN_SKIP_THIS
#include "ComponentInterface.h"
#endif // DOXYGEN_SKIP_THIS

template <typename TargetClass, typename Iter>
class DynamicCastIterator {
public:
   DynamicCastIterator(const Iter& iter, const Iter& iter_end)
      : wrapped_iter(iter), wrapped_iter_end(iter_end), casted(0) {
         skipInvalidForward();
   }

   template <typename T>
   DynamicCastIterator(T& container)
      : wrapped_iter(container.begin()), wrapped_iter_end(container.end()), casted(0) {
         skipInvalidForward();
   }

   DynamicCastIterator& operator++() {
      ++wrapped_iter;
      skipInvalidForward();

      return *this;
   }

   TargetClass* operator*() {
      if (valid())
         return casted;
      else
         return 0;
   }

   TargetClass* operator->() {
      return **this;
   }

   bool valid() const {
      return wrapped_iter != wrapped_iter_end;
   }

   Iter base() const {
      return wrapped_iter;
   }

   bool operator==(const DynamicCastIterator& o) const {
      return wrapped_iter == o.wrapped_iter;
   }

   bool operator==(const Iter& o) const {
      return wrapped_iter == o;
   }

   bool operator!=(const DynamicCastIterator& o) const {
      return !(*this == o);
   }

   bool operator!=(const Iter& o) const {
      return !(*this == o);
   }

private:
   void skipInvalidForward() {
      while (wrapped_iter != wrapped_iter_end) {
         casted = dynamic_cast<TargetClass*>(*wrapped_iter);
         if (casted == 0)
            ++wrapped_iter;
         else
            break;
      };
   }

   Iter wrapped_iter;
   Iter wrapped_iter_end;
   TargetClass* casted;
};

template <typename Iter>
class DynamicCastIterator<scv::ComponentInterface, Iter> {
public:
   DynamicCastIterator(const Iter& iter, const Iter& iter_end)
      : wrapped_iter(iter), wrapped_iter_end(iter_end) {
         skipInvalidForward();
   }

   template <typename T>
   DynamicCastIterator(T& container)
      : wrapped_iter(container.begin()), wrapped_iter_end(container.end()) {
         skipInvalidForward();
   }

   DynamicCastIterator& operator++() {
      ++wrapped_iter;
      skipInvalidForward();

      return *this;
   }

   scv::ComponentInterface* operator*() {
      if (valid())
         return static_cast<scv::ComponentInterface*>(*wrapped_iter);
      else
         return 0;
   }

   scv::ComponentInterface* operator->() {
      return **this;
   }

   bool valid() const {
      return wrapped_iter != wrapped_iter_end;
   }

   Iter base() const {
      return wrapped_iter;
   }

   bool operator==(const DynamicCastIterator& o) const {
      return wrapped_iter == o.wrapped_iter;
   }

   bool operator==(const Iter& o) const {
      return wrapped_iter == o;
   }

   bool operator!=(const DynamicCastIterator& o) const {
      return !(*this == o);
   }

   bool operator!=(const Iter& o) const {
      return !(*this == o);
   }

private:
   void skipInvalidForward() {
      while (wrapped_iter != wrapped_iter_end) {
         if ((*wrapped_iter)->isComponent())
            break;
         else
            ++wrapped_iter;
      };
   }

   Iter wrapped_iter;
   Iter wrapped_iter_end;
};

#endif // __SCV_DYNAMIC_CAST_ITERATOR_H__