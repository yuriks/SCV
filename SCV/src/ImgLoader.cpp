#include "stdafx.h"
#include "ImgLoader.h"
#include "stb_image.h"

namespace scv {

unsigned char* loadImageToArray(const std::string &fileName, int *width, int *height) {
   int comp;
   unsigned char* data = stbi_load(fileName.c_str(), width, height, &comp, 4);

   if (data == nullptr) {
      std::cerr << "ImageLoader: " << stbi_failure_reason() << std::endl;
   }

   return data;
}

void freeImageData(unsigned char* data) {
   stbi_image_free(data);
}

} // namespace scv
