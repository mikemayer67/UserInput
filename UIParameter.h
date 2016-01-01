#ifndef _UIPARAMETER_H_
#define _UIPARAMETER_H_

#include "UIQualifier.h"
#include "UIValue.h"

#include <map>

class UIParameter
{
  private:
    typedef std::map<UIQualifier,UIValue> Map_t;
    typedef Map_t::const_iterator         Iter_t;

  public:
    UIParameter(std::string name) : myName(name), myUsed(false) {}

    void add(const UIQualifier &,const UIValue &);

    const UIValue &lookup(bool validate) const;
    const UIValue &lookup(int id,bool validate) const;
    const UIValue &lookup(int id,Color_t color,bool validate) const;
    const UIValue &lookup(int id,Color_t color,int flavor,bool validate) const;
    const UIValue &lookup(int id,Color_t color,int flavor,double quality,bool validate) const;

    std::string name(void)   const { return myName; }
    bool        isUsed(void) const { return myUsed; }

    void findUnusedQualifiers(std::map<int,std::string> &) const;

  private:
    const UIValue &lookup(const UIQualifier &criteria) const;

    void validateKeys(UIQualifier::Qualifiers_t) const;

  private:
    std::string  myName;
    Map_t        myValues;
    mutable bool myUsed;
};

#endif // _UIPARAMETER_H_
