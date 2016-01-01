#include "util.h"

#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <sstream>

using namespace std;

bool util::isInteger(const string &s)
{
  return ! s.empty() && s.find_first_not_of("0123456789")==string::npos;
}

bool util::isNumber(const string &s)
{
  bool rval=true;

  try { str2num(s); } catch(...) { rval = false; }

  return rval;
}

int util::str2int(const string &s)
{
  const char *str = s.c_str();
  char *end;

  errno=0;
  long rval = strtol(str,&end,0);
  if(errno)
  {
    stringstream err;
    err << "failed to convert '" << s << "' to integer: " << strerror(errno);
    throw runtime_error(err.str());
  }
  if(rval>INT_MAX || rval<INT_MIN)
  {
    stringstream err;
    err << "cannot convert '" << s << "' to an integer: exceeds limits";
    throw runtime_error(err.str());
  }
  while(*end)
  {
    if( ! isspace(*end) )
    {
      stringstream err;
      err << "failed to convert '" << s << "' to integer";
      throw runtime_error(err.str());
    }
    ++end;
  }
  
  return int(rval);
}

double util::str2num(const string &s)
{
  const char *str = s.c_str();
  char *end;

  errno=0;
  double rval = strtod(str,&end);
  if(errno)
  {
    stringstream err;
    err << "failed to convert '" << s << "' to number: " << strerror(errno);
    throw runtime_error(err.str());
  }
  while(*end)
  {
    if( ! isspace(*end) )
    {
      stringstream err;
      err << "failed to convert '" << s << "' to number: extra stuff following numerical value";
      throw runtime_error(err.str());
    }
    ++end;
  }
  
  return rval;
}

string util::int2str(int n)
{
  stringstream rval;
  rval << n;
  return rval.str();
}

string util::num2str(double n)
{
  stringstream rval;
  rval << n;
  return rval.str();
}

StringList_t util::tokenize(string s)
{
  StringList_t rval;

  string::iterator a=s.begin();
  while(a!=s.end())
  {
    if( *a==':' )
    {
      rval.push_back(":");
      ++a;
    }
    else if( isspace(*a) )
    {
      ++a;
    }
    else
    {
      string::iterator b(a+1);
      while(true)
      {
        if( b==s.end() || *b==':' || isspace(*b) )
        {
          rval.push_back(string(a,b));
          a=b;
          break;
        }
        ++b;
      }
      if(a!=s.end()) ++a;
    }
  }

  return rval;
}

string util::str2key(const string &s)
{
  string rval;

  for(int i=0; i<s.length(); ++i)
  {
    char c = s.at(i);
    if( ! ( c=='_' || isspace(c) ) )
    {
      rval.append(1,tolower(c));
    }
  }

  return rval;
}
