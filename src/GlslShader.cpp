#include "stdafx.h"
#include "GlslShader.h"

namespace scv {

bool GlslShader::_initialized = false;
bool GlslShader::_shaderReady = false;

void GlslShader::setShaders(char *vert, char *frag) {
   char *vs,*fs;

   _vert = glCreateShader(GL_VERTEX_SHADER);
   _frag = glCreateShader(GL_FRAGMENT_SHADER);

   vs = textFileRead(vert);
   fs = textFileRead(frag);

   const char * vv = vs;
   const char * ff = fs;

   glShaderSource(_vert, 1, &vv, NULL);
   glShaderSource(_frag, 1, &ff, NULL);

   free(vs);
   free(fs);

   glCompileShader(_vert);
   glCompileShader(_frag);

   _program = glCreateProgram();

   glAttachShader(_program,_vert); //Um programa pode 0 ou mais Vertex Shaders e 0 ou mais fragment shader
   glAttachShader(_program,_frag); //caso nao tiver nenhum Vertex Shader, por exemplo, utiliza-se o pipeline fixo do OpenGL para esta funcionalidade

   glLinkProgram(_program);
}

//somente UM programa pode estar ativo a cada momento.
void GlslShader::setActive(bool active) {
   if(active)
      glUseProgram(_program);
   else
      glUseProgram(0); //desbilita o programa "corrente". Nao necessariamente eh o do proprio objeto.
}

GLint GlslShader::getUniformLocation(const std::string& theVar) {
   if (_uniformLocations.find(theVar)==_uniformLocations.end()) {
      GLint id=glGetUniformLocation(_program, theVar.c_str());
      _uniformLocations[theVar]=id;
      if (id == -1) {
         std::cout << "WARNING: getUniformLocation(\"" << theVar << "\") returns -1" << std::endl;
         return -1;
      }
   }
   return _uniformLocations[theVar];
}

GLint GlslShader::getAttribLocation(const std::string& theVar) {
   if (_attribLocations.find(theVar)==_attribLocations.end()) {
      GLint id=glGetAttribLocation(_program, theVar.c_str());
      _attribLocations[theVar]=id;
      if (id == -1) {
         std::cout << "WARNING: getAttribLocation(\"" << theVar << "\") returns -1" << std::endl;
         return -1;
      }
   }
   return _attribLocations[theVar];
}


GlslShader::GlslShader(char *vert, char *frag) {
   if (!_initialized) {
      std::cout<< "ERROR: Not initilized. call GlslShader::init()\n";
      exit(1);
   }

   if (!_shaderReady) {
      std::cout << "ERROR: Not shader compatible."<< std::endl;
      exit(1);
   }
   setShaders(vert, frag);

   printShaderInfoLog(_vert);
   printShaderInfoLog(_frag);
   printProgramInfoLog(_program);

   //http://www.delorie.com/gnu/docs/gcc/cpp_21.html
   //http://www.thescripts.com/forum/thread212429.html
   //http://www.codeguru.com/forum/showthread.php?t=231043
   //printf("\n%s  %d  %s  %s \n", __FILE__, __LINE__, __FUNCTION__, __TIMESTAMP__);

   //printOglError(__FILE__, __LINE__);
}

char *GlslShader::textFileRead(char *fn) {
   FILE *fp;
   char *content = NULL;

   int count=0;

   if (fn != NULL) {
      fp = fopen(fn,"rt");

      if (fp != NULL) {
         fseek(fp, 0, SEEK_END);
         count = ftell(fp);
         rewind(fp);

         if (count > 0) {
            content = (char *)malloc(sizeof(char) * (count+1));
            count = (int)fread(content,sizeof(char),count,fp);
            content[count] = '\0';
         }
         fclose(fp);
      } else {
         printf("\nFile %s not found", fn);
         getchar();
         exit(1);
      }
   }
   //printf("Arquivo %s %d = \n%s\n\n", fn, strlen(content), content);
   return content;
}

int GlslShader::printOglError(char *file, int line) {
   //
   // Returns 1 if an OpenGL error occurred, 0 otherwise.
   //
   GLenum glErr;
   int    retCode = 0;

   glErr = glGetError();
   while (glErr != GL_NO_ERROR) {
      printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
      retCode = 1;
      glErr = glGetError();
   }
   return retCode;
}

void GlslShader::printShaderInfoLog(GLuint obj) {
   int infologLength = 0;
   int charsWritten  = 0;
   char *infoLog;

   glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

   if (infologLength > 1) {
      infoLog = (char *)malloc(infologLength);
      glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
      printf("%s\n",infoLog);
      free(infoLog);
   }
}

void GlslShader::printProgramInfoLog(GLuint obj) {
   int infologLength = 0;
   int charsWritten  = 0;
   char *infoLog;

   glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

   if (infologLength > 1) {
      infoLog = (char *)malloc(infologLength);
      glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
      printf("%s\n",infoLog);
      free(infoLog);
   }
}


void GlslShader::init() {
   if (_initialized) return;

   _initialized = true;
   GLenum err = glewInit();
   if (GLEW_OK != err) {
      /* Problem: glewInit failed, something is seriously wrong. */
      //fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
      _shaderReady=false;
      return;
   }
   //fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

   if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
      _shaderReady = true;
   //printf("Ready for GLSL\n");
   else {
      //printf("Not totally ready :( \n");
      _shaderReady = false;
      //exit(1);
   }
   /*if (glewIsSupported("GL_VERSION_2_0"))
      printf("Ready for OpenGL 2.0\n");
   else {
      printf("OpenGL 2.0 not supported\n");
      exit(1);
   }*/
}

} // namespace scv