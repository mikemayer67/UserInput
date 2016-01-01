#ifndef _USERINPUT_H_
#define _USERINPUT_H_

#include "UIParameter.h"

#include <map>
#include <string>

class UserInput
{
    typedef std::map<std::string,UIParameter> Map_t;
    typedef Map_t::const_iterator             Iter_t;
    
  public:
    
    UserInput(const std::string &filename);
    
    const UIValue &lookup(std::string key,bool validate) const;
    const UIValue &lookup(std::string key,int id,bool validate) const;
    const UIValue &lookup(std::string key,int id,Color_t color,bool validate) const;
    const UIValue &lookup(std::string key,int id,Color_t color,int flavor,bool validate) const;
    const UIValue &lookup(std::string key,int id,Color_t color,int flavor,double quality,bool validate) const;
    
    void warn_unused(void) const;
    
  private:
    
    void add(int lineno, std::string line);
    
    const UIParameter &lookupParameter(std::string key) const;
    
  private:
    Map_t myParameters;
};

#endif // _USERINPUT_H_
