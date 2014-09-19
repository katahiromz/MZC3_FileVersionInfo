////////////////////////////////////////////////////////////////////////////
// FileVersionInfo_inl.hpp -- Win32 executable file version info getter
// This file is part of MZC3.  See file "ReadMe.txt" and "License.txt".
////////////////////////////////////////////////////////////////////////////

MZC_INLINE MFileVersionInfo::MFileVersionInfo() :
    m_pbData(NULL), m_pTranslations(NULL), m_iTranslation(-1),
    m_cTranslation(0)
{
}

MZC_INLINE MFileVersionInfo::MFileVersionInfo(LPCTSTR pszFileName) :
    m_pbData(NULL), m_pTranslations(NULL), m_iTranslation(-1),
    m_cTranslation(0)
{
    Open(pszFileName);
}

MZC_INLINE /*virtual*/ MFileVersionInfo::~MFileVersionInfo()
{
    if (m_pbData)
        Close();
}

MZC_INLINE MFileVersionInfo::operator bool() const
{
	return m_pbData != NULL;
}

MZC_INLINE bool MFileVersionInfo::operator!() const
{
	return m_pbData == NULL;
}

MZC_INLINE BOOL MFileVersionInfo::GetComments(MString& strValue) const
{
    return GetValue(TEXT("Comments"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetCompanyName(MString& strValue) const
{
    return GetValue(TEXT("CompanyName"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetFileDescription(MString& strValue) const
{
    return GetValue(TEXT("FileDescription"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetFileVersion(MString& strValue) const
{
    return GetValue(TEXT("FileVersion"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetInternalName(MString& strValue) const
{
    return GetValue(TEXT("InternalName"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetLegalCopyright(MString& strValue) const
{
    return GetValue(TEXT("LegalCopyright"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetLegalTrademarks(MString& strValue) const
{
    return GetValue(TEXT("LegalTrademarks"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetOriginalFilename(MString& strValue) const
{
    return GetValue(TEXT("OriginalFilename"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetPrivateBuild(MString& strValue) const
{
    return GetValue(TEXT("PrivateBuild"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetProductName(MString& strValue) const
{
    return GetValue(TEXT("ProductName"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetProductVersion(MString& strValue) const
{
    return GetValue(TEXT("ProductVersion"), strValue);
}

MZC_INLINE BOOL MFileVersionInfo::GetSpecialBuild(MString& strValue) const
{
    return GetValue(TEXT("SpecialBuild"), strValue);
}

MZC_INLINE const BYTE *MFileVersionInfo::GetData() const
{
    return m_pbData;
}

MZC_INLINE int MFileVersionInfo::GetTranslationIndex() const
{
    return m_iTranslation;
}

MZC_INLINE int MFileVersionInfo::GetNumberOfTranslations() const
{
    return m_cTranslation;
}

MZC_INLINE const MLangAndCodePage *MFileVersionInfo::GetTranslations() const
{
    return m_pTranslations;
}

MZC_INLINE void MFileVersionInfo::Close()
{
    if (m_pbData)
    {
        delete[] m_pbData;
        m_pbData = NULL;
    }
}
