#include "UserInput.h"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main(int argc,char **argv)
{
  try
  {
    if( argc!=2 ) 
    {
      stringstream err;
      err << "Incorrect number of arguments" << endl
        << "  Usage: " << argv[0] << " datafile";
      throw runtime_error(err.str());
    }

    UserInput ui(argv[1]);

    IntSet_t indices = ui.lookup("Indices",true).getIntSet();
    for(IntSet_t::iterator id=indices.begin(); id!=indices.end(); ++id)
    {
      StringSet_t colors = ui.lookup("colors",*id,true).getStringSet();
      for(StringSet_t::iterator col=colors.begin(); col!=colors.end(); ++col)
      {
        Color_t color(NoColor);
        if(      util::str2key(*col)=="red"  ) color=Red;
        else if( util::str2key(*col)=="black") color=Black;
        else throw runtime_error(string("Unknown color: ")+*col);

        IntSet_t flavors = ui.lookup("Flavors",*id,color,true).getIntSet();
        for(IntSet_t::iterator flavor=flavors.begin(); flavor!=flavors.end(); ++flavor)
        {
          NumSet_t qualities = ui.lookup("Qualities",*id,color,*flavor,true).getNumSet();
          for(NumSet_t::iterator quality=qualities.begin(); quality!=qualities.end(); ++quality)
          {
            NumSet_t temps = ui.lookup("tempertures",*id,color,*flavor,*quality,true).getNumSet();

            cout 
              << "  " << *id 
              << " "  << setw(5) << *col << "(" << color << ")"
              << " "  << *flavor
              << " "  << setw(3) << left << *quality 
              << ": ";

            for(NumSet_t::iterator t=temps.begin(); t!=temps.end(); ++t)
            {
              cout << " " << *t;
            }
            cout << endl;
          }
        }
      }
    }
    ui.warn_unused();
  }
  catch(const exception &e)
  {
    cout << endl
      << "Sorry:: " << e.what() << endl
      << endl;
  }

  return 0;
}
