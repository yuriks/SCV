/*!
\file       TextFilter.h
\brief      Implementation of a Filter to the input text.
\author     SCV Team
*/

#ifndef __SCV_TEXT_FILTER_H__
#define __SCV_TEXT_FILTER_H__

namespace scv {

/*! A class that can be associated with a TextBox or a TextField to filter some characters.
 * \ingroup util
 */

class TextFilter {
public:

   TextFilter(void);

   /*! Causes the filter does not filter anything.
   */
   void allowAll(void);
   /*! Causes the filter just allows numbers.
   */
   void allowNumbers(void);
   /*! Causes the filter just allows letters.
   */
   void allowLetters(void);
   /*! Causes the filter also allows the characters specified in the argument.
   \param filter Characters that the filter will allow.
   */
   void allowThese(const std::string &filter);
   /*! Causes the filter allows nothing.
   */
   void denyAll(void);
   /*! Causes the filter to filter numbers.
   */
   void denyNumbers(void);
   /*! Causes the filter to filter letters.
   */
   void denyLetters(void);
   /*! Causes the filter to filter the characters specified in the argument.
   \param filter Characters that the filter will deny.
   */
   void denyThese(const std::string &filter);
   /*! Test if a character is filtered by the filter.
   \param character Character to be tested.
   */
   bool checkFilter(char character);

protected:

private:

   static const int s_printableCharacters = 94;
   static const int s_vectorDisplacement  = 32;
   bool _filter[s_printableCharacters + 1];
};

} // namespace scv

#endif // __SCV_TEXT_FILTER_H__
