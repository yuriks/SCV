#ifndef __SCV_BUTTON_GROUP_H__
#define __SCV_BUTTON_GROUP_H__

namespace scv {

class StateButton;

/*! A group of mutually exclusive StateButtons.
 * If several StateButtons are added to the same ButtonGroup, it will ensure
 * that only one of those can be active at any given time. (Commonly used with
 * RadioButtons.)
 */
class ButtonGroup {
friend class StateButton;
public:

   /************************************************************************/
   /* Constructors                                                         */
   /************************************************************************/
   ButtonGroup(void);

   /************************************************************************/
   /* User Functions                                                       */
   /************************************************************************/
   /*! Returns the index of the currently active widget in the group. Widgets
    * are numbered from 0 in the order they have been added to the button
    * group. A value of -1 indicates that no widget is currently selected.
    */
   int getActive(void);

private:
   void update(StateButton *ptr);
   std::deque<StateButton*> _componentsArray;

};

} // namespace scv

#endif // __SCV_BUTTON_GROUP_H__