#include "UserInput.h"

#include <iostream>
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
  }
  catch(const exception &e)
  {
    cout << endl
      << "Sorry:: " << e.what() << endl
      << endl;
  }

  return 0;
}
