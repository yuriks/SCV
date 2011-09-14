/*!
\file       ColorPicker.h
\brief      Implementation of a Color Picker widget.
\author     SCV Team
*/

#ifndef __SCV_COLORPICKER_H__
#define __SCV_COLORPICKER_H__

#ifndef DOXYGEN_SKIP_THIS
#include "MatrixTemplate.h"
#include "ToggleButton.h"
#include "Panel.h"
#include "Spinner.h"
#endif // DOXYGEN_SKIP_THIS


namespace scv {

/*! A color chooser, made to preview and test color values.
 * \ingroup widgets
 */

class ColorPicker : public MatrixTemplate<ColorRGBA>, public Panel {
public:


   /*! Constructor
   \param p The upper left corner of the component.
   */
   ColorPicker(const scv::Point &p);
   /*! Destructor
   */
   ~ColorPicker();

   virtual void onMouseClick(const scv::MouseEvent &evt);
   virtual void onMouseHold(const scv::MouseEvent &evt);
   virtual void onMouseOver(const scv::MouseEvent &evt);
   virtual void onMouseUp(const scv::MouseEvent &evt);
   virtual void onMouseWheel(const scv::MouseEvent &evt);
   virtual void onKeyPressed(const scv::KeyEvent &evt);
   virtual void onKeyUp(const scv::KeyEvent &evt);
   virtual void onResizing(void);
   virtual void onDragging(void);
   virtual void onColorChange(void);


   //! Get the component width
   int getWidth(void) const;
   //! Get the component height
   int getHeight(void) const;
   //! Get the current color selected
   ColorRGBA getColor(void) const;
   //! Set the current color
   /*!
   \param color New color
   */
   void setColor(const ColorRGBA &color);

   virtual void setDraggable(bool state);
   virtual void setResizable(bool state);

   //! Mouse function of the component.
   /*!
   IMPORTANT: This is an internal function and don't must be called!
   */
   void processMouse(const scv::MouseEvent &evt);
   virtual void display(void);

private:
   class EyeDropper : public ToggleButton {
   public:
      EyeDropper(ColorPicker *picker, const scv::Point &p1, const scv::Point &p2, const std::string &str) :
         ToggleButton(p1, p2, false, str), _picker(picker) {}
         void onMouseUp(const scv::MouseEvent &evt) {
            _picker->_pickerWaitingColor = true;
         }
   private:
      ColorPicker *_picker;
   };

   void createColors();
   void createTexture(void);
   void refreshColor(void);
   void setSpinsColor(void);

   Point foundHSL(void);
   Point _currentColorPosition;

   bool _pickerWaitingColor;

   double _saturation;
   ColorRGBA _currentColor;
   ColorRGBA _currentPickerColor;

   Spinner *_rgbs[4];
   EyeDropper *_btPicker;

   ComponentTexture * _cpTexture;

};

} // namespace scv


#endif // __SCV_COLORPICKER_H__