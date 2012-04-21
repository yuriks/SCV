#ifndef __SCV_IMG_LOADER_H__
#define __SCV_IMG_LOADER_H__

#ifndef DOXYGEN_SKIP_THIS
#include "Singleton.h"
#endif // DOXYGEN_SKIP_THIS

namespace scv {

/*! Gets the image information.
\return Array with RGBA colors or nullptr if loading failed. Should be freed by freeImageData()
\param fileName Location of image in your computer.
\param witdh An integer pointer to receive the witdh of the image by reference.
\param height An integer pointer to receive the height of the image by reference.
*/
unsigned char* loadImageToArray(const std::string &fileName, /* out */ int* witdh, /* out */ int* height);

/*! Frees image buffer.
\param data A buffer returned by loadImageToArray()
*/
void freeImageData(unsigned char* data);

} // namespace scv

#endif // __SCV_IMG_LOADER_H__