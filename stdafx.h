///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <cstring>

///////////////////////////////////////////////////////////////////////////////

#define EXTENDS_MOBJECT /*empty*/
#define MzcFootmark()
#define MzcFootmarkThis()

///////////////////////////////////////////////////////////////////////////////

#include <string>

#ifdef UNICODE
    #define MString std::wstring
#else
    #define MString std::string
#endif

///////////////////////////////////////////////////////////////////////////////

#include "FileVersionInfo.h"

///////////////////////////////////////////////////////////////////////////////