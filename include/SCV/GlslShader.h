/*!
\file       GlslShader.h
\brief      Implementation of a Glsl Shader Class.
\author     SCV Team
*/

#ifndef __SCV_GLSLSHADER_H__
#define __SCV_GLSLSHADER_H__

namespace scv {

/*! This class implements a basic shader functions.
 * \ingroup util
 */

class GlslShader {
public:

   /*! Constructor
   \param vert File path of the vertice file code.
   \param frag File path of the fragment file code.
   */
   GlslShader(char *vert, char *frag);
   //! Initializes the shared program.
   static void init();
   //! Activates and Deactivates the shader
   void setActive(bool);
   /*! Return the location of the uniform variable.
   \param theVar Variable.
   */
   GLint getUniformLocation(const std::string& theVar);
   /*! Return the location of the attribute variable.
   \param theVar Variable.
   */
   GLint getAttribLocation(const std::string& theVar);
   //! Verifies if the shader is ready.
   static inline bool isReady(void) {
      return _shaderReady && _initialized;
   }

private:
   static bool _initialized;
   static bool _shaderReady;
   GLuint _program, _frag, _vert;
   std::map<std::string, GLuint> _uniformLocations,_attribLocations;
   void setShaders(char *vert, char *frag);
   char *textFileRead(char *fn);
   int  printOglError(char *file, int line);
   void printProgramInfoLog(GLuint obj);
   void printShaderInfoLog(GLuint obj);
};

} // namespace scv

#endif // __SCV_GLSLSHADER_H__