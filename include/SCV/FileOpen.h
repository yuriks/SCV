/*!
\file       FileOpen.h
\brief      Implementation of a File Open.
\author     SCV Team
*/

#ifndef __SCV_FILE_OPEN_H__
#define __SCV_FILE_OPEN_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! This class calls a FileOpenDialog from the system.
 * \ingroup util
 */

class FileOpen : public Singleton<FileOpen> {
   friend class Singleton<FileOpen>;

public:
   /*! Constructor of FileOpen.*/
   FileOpen(void);
   /*! Destructor of FileOpen just
    delete the path.*/
   ~FileOpen(void);

   /*! Create a open file dialog
    for user choose the file.*/
   void getItem();

   /*! Return the path of the
    last file selected.*/
   std::string getSpath();

private:
   char* path;
};

} // namespace scv

#endif