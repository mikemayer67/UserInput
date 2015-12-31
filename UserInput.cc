#include "UserInput.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

UserInput::UserInput(const string &filename)
{
  ifstream src(filename);
  if(!src)
  {
    stringstream err;
    err << "Failed to open '" << filename << "' as input " << endl << "   " << strerror(errno);
    throw runtime_error(err.str());
  }

  int lineno(0);
  string line;
  for( getline(src,line); src.good(); getline(src,line) )
  {
    add(++lineno,line);
  }
}

void UserInput::add(int lineno,string line)
{
  line = line.substr(0, line.find('#'));
  
  StringList_t tokens = util::tokenize(line);

  if( tokens.empty() ) return;

  StringList_t keys;
  StringList_t values;

  StringList_t::iterator x = find(tokens.begin(), tokens.end(), string(":"));
  if( x==tokens.end() )
  {
    stringstream err;
    err << "Input line must contain both key(s) and value(s): missing a colon" << endl
      << "  [Line " << lineno << "] " << line;
    throw runtime_error(err.str());
  }

  keys.insert(keys.end(),tokens.begin(),x);

  if(keys.empty())
  {
    stringstream err;
    err << "Input line is missing key(s)" << endl
      << "  [Line " << lineno << "] " << line;
    throw runtime_error(err.str());
  }

  ++x;

  if( find(x, tokens.end(), string(":")) != tokens.end() )
  {
    stringstream err;
    err << "Input line may only contain one colon" << endl
      << "  [Line " << lineno << "] " << line;
    throw runtime_error(err.str());
  }

  values.insert(values.end(),x,tokens.end());

  if(values.empty())
  {
    stringstream err;
    err << "Input line is missing value(s)" << endl
      << "  [Line " << lineno << "] " << line;
    throw runtime_error(err.str());
  }

  UIQualifier qual(keys);
  UIValue     value(values,lineno,line);

  string parameter_key = util::str2key(qual.parameter_name());

  pair<Map_t::iterator,bool> rc = 
    myParameters.insert( make_pair( parameter_key, UIParameter(parameter_key) ) );

  rc.first->second.add(qual,value);
}

const UIValue &UserInput::lookup(string key,bool validate) const
{
  return lookupParameter(key).lookup(validate);
}

const UIValue &UserInput::lookup(string key,int id,bool validate) const
{
  return lookupParameter(key).lookup(id,validate);
}

const UIValue &UserInput::lookup(string key,int id,Color_t color,bool validate) const
{
  return lookupParameter(key).lookup(id,color,validate);
}

const UIValue &UserInput::lookup(string key,int id,Color_t color,int flavor,bool validate) const
{
  return lookupParameter(key).lookup(id,color,flavor,validate);
}

const UIValue &UserInput::lookup(string key,int id,Color_t color,int flavor,double quality,bool validate) const
{
  return UserInput::lookupParameter(key).lookup(id,color,flavor,quality,validate);
}

const UIParameter &UserInput::lookupParameter(string key) const
{
  Iter_t rval = myParameters.find(key);
  if(rval==myParameters.end())
  {
    stringstream err;
    err << "Failed to find any entries for " << key;
    throw runtime_error(err.str());
  }
  return rval->second;
}
