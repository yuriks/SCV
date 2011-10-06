#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template <typename T>
class Singleton {
 public:
    static void setInstance(T *instance) {
       _instance = instance;
    };

   static T* getInstance() {
      if (_instance == 0) _instance = new T;
      return _instance;
   };

   static void destroyInstance() {	
      delete _instance;
      _instance = 0;
   };

 protected:
   Singleton(void) {
   };
   virtual ~Singleton(void) {
   };

   Singleton(const Singleton& source) {
   };

   static T* _instance;
};

template <typename T> T* Singleton<T>::_instance = 0;

#endif // ! defined __SINGLETON_H__
