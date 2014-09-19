////////////////////////////////////////////////////////////////////////////
// FileVersionInfo.cpp -- Win32 executable file version info getter
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef MZC_NO_INLINING
    #undef MZC_INLINE
    #define MZC_INLINE  /*empty*/
    #include "FileVersionInfo_inl.hpp"
#endif

////////////////////////////////////////////////////////////////////////////

BOOL MFileVersionInfo::Open(LPCTSTR pszFileName)
{
    LPTSTR pszFile = const_cast<LPTSTR>(pszFileName);
    DWORD cb = ::GetFileVersionInfoSize(pszFile, NULL);
    if (cb == 0)
    {
        MzcFootmarkThis();
        return FALSE;
    }

    delete[] m_pbData;
    m_pbData = new BYTE[cb];
    assert(m_pbData);
    if (!::GetFileVersionInfo(pszFile, 0, cb, m_pbData))
    {
        MzcFootmarkThis();
        delete[] m_pbData;
        m_pbData = NULL;
        return FALSE;
    }

    return TRUE;
}

BOOL MFileVersionInfo::QueryTranslation()
{
    if (m_pbData == NULL)
        return FALSE;

    LPVOID lpBuffer;
    UINT cbBuffer;
    if (!::VerQueryValue(m_pbData, TEXT("\\VarFileInfo\\Translation"),
                         &lpBuffer, &cbBuffer))
    {
        MzcFootmarkThis();
        return FALSE;
    }

    LCID lcid = ::GetThreadLocale();
    WORD wLangID = LANGIDFROMLCID(lcid);

    MLangAndCodePage *pLangAndCodePage =
        reinterpret_cast<MLangAndCodePage *>(lpBuffer);

    int i, c = static_cast<int>(cbBuffer / sizeof(MLangAndCodePage));
    for (i = 0; i < c; i++)
    {
        if (pLangAndCodePage[i].wLanguage == wLangID)
            break;
    }

    if (i == c)
    {
        for (i = 0; i < c; i++)
        {
            if (PRIMARYLANGID(pLangAndCodePage[i].wLanguage) == LANG_ENGLISH)
                break;
        }
        if (i == c)
            i = -1;
    }

    m_pTranslations = pLangAndCodePage;
    m_iTranslation = i;
    m_cTranslation = c;
    return TRUE;
}

BOOL MFileVersionInfo::GetValue(LPCTSTR pszBlockName, MString& strValue) const
{
    LPVOID pData;
    UINT cb;
    TCHAR szPath[MAX_PATH];
    static const TCHAR szFormat[] = TEXT("\\StringFileInfo\\%04x%04x\\%s");

    if (m_pbData == NULL || m_pTranslations == NULL)
    {
        MzcFootmarkThis();
        return FALSE;
    }

    if (m_iTranslation != -1 && m_cTranslation > 0)
    {
        int i = m_iTranslation;
        ::wsprintf(szPath, szFormat,
            m_pTranslations[i].wLanguage, m_pTranslations[i].wCodePage,
            pszBlockName);
        if (::VerQueryValue(m_pbData, szPath, &pData, &cb))
        {
            strValue = reinterpret_cast<LPCTSTR>(pData);
            return TRUE;
        }
    }

    for (int i = 0; i < m_cTranslation; i++)
    {
        ::wsprintf(szPath, szFormat,
            m_pTranslations[i].wLanguage, m_pTranslations[i].wCodePage,
            pszBlockName);

        if (::VerQueryValue(m_pbData, szPath, &pData, &cb))
        {
            strValue = reinterpret_cast<LPCTSTR>(pData);
            return TRUE;
        }
    }

    MzcFootmarkThis();
    return FALSE;
}

BOOL MFileVersionInfo::GetFixedFileInfo(VS_FIXEDFILEINFO& info) const
{
    if (m_pbData == NULL)
    {
        MzcFootmarkThis();
        return FALSE;
    }

    LPVOID lpBuffer;
    UINT cbBuffer;
    if (!::VerQueryValue(m_pbData, TEXT("\\"), &lpBuffer, &cbBuffer))
    {
        MzcFootmarkThis();
        return FALSE;
    }

    assert(cbBuffer >= sizeof(VS_FIXEDFILEINFO));
    memcpy(&info, lpBuffer, sizeof(VS_FIXEDFILEINFO));
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////

#ifdef UNITTEST
    #include <cstdio>
    using namespace std;
    int main(void)
    {
        TCHAR szPath[MAX_PATH];
        SearchPath(NULL, TEXT("notepad"), TEXT(".exe"), MAX_PATH, szPath, NULL);
        printf("Notepad found: %hs\n", szPath);
        MFileVersionInfo info(szPath);
        if (info && info.QueryTranslation())
        {
            printf("success\n");
            MString str;
            if (info.GetComments(str))
                printf("Comments: %hs\n", str.c_str());
            if (info.GetCompanyName(str))
                printf("CompanyName: %hs\n", str.c_str());
            if (info.GetFileDescription(str))
                printf("FileDescription: %hs\n", str.c_str());
            if (info.GetFileVersion(str))
                printf("FileVersion: %hs\n", str.c_str());
            if (info.GetInternalName(str))
                printf("InternalName: %hs\n", str.c_str());
            if (info.GetLegalCopyright(str))
                printf("LegalCopyright: %hs\n", str.c_str());
            if (info.GetLegalTrademarks(str))
                printf("LegalTrademarks: %hs\n", str.c_str());
            if (info.GetOriginalFilename(str))
                printf("OriginalFilename: %hs\n", str.c_str());
            if (info.GetPrivateBuild(str))
                printf("PrivateBuild: %hs\n", str.c_str());
            if (info.GetProductName(str))
                printf("ProductName: %hs\n", str.c_str());
            if (info.GetProductVersion(str))
                printf("ProductVersion: %hs\n", str.c_str());
            if (info.GetSpecialBuild(str))
                printf("SpecialBuild: %hs\n", str.c_str());
        }
        else
        {
            printf("failure\n");
        }
        return 0;
    }
#endif

////////////////////////////////////////////////////////////////////////////
