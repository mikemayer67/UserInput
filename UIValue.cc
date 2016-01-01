#include "UIValue.h"
#include "util.h"

#include <math.h>

#include <sstream>

using namespace std;

IntSet_t UIValue::getIntSet(void) const
{
  IntSet_t rval;
  try
  {
    for(StringList_t::const_iterator x=myValues.begin(); x!=myValues.end(); ++x)
    {
      rval.insert( util::str2int(*x) );
    }
  }
  catch(const exception &e)
  {
    stringstream err;
    err << e.what() << endl << "  [" << myLineNo << "] " << myLine;
    throw runtime_error(err.str());
  }
  return rval;
}

StringSet_t UIValue::getStringSet(void) const
{
  StringSet_t rval;
  for(StringList_t::const_iterator x=myValues.begin(); x!=myValues.end(); ++x)
  {
    rval.insert( *x );
  }
  return rval;
}

NumSet_t UIValue::getNumSet(void) const
{
  NumSet_t rval;

  if(myValues.size()==3) 
  {
    try
    {
      double min = util::str2num(myValues.at(0));
      double max = util::str2num(myValues.at(1));

      if(min>max) { double tmp=min; min=max; max=tmp; }

      int num;
      double del(0.);

      if( util::isInteger(myValues.at(2)) )
      {
        num = util::str2int(myValues.at(2));
        if(num<1) throw runtime_error("count must be positive");
        if( num>1 ) del = (max-min)/(num-1);
      }
      else
      {
        del = util::str2num(myValues.at(2));
        if(del<=0.) throw runtime_error("step must be positive");
        double n = 1+(max-min)/del;
        if( fabs( fmod(n,1.) - 0.5 ) > 0.49 )
        {
          num = int(n+0.5);
          del = (max-min)/(num-1);
        }
      }

      for(int i=0; i<num; ++i) rval.insert(min + i*del);
    }
    catch(const exception &e)
    {
      stringstream err;
      err << "Invalid number sequence: should be min max (step|count)" << endl
        << "  " << e.what() << endl
        << "  [Line " << myLineNo << "] " << myLine;
      throw runtime_error(err.str());
    }
  }
  else
  {
    try
    {
      for(StringList_t::const_iterator x=myValues.begin(); x!=myValues.end(); ++x)
      {
        rval.insert( util::str2num(*x) );
      }
    }
    catch(const exception &e)
    {
      stringstream err;
      err << "Invalid number in sequence: " << e.what() << endl
        << "  [Line " << myLineNo << "] " << myLine;
      throw runtime_error(err.str());
    }
  }

  return rval;
}
