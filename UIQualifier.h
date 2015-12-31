#ifndef _UIQUALIFIER_H_
#define _UIQUALIFIER_H_

#include "types.h"

class UIQualifier
{
  public:
    typedef enum { NO_QUALIFIERS, ID_ONLY, ID_AND_COLOR, ALL_BUT_QUALITY, ALL_QUALIFIERS } Qualifiers_t;

  public:
    UIQualifier(const StringList_t &values);

    UIQualifier(int id=-1,Color_t color=NoColor,int flavor=-1, double quality=-1.)
      : _id(id), _color(color), _flavor(flavor), _quality(quality)
    {}

    std::string parameter_name(void) const { return _name; }
    std::string qualifiers(void) const;

    bool operator<( const UIQualifier & ) const;

    bool satisfies( const UIQualifier &criteria ) const;
    bool validate( Qualifiers_t ) const;

  private:

    void setID(int id);
    void setColor(Color_t color);
    void setFlavor(int flavor);
    void setQuality(double quality);

    bool hasID(void)      const { return _id>0; }
    bool hasColor(void)   const { return _color!=NoColor; }
    bool hasFlavor(void)  const { return _flavor>=0; }
    bool hasQuality(void) const { return _quality>0.; }

    std::string _name;
    int         _id;
    Color_t     _color;
    int         _flavor;
    double      _quality;
};

#endif // _UIQUALIFIER_H_
