#ifndef __PROPERTIE_OPTION_H__
#define __PROPERTIE_OPTION_H__

class Properties;

class PropertieOption : public scv::Panel {
public:
   enum Type {
      EDITABLE_TEXTFIELD, TEXTFIELD, EDITABLE_CHECKBOX
   };

   PropertieOption(Properties *host, std::string title, Type type);
   virtual ~PropertieOption(void);
   void onValueChange(const std::string &str);
   void onValueChange(bool state);

protected:
   class PropertieCheckBox : public scv::CheckBox {
   public:
      PropertieCheckBox(PropertieOption *host);
      virtual ~PropertieCheckBox(void);

      void onValueChange(void);

   protected:
      PropertieOption *_host;
   };

   class PropertieTextField : public scv::TextField {
   public:
      PropertieTextField(PropertieOption *host);
      virtual ~PropertieTextField(void);

      void onKeyUp(const scv::KeyEvent &evt);

   protected:
      PropertieOption *_host;
   };

   Type _type;
private:
   Properties *_host;
};

#endif //__PROPERTIE_OPTION_H__