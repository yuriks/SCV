#include "GTree.h"
#include "TreeModel.h"

#include "Kernel.h"
#include "Image.h"
#include "stdafx.h"

namespace scv{

TreeModel::TreeModel(void) {
}

TreeModel::~TreeModel(void) {
}

void TreeModel::getNamesInTree(std::vector<GInfoNode> &m_nodes, GTree* tree)
{
   GInfoNode GNodeAux;
   for(GNode *aux = tree->init->first ; aux != NULL ; aux = aux->next)
   {
      GNodeAux.setName(aux->name);
      GNodeAux.setHaveChilds(aux->ifHaveFolders());
      GNodeAux.setType(aux->getType());
      if(aux->first != NULL){
         GNodeAux.setOpen(true);
      }else {GNodeAux.setOpen(false);}
      m_nodes.push_back(GNodeAux);
      aux->getChildNames(m_nodes, "   ");
   }

}

#ifdef _WIN32
/****Base Codes From: http://msdn.microsoft.com/en-us/library/ **************/
void DisplayVolumePaths(__in PWCHAR VolumeName, std::vector<std::string> &dirNames)
{
   DWORD  CharCount = MAX_PATH + 1;
   PWCHAR Names     = NULL;
   PWCHAR NameIdx   = NULL;
   BOOL   Success   = FALSE;

   while(true)
   {
      //  Allocate a buffer to hold the paths.
      Names = (PWCHAR) new BYTE [CharCount * sizeof(WCHAR)];

      if ( !Names )
      {
         //  If memory can't be allocated, return.
         return;
      }

      //  Obtain all of the paths
      //  for this volume.
      Success = GetVolumePathNamesForVolumeNameW(VolumeName, Names, CharCount, &CharCount);

      if ( Success )
      {
         break;
      }

      if ( GetLastError() != ERROR_MORE_DATA )
      {
         break;
      }

      //  Try again with the
      //  new suggested size.
      delete [] Names;
      Names = NULL;
   }

   if ( Success )
   {
      //  Display the various paths.
      for ( NameIdx = Names;
         NameIdx[0] != L'\0';
         NameIdx += wcslen(NameIdx) + 1 )
      {
         /*Insert the names in the vec*/
         char ala[MAX_PATH];
         wcstombs(ala,NameIdx,MAX_PATH);
         dirNames.push_back(ala);
      }
   }

   if ( Names != NULL )
   {
      delete [] Names;
      Names = NULL;
   }
   return;
}

void TreeModel::getDirs(std::vector<std::string> &dirNames)
{
   DWORD  CharCount            = 0;
   WCHAR  DeviceName[MAX_PATH] = L"";
   DWORD  Error                = ERROR_SUCCESS;
   HANDLE FindHandle           = INVALID_HANDLE_VALUE;
   BOOL   Found                = FALSE;
   size_t Index                = 0;
   BOOL   Success              = FALSE;
   WCHAR  VolumeName[MAX_PATH] = L"";

   //  Enumerate all volumes in the system.
   FindHandle = FindFirstVolumeW(VolumeName, ARRAYSIZE(VolumeName));
   if (FindHandle == INVALID_HANDLE_VALUE)
   {
      Error = GetLastError();
      return;
   }

   while(true)
   {
   //  Skip the \\?\ prefix and remove the trailing backslash.
   Index = wcslen(VolumeName) - 1;

   if (VolumeName[0]     != L'\\' ||
   VolumeName[1]     != L'\\' ||
   VolumeName[2]     != L'?'  ||
   VolumeName[3]     != L'\\' ||
   VolumeName[Index] != L'\\')
   {
      Error = ERROR_BAD_PATHNAME;
      break;
   }
   //  QueryDosDeviceW does not allow a trailing backslash,
   //  so temporarily remove it.
   VolumeName[Index] = L'\0';

   CharCount = QueryDosDeviceW(&VolumeName[4], DeviceName, ARRAYSIZE(DeviceName));

   VolumeName[Index] = L'\\';

   if ( CharCount == 0 )
   {
      Error = GetLastError();
      break;
   }
      DisplayVolumePaths(VolumeName, dirNames);

   //  Move on to the next volume.
   Success = FindNextVolumeW(FindHandle, VolumeName, ARRAYSIZE(VolumeName));

   if ( !Success )
   {
      Error = GetLastError();

      if (Error != ERROR_NO_MORE_FILES)
      {
         break;
      }

      //  Finished iterating
      //  through all the volumes.
      Error = ERROR_SUCCESS;
      break;
      }
   }

   FindVolumeClose(FindHandle);
   FindHandle = INVALID_HANDLE_VALUE;
}

bool TreeModel::getIfHaveFolders(const char* dir, TW_types view)
{
   WIN32_FIND_DATA ffd; //Have the informations about each file or folder
   WIN32_FIND_DATA auxffd;
   TCHAR szDir[MAX_PATH];
   size_t length_of_arg;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;

   DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, dir, -1, NULL, 0);
   wchar_t *pwText;
   pwText = new wchar_t[dwNum];

   MultiByteToWideChar (CP_ACP, 0, dir, -1, pwText, dwNum );

   StringCchLength(pwText, MAX_PATH, &length_of_arg);

   if (length_of_arg > (MAX_PATH - 3))
   {
      delete[] pwText;
      return false;
   }

   StringCchCopy(szDir, MAX_PATH, pwText);
   StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

   hFind = FindFirstFile(szDir, &ffd);


   if (INVALID_HANDLE_VALUE == hFind)
   {
      FindClose(hFind);
      delete[] pwText;
      return false;
   }
   if(view == TW_ONLY_FOLDERS){
      do
      {     
         GInfoNode nodeAux;
         TCHAR szDirAux[MAX_PATH];
         StringCchCopy(szDirAux, MAX_PATH, pwText);
         StringCchCat(szDirAux, MAX_PATH, ffd.cFileName);
         StringCchCat(szDirAux, MAX_PATH, TEXT("/"));
         StringCchCat(szDirAux, MAX_PATH, TEXT("\\*"))  ;
               
         if ( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY 
            && (wcscmp(ffd.cFileName,TEXT("..")) == 1)
            && (wcscmp(ffd.cFileName,TEXT(".")) == 1) 
            && INVALID_HANDLE_VALUE != FindFirstFile(szDirAux, &auxffd)) //se for diretório
         {
            FindClose(hFind);
            delete[] pwText;
            return true;
         }
      } while (FindNextFile(hFind, &ffd) != 0);
   } else if (view == TW_FOLDERS_AND_FILES)
   {
      do
      {     
         GInfoNode nodeAux;
         TCHAR szDirAux[MAX_PATH];
         StringCchCopy(szDirAux, MAX_PATH, pwText);
         StringCchCat(szDirAux, MAX_PATH, ffd.cFileName);
         StringCchCat(szDirAux, MAX_PATH, TEXT("/"));
         StringCchCat(szDirAux, MAX_PATH, TEXT("\\*"))  ;
               
         if ((wcscmp(ffd.cFileName,TEXT("..")) == 1)
            && (wcscmp(ffd.cFileName,TEXT(".")) == 1) ) //se for diretório
         {
            FindClose(hFind);
            delete[] pwText;
            return true;
         }
      } while (FindNextFile(hFind, &ffd) != 0);

   }

   FindClose(hFind);
   delete[] pwText;
   return false;
}

void TreeModel::getFolders(const char* dir, std::vector<GInfoNode> &m_nodes, TW_types view)
{
   m_nodes.clear();
   WIN32_FIND_DATA ffd; //Have the informations about each file or folder
   WIN32_FIND_DATA auxffd;
   LARGE_INTEGER filesize;
   TCHAR szDir[MAX_PATH];
   size_t length_of_arg;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;

   DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, dir, -1, NULL, 0);
   wchar_t *pwText;
   pwText = new wchar_t[dwNum];

   MultiByteToWideChar (CP_ACP, 0, dir, -1, pwText, dwNum );

   // If the directory is not specifiedx as a command-line argument,
   // print usage.
   // Check that the input path plus 3 is not longer than MAX_PATH.
   // Three characters are for the "\*" plus NULL appended below.


   StringCchLength(pwText, MAX_PATH, &length_of_arg);

   if (length_of_arg > (MAX_PATH - 3))
   {
      delete[] pwText;
      return;
   }

   // Prepare string for use with FindFile functions.  First, copy the
   // string to a buffer, then append '\*' to the directory name.

   StringCchCopy(szDir, MAX_PATH, pwText);
   StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

   // Find the first file in the directory.

   hFind = FindFirstFile(szDir, &ffd);

   if (INVALID_HANDLE_VALUE == hFind)
   {
      delete[] pwText;
      return;
   }

   GInfoNode nodeAux;
   std::vector<GInfoNode> vFiles;
   // List all the files in the directory.
   if(view == TW_ONLY_FOLDERS)
   {
      do
      {
         GInfoNode nodeAux;
         TCHAR szDirAux[MAX_PATH];
         StringCchCopy(szDirAux, MAX_PATH, pwText);
         StringCchCat(szDirAux, MAX_PATH, ffd.cFileName);
         StringCchCat(szDirAux, MAX_PATH, TEXT("/"));
         StringCchCat(szDirAux, MAX_PATH, TEXT("\\*"))  ;

         if ( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
            && (wcscmp(ffd.cFileName,TEXT("..")) == 1)
            && (wcscmp(ffd.cFileName,TEXT(".")) == 1)
            && INVALID_HANDLE_VALUE != FindFirstFile(szDirAux, &auxffd)) //se for diretório
         {
            int found = (int)wcslen(ffd.cFileName);
            char *a = new char[found+1];
            wcstombs(a,ffd.cFileName,256);
            nodeAux.setName(a);
            nodeAux.setType(T_FOLDER);
            m_nodes.push_back(nodeAux);
            delete[] a;
         }
      } while (FindNextFile(hFind, &ffd) != 0);
   } else if(view == TW_FOLDERS_AND_FILES)
      do
      {
         TCHAR szDirAux[MAX_PATH];
         StringCchCopy(szDirAux, MAX_PATH, pwText);
         StringCchCat(szDirAux, MAX_PATH, ffd.cFileName);
         StringCchCat(szDirAux, MAX_PATH, TEXT("/"));
         StringCchCat(szDirAux, MAX_PATH, TEXT("\\*"))  ;
         if((wcscmp(ffd.cFileName,TEXT("..")) == 1)
            && (wcscmp(ffd.cFileName,TEXT(".")) == 1))
         {

            if ( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
                && INVALID_HANDLE_VALUE != FindFirstFile(szDirAux, &auxffd)) //se for diretório
            {
               int found = (int)wcslen(ffd.cFileName);
               char *a = new char[found+1];
               wcstombs(a,ffd.cFileName,256);
               nodeAux.setName(a);
               nodeAux.setType(T_FOLDER);
               m_nodes.push_back(nodeAux);
               delete[] a;
            } else
            {
               filesize.LowPart = ffd.nFileSizeLow;
               filesize.HighPart = ffd.nFileSizeHigh;
               int a = wcsnlen(ffd.cFileName,MAX_PATH);
               int found = (int)wcslen(ffd.cFileName);
               char *an = new char[found+1];
               wcstombs(an,ffd.cFileName,256);
               nodeAux.setName(an);
               nodeAux.setType(T_FILE);
               vFiles.push_back(nodeAux);
               delete[] an;
            }
         }
      } while (FindNextFile(hFind, &ffd) != 0);
   {

   }
   for(int i = 0 ; i < vFiles.size() ; i++)
   {
      m_nodes.push_back(vFiles[i]);
   }

   FindClose(hFind);
   delete[] pwText;
}
/****************************************************************************/
#else
void TreeModel::getNFolders (std::string dir)
{
   int res = 0;
   DIR *dp;
   struct dirent *dirp;
   if((dp  = opendir(dir.c_str())) == NULL) {
      std::cout << "Error(" << errno << ") opening " << dir << std::endl;
      return errno;
   }

   while ((dirp = readdir(dp)) != NULL) {
      if(dirp->d_type == 4 && strcmp(dirp->d_name, ".") == 1
         && strcmp(dirp->d_name, "..") == 1
         && dirp->d_name[0] != '.')
      { res++; }
   }
   closedir(dp);
   return res;
}

void TreeModel::getFolders (std::string dir, std::vector<std::string> &files)
{
   DIR *dp;
   struct dirent *dirp;
   if((dp  = opendir(dir.c_str())) == NULL) {
      std::cout << "Error(" << errno << ") opening " << dir << std::endl;
      return errno;
   }

   while ((dirp = readdir(dp)) != NULL) {
      if(dirp->d_type == 4 && strcmp(dirp->d_name, ".") == 1
         && strcmp(dirp->d_name, "..") == 1
         && dirp->d_name[0] != '.')
      { files.push_back(std::string(dirp->d_name)); }
   }
   closedir(dp);
}

#endif
}
