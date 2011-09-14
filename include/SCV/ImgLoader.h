#ifndef __SCV_IMG_LOADER_H__
#define __SCV_IMG_LOADER_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#include <string>
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! This class implements a image loader.
 * \ingroup util
 */

class ImgLoader : public Singleton<ImgLoader> {
friend class Singleton<ImgLoader>;
public:

   /*! Gets the image information.
   \return Array with RGBA colors.
   \param fileName Location of image in your computer.
   \param witdh A integer pointer to receive the witdh of the image by reference.
   \param height A integer pointer to receive the height of the image by reference.
   */
   unsigned char* loadImageToArray(const std::string &fileName, /* out */ int* witdh, /* out */ int* height);

private:
   ImgLoader();
   ~ImgLoader();

   // Prevent copy-construction or assignment
   ImgLoader(const ImgLoader&);
   ImgLoader& operator=(const ImgLoader&);

};

} // namespace scv

#endif // __SCV_IMG_LOADER_H__