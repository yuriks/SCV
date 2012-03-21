#ifndef __PROPERTIE_OPTION_H__
#define __PROPERTIE_OPTION_H__

class Properties;

class PropertieOption {
public:
   ///////////////////////////////////////////////////////////
   enum Type { 
      EDITABLE_NUMERAL_TEXTFIELD, EDITABLE_TEXTFIELD,
      NUMERAL_TEXTFIELD, TEXTFIELD,
      EDITABLE_CHECKBOX
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   PropertieOption(Properties *host, std::string title, Type type);
   virtual ~PropertieOption(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   inline scv::Label *getLabel(void) const;
   inline scv::Component *getTarget(void) const;
   inline const std::string &getOption(void) const;
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void setValue(const std::string &str);
   void setValue(bool state);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   void onValueChange(const std::string &str);
   void onValueChange(bool state);
   ///////////////////////////////////////////////////////////

protected:
   ///////////////////////////////////////////////////////////
   class PropertieCheckBox : public scv::CheckBox {
   public:
      PropertieCheckBox(PropertieOption *host);
      virtual ~PropertieCheckBox(void);

      void onValueChange(void);

   protected:
      PropertieOption *_host;
   };
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   class PropertieTextField : public scv::TextField {
   public:
      PropertieTextField(PropertieOption *host, bool editable, bool allowOnlyNumbers);
      virtual ~PropertieTextField(void);

      void onKeyPressed(const scv::KeyEvent &evt);

   protected:
      PropertieOption *_host;
   };
   ///////////////////////////////////////////////////////////

   Type _type;

private:
   Properties *_host;
   scv::Label *_label;
   scv::Component *_target;
};
///////////////////////////////////////////////////////////

inline scv::Label *PropertieOption::getLabel(void) const {
   return _label;
}

inline scv::Component *PropertieOption::getTarget(void) const {
   return _target;
}

const std::string & PropertieOption::getOption(void) const {
   return _label->getString();
}

///////////////////////////////////////////////////////////

#endif //__PROPERTIE_OPTION_H__