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

    std::string input_line(void) const
    {
      return std::string("[line ") + util::int2str(myLineNo) + "] " + myLine;
    }

  private:
    StringList_t myValues;

    mutable bool myUsed;
    int          myLineNo;
    std::string  myLine;
};

#endif // _UIVALUE_H_
