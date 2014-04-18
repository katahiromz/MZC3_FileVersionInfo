////////////////////////////////////////////////////////////////////////////
// FileVersionInfo.h -- Win32 executable file version info getter
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#ifndef __MZC3_FILEVERSIONINFO__
#define __MZC3_FILEVERSIONINFO__

#pragma comment(lib, "version.lib")

////////////////////////////////////////////////////////////////////////////

#include <pshpack1.h>
struct MLangAndCodePage
{
    WORD wLanguage;
    WORD wCodePage;
};
#include <poppack.h>

////////////////////////////////////////////////////////////////////////////

class MFileVersionInfo EXTENDS_MOBJECT
{
public:
    MFileVersionInfo();
    MFileVersionInfo(LPCTSTR pszFileName);
    virtual ~MFileVersionInfo();

    operator bool() const;
    bool operator!() const;

    BOOL Open(LPCTSTR pszFileName);
	BOOL QueryTranslation();
    VOID Close();

    BOOL GetValue(LPCTSTR pszBlockName, MString& strValue) const;
    BOOL GetFixedFileInfo(VS_FIXEDFILEINFO& info) const;

    BOOL GetComments(MString& strValue) const;
    BOOL GetCompanyName(MString& strValue) const;
    BOOL GetFileDescription(MString& strValue) const;
    BOOL GetFileVersion(MString& strValue) const;
    BOOL GetInternalName(MString& strValue) const;
    BOOL GetLegalCopyright(MString& strValue) const;
    BOOL GetLegalTrademarks(MString& strValue) const;
    BOOL GetOriginalFilename(MString& strValue) const;
    BOOL GetPrivateBuild(MString& strValue) const;
    BOOL GetProductName(MString& strValue) const;
    BOOL GetProductVersion(MString& strValue) const;
    BOOL GetSpecialBuild(MString& strValue) const;

    const BYTE *GetData() const;
    int GetTranslationIndex() const;
    int GetNumberOfTranslations() const;
    const MLangAndCodePage *GetTranslations() const;

protected:
    BYTE *               m_pbData;
    MLangAndCodePage *   m_pTranslations;
    int                  m_iTranslation;
    int                  m_cTranslation;

private:
    // NOTE: MFileVersionInfo is not copyable.
    MFileVersionInfo(const MFileVersionInfo& info);
    MFileVersionInfo& operator=(const MFileVersionInfo& info);
};

////////////////////////////////////////////////////////////////////////////

#ifndef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE inline
    #include "FileVersionInfo_inl.h"
#endif

#endif  // ndef __MZC3_FILEVERSIONINFO__
