/*!
\file       singleton.h
\brief      Implementation of the Singleton template class.
\author     Brian van der Beek
*/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

//! Template class for creating singleton objects.

/*!
When the static Instance() method is called for the first time, the singleton
object is created. Every sequential call returns a reference to this instance.
The class instance can be destroyed by calling the DestroyInstance() method.
*/
template <typename T>
class Singleton {
 public:

   //! Gets a reference to the instance of the singleton class.

   /*!
   \return A reference to the instance of the singleton class.
   If there is no instance of the class yet, one will be created.
   */
   static T* getInstance() {
      if (_instance == 0) _instance = new T;
      return _instance;
   };

   //! Destroys the singleton class instance.

   /*!
   Be aware that all references to the single class instance will be
   invalid after this method has been executed!
   */
   static void destroyInstance() {	
      delete _instance;
      _instance = 0;
   };

 protected:

   // shield the constructor and destructor to prevent outside sources
   // from creating or destroying a CSingleton instance.

   //! Default constructor.
   Singleton() {
   };

   //! Destructor.
   virtual ~Singleton() {
   };

   //! Copy constructor.
   Singleton(const Singleton& source) {
   };

   static T* _instance; //!< singleton class instance
};

//! static class member initialization.
template <typename T> T* Singleton<T>::_instance = 0;

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#endif // ! defined __SINGLETON_H__
