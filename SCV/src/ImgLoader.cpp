#include "stdafx.h"
#include "ImgLoader.h"
#include "FreeImage.h"

#include <cstring>

namespace scv {

ImgLoader::ImgLoader() {
#ifdef FREEIMAGE_LIB
   FreeImage_Initialise();
#endif
}

ImgLoader::~ImgLoader() {
#ifdef FREEIMAGE_LIB
   FreeImage_DeInitialise();
#endif
}

namespace {

static unsigned DLL_CALLCONV
read_proc_cb(void *buffer, unsigned size, unsigned count, fi_handle handle) {
   return fread(buffer, size, count, (FILE*)handle);
}

static int DLL_CALLCONV
seek_proc_cb(fi_handle handle, long offset, int origin) {
	return fseek((FILE*)handle, offset, origin);
}

static long DLL_CALLCONV
tell_proc_cb(fi_handle handle) {
   return ftell((FILE*)handle);
}

} // namespace

unsigned char* ImgLoader::loadImageToArray(const std::string &fileName, int *width, int *height) {

   FILE *f = fopen(fileName.c_str(), "rb");
   if (f == NULL) {
      std::cout << "ImageLoader: Image \"" << fileName << "\" not found."<< std::endl;
      return NULL;
   }

   FreeImageIO io;
   io.read_proc = read_proc_cb;
   io.write_proc = NULL;
   io.seek_proc = seek_proc_cb;
   io.tell_proc = tell_proc_cb;

   FREE_IMAGE_FORMAT format = FreeImage_GetFileTypeFromHandle(&io, f, 0);
   if (format == FIF_UNKNOWN)
      return NULL;

   FIBITMAP *image = FreeImage_LoadFromHandle(format, &io, f);
   if (image == NULL)
      return NULL;

   if (FreeImage_GetBPP(image) != 32) {
      FIBITMAP* new_image = FreeImage_ConvertTo32Bits(image);
      FreeImage_Unload(image);
      image = new_image;
   }

   *width = FreeImage_GetWidth(image);
   *height = FreeImage_GetHeight(image);

   BYTE* data = new BYTE[(*width) * (*height) * 4];
   BYTE* data_cur = data;

   for (int i = *height; i != 0; --i) {
      BYTE* line = FreeImage_GetScanLine(image, i-1);
      if (FreeImage_IsLittleEndian()) {
         for (int x = *width; x != 0; --x) {
            // BGRA -> RGBA
            *data_cur++ = line[2];
            *data_cur++ = line[1];
            *data_cur++ = line[0];
            *data_cur++ = line[3];
            line += 4;
         }

      } else {
         memcpy(data_cur, line, *width * 4);
         data_cur += *width * 4;
      }
   }

   FreeImage_Unload(image);
   fclose(f);

   return data;
}

} // namespace scv
