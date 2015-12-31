#include "UIQualifier.h"

#include "util.h"

#include <sstream>

using namespace std;

UIQualifier::UIQualifier(const StringList_t &values) :
  _id(-1), _color(NoColor), _flavor(-1), _quality(-1.0)
{
  for(StringList_t::const_iterator x=values.begin(); x!=values.end(); ++x)
  {
    if(util::isInteger(*x))
    {
      int n = util::str2int(*x);
      if     ( n>=1000 && n<1010 ) setID(n-1000);
      else if( n>=0    && n<10   ) setFlavor(n);
      else
      {
        stringstream err;
        err << "Unrecognized integer qualifier (" << *x << ")";
        throw runtime_error(err.str());
      }
    }
    else if(util::isNumber(*x))
    {
      double n = util::str2num(*x);
      if( n<0. || n>7.5 ) setQuality(n);
      else
      {
        stringstream err;
        err << "Unrecognized number qualifier (" << *x << ")";
        throw runtime_error(err.str());
      }
    }
    else
    {
      string qual=util::str2key(*x);
      if     (qual=="red")   setColor(Red);
      else if(qual=="black") setColor(Black);
      else if(qual.substr(0,2)=="fl" && util::isInteger(qual.substr(2)))
      {
        setFlavor(util::str2int(qual.substr(2)));
      }
      else if(qual.substr(0,1)=="q" && util::isNumber(qual.substr(1)))
      {
        setQuality(util::str2num(qual.substr(1)));
      }
      else if(_name.empty())
      {
        _name = *x;
      }
      else
      {
        throw runtime_error("Cannot specify parameter name more than one");
      }
    }
  }

  if(_name.empty())
  {
    throw runtime_error("Failed to specify a parameter name");
  }
}

void UIQualifier::setID(int id)
{
  if(_id>=0) throw runtime_error("Cannot specify id more than once");
  _id = id;
}

void UIQualifier::setFlavor(int flavor)
{
  if(_flavor>=0) throw runtime_error("Cannot specify flavor more than once");
  _flavor = flavor;
}

void UIQualifier::setQuality(double quality)
{
  if(_quality>=0.) throw runtime_error("Cannot specify quality more than once");
  _quality = quality;
}

void UIQualifier::setColor(Color_t color)
{
  if(_color!=NoColor) throw runtime_error("Cannot specify color more than once");
  _color = color;
}

bool UIQualifier::operator<(const UIQualifier &x) const
{
  bool rval(false);

  if( _id != x._id )
  {
    rval = ( x.hasID() && !hasID() ? false :
             hasID() && !x.hasID() ? true  : _id < x._id );
  }
  else if( _color != x._color )
  {
    rval = ( x.hasColor() && !hasColor() ? false :
             hasColor() && !x.hasColor() ? true  : _color < x._color );
  }
  else if( _flavor != x._flavor )
  {
    rval = ( x.hasFlavor() && !hasFlavor() ? false :
             hasFlavor() && !x.hasFlavor() ? true  : _flavor < x._flavor );
  }
  else if( _quality != x._quality )
  {
    rval = ( x.hasQuality() && !hasQuality() ? false :
             hasQuality() && !x.hasQuality() ? true  : _quality < x._quality );
  }

  return rval;
}

bool UIQualifier::satisfies( const UIQualifier &criteria ) const
{
  if( hasID()      &&      _id!=criteria._id     ) return false; 
  if( hasColor()   &&   _color!=criteria._color  ) return false;
  if( hasFlavor()  &&  _flavor!=criteria._flavor ) return false;
  if( hasQuality() && _quality!=criteria._quality) return false;
  return true;
}

bool UIQualifier::validate( Qualifiers_t q ) const
{
  bool rval(true);
  switch(q)
  {
    case NO_QUALIFIERS:    if( hasID()      ) rval = false;  // no break, fallthrough is intentional
    case ID_ONLY:          if( hasColor()   ) rval = false;  // "
    case ID_AND_COLOR:     if( hasFlavor()  ) rval = false;  // "
    case ALL_BUT_QUALITY:  if( hasQuality() ) rval = false;  break;
    default: break; // here to supress compiler warnings
  }
  return rval;
}

string UIQualifier::qualifiers(void) const
{
  stringstream rval;

  string sep="";

  if(_id>0) { rval << sep << 1000+_id; sep=","; }

  switch(_color)
  {
    case Red:   rval << sep << "Red";   sep=","; break;
    case Black: rval << sep << "Black"; sep=","; break;
    default: break; // here to supress compiler warnings
  }

  if(_flavor>=0)   { rval<<sep<<_flavor;  sep=","; }
  if(_quality>=0.) { rval<<sep<<_quality; sep=","; }

  return rval.str();
}
