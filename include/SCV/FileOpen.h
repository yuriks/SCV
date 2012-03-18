/*!
\file       FileOpen.h
\brief      Implementation of a File Open.
\author     SCV Team
*/

#ifndef __SCV_FILE_OPEN_H__
#define __SCV_FILE_OPEN_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"

#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! This class calls a FileOpenDialog from the system.
 * \ingroup util
 */

class FileOpen : public Singleton<FileOpen> {
   friend class Singleton<FileOpen>;

public:
   ~FileOpen(void);

   /*! Create a open file dialog
    for user choose the file.*/
   void showDialog();

   /*! Return the path of the
    last file selected.*/
   std::string getFilePath();

private:
   char* path;
};

} // namespace scv

#endif