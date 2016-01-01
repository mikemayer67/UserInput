#ifndef _UIVALUE_H_
#define _UIVALUE_H_

#include "types.h"
#include "util.h"

class UIValue
{
  public:
    UIValue(void) : myUsed(false), myLineNo(-1), myLine("") {}

    UIValue(const StringList_t &values, int lineno, std::string line)
      : myUsed(false), myLineNo(lineno), myLine(line)
    {
      myValues = values;
    }

    void setUsed(void) const { myUsed=true; }

    bool        isUsed(void)      const { return myUsed; }
    int         line_number(void) const { return myLineNo; }
    std::string input_line(void)  const { return myLine; }

    IntSet_t    getIntSet(void) const;
    StringSet_t getStringSet(void) const;
    NumSet_t    getNumSet(void) const;

  private:
    StringList_t myValues;

    mutable bool myUsed;
    int          myLineNo;
    std::string  myLine;
};

#endif // _UIVALUE_H_
