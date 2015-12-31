#include "UIParameter.h"

#include <sstream>

using namespace std;

void UIParameter::add(const UIQualifier &q, const UIValue &v)
{
  myValues.erase(q);
  myValues.insert( make_pair(q,v) );
}

const UIValue &UIParameter::lookup(bool validate) const
{
  if(validate) validateKeys(UIQualifier::NO_QUALIFIERS);
  return lookup(UIQualifier());
}

const UIValue &UIParameter::lookup(int id,bool validate) const
{
  if(validate) validateKeys(UIQualifier::ID_ONLY);
  return lookup(UIQualifier(id));
}

const UIValue &UIParameter::lookup(int id,Color_t color,bool validate) const
{
  if(validate) validateKeys(UIQualifier::ID_AND_COLOR);
  return lookup(UIQualifier(id,color));
}

const UIValue &UIParameter::lookup(int id,Color_t color,int flavor,bool validate) const
{
  if(validate) validateKeys(UIQualifier::ALL_BUT_QUALITY);
  return lookup(UIQualifier(id,color,flavor));
}

const UIValue &UIParameter::lookup(int id,Color_t color,int flavor,double quality,bool validate) const
{
  // accepts all qualifiers, no need to validate
  return lookup(UIQualifier(id,color,flavor,quality));
}

const UIValue &UIParameter::lookup(const UIQualifier &criteria) const
{
  static UIValue failValue;

  myUsed=true;
  for( Iter_t x=myValues.begin(); x!=myValues.end(); ++x )
  {
    if( x->first.satisfies(criteria) )
    {
      x->second.setUsed();
      return x->second;
    }
  }

  stringstream err;
  err << "No values specified for " << myName << " (" << criteria.qualifiers() << ")";
  throw runtime_error(err.str());

  return failValue;
}

void UIParameter::validateKeys(UIQualifier::Qualifiers_t q) const
{
  for(Iter_t x=myValues.begin(); x!=myValues.end(); ++x)
  {
    if( ! x->first.validate(q) ) 
    {
      stringstream err;
      err << "Parameter " << myName << " ";
      switch(q)
      {
        case UIQualifier::NO_QUALIFIERS:   err << "does not allow any questions";        break;
        case UIQualifier::ID_ONLY:         err << "only allows ID qualifier";            break;  
        case UIQualifier::ID_AND_COLOR:    err << "only allows ID and color qualifiers"; break;  
        case UIQualifier::ALL_BUT_QUALITY: err << "does not allow quality qualifiers";   break;
        default: break; // only here to suppress warnings
      }
      err << endl << "  " << x->second.input_line();
      throw runtime_error(err.str());
    }
  }
}
