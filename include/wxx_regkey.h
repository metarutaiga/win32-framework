// Win32++   Version 8.7.1
// Release Date: TBA
//
//      David Nash
//      email: dnash@bigpond.net.au
//      url: https://sourceforge.net/projects/win32-framework
//
//
// Copyright (c) 2005-2020  David Nash
//
// Permission is hereby granted, free of charge, to
// any person obtaining a copy of this software and
// associated documentation files (the "Software"),
// to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice
// shall be included in all copies or substantial portions
// of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
// wxx_regkey.h
//  Declaration of the CRegKey class

#ifndef _WIN32XX_REGKEY_H_
#define _WIN32XX_REGKEY_H_

namespace Win32xx
{

    // The CRegKey class manages access to the system registry. It provides a
    // means of creating, querying, modifying and deleting registry entries.
    class CRegKey
    {
    public:
        CRegKey();
        CRegKey(HKEY key);
        CRegKey(const CRegKey&);
        ~CRegKey();
        operator HKEY() const { return m_key; }
        CRegKey& operator =(CRegKey& key);

        void Attach(HKEY key);
        LONG Close();
        LONG Create(HKEY keyParent, LPCTSTR pKeyName, LPTSTR pClass = REG_NONE,
                    DWORD options = REG_OPTION_NON_VOLATILE,
                    REGSAM samDesired = KEY_READ | KEY_WRITE,
                    LPSECURITY_ATTRIBUTES pSecAttr = NULL,
                    LPDWORD pDisposition = NULL);
        LONG DeleteSubKey(LPCTSTR pSubKey) const;
        LONG DeleteValue(LPCTSTR pSubKey) const;
        HKEY Detach();
        LONG EnumKey(DWORD index, LPTSTR pName, LPDWORD pNameLength, FILETIME* pLastWriteTime = NULL) const;
        LONG Flush() const;
        HKEY GetKey()  const { return m_key; }
        LONG NotifyChangeKeyValue(BOOL watchSubtree, DWORD notifyFilter, HANDLE event, BOOL isAsync = TRUE) const;
        LONG Open(HKEY hKeyParent, LPCTSTR pKeyName, REGSAM samDesired = KEY_READ | KEY_WRITE);
        LONG QueryBinaryValue(LPCTSTR pValueName, void* pValue, ULONG* pBytes) const;
        LONG QueryDWORDValue(LPCTSTR pValueName, DWORD& value) const;
        LONG QueryGUIDValue(LPCTSTR pValueName, GUID& value) const;
        LONG QueryMultiStringValue(LPCTSTR pValueName, LPTSTR pValue, ULONG* pChars) const;
        LONG QueryStringValue(LPCTSTR pValueName, LPTSTR pValue, ULONG* pChars) const;
        LONG QueryValue(LPCTSTR pValueName, DWORD* pType, void* pData, ULONG* pBytes) const;
        LONG RecurseDeleteKey(LPCTSTR pKeyName) const;
        LONG SetBinaryValue(LPCTSTR pValueName, const void* pValue, ULONG bytes) const;
        LONG SetDWORDValue(LPCTSTR pValueName, DWORD value) const;
        LONG SetGUIDValue(LPCTSTR pValueName, REFGUID value) const;
        LONG SetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd) const;
        LONG SetMultiStringValue(LPCTSTR pValueName, LPCTSTR pValue) const;
        LONG SetStringValue(LPCTSTR pValueName, LPCTSTR pValue, DWORD type = REG_SZ) const;
        LONG SetValue(LPCTSTR pValueName, DWORD type, const void* pValue, ULONG bytes) const;

#ifdef REG_QWORD
        LONG QueryQWORDValue(LPCTSTR pValueName, ULONGLONG& value) const;
        LONG SetQWORDValue(LPCTSTR pValueName, ULONGLONG value) const;
#endif

#if (WINVER >= 0x0600) && defined(RegSetKeyValue)
        LONG SetKeyValue(LPCTSTR pKeyName, LPCTSTR pValue, LPCTSTR pValueName = NULL) const;
#endif

    private:
        HKEY m_key;
    };

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace Win32xx
{
    inline CRegKey::CRegKey() : m_key(0)
    {
    }

    inline CRegKey::CRegKey(HKEY key) : m_key(0)
    {
        Attach(key);
    }

    inline CRegKey::CRegKey(const CRegKey& Key)
    {
        m_key = Key.m_key;
    }

    inline CRegKey::~CRegKey()
    {
        Close();
    }

    inline CRegKey& CRegKey::operator =(CRegKey& key)
    {
        Close();
        Attach(key.m_key);
        return *this;
    }

    // Attaches a KEY handle to this CRegKey object.
    inline void CRegKey::Attach(HKEY key)
    {
        assert(m_key == NULL);
        m_key = key;
    }

    // Closes the registry key.
    inline LONG CRegKey::Close()
    {
        LONG lRes = ERROR_SUCCESS;

        if (m_key != NULL)
        {
            lRes = ::RegCloseKey(m_key);
            m_key = NULL;
        }

        return lRes;
    }

    // Creates the specified registry key.
    inline LONG CRegKey::Create(HKEY keyParent, LPCTSTR pKeyName, LPTSTR pClass, DWORD options,
                   REGSAM samDesired, LPSECURITY_ATTRIBUTES pSecAttr, LPDWORD pDisposition)
    {
        HKEY hKey = 0;
        LONG result =  ::RegCreateKeyEx(keyParent, pKeyName, 0, pClass, options, samDesired, pSecAttr, &hKey, pDisposition);

        // RegCreateKeyEx opens existing keys, so close it now.
        ::RegCloseKey(hKey);

        return result;
    }

    // Removes the specified key from the registry.
    inline LONG CRegKey::DeleteSubKey(LPCTSTR pSubKey) const
    {
        assert(m_key);
        return ::RegDeleteKey(m_key, pSubKey);
    }

    // Removes a named value from the specified registry key.
    inline LONG CRegKey::DeleteValue(LPCTSTR pSubKey ) const
    {
        assert(m_key);
        return ::RegDeleteValue(m_key, pSubKey);
    }

    // Detaches the key handle from this CRegKey object.
    inline HKEY CRegKey::Detach()
    {
        assert(m_key);
        HKEY hKey = m_key;
        m_key = 0;
        return hKey;
    }

    // Enumerates subkeys of the specified open registry key.
    inline LONG CRegKey::EnumKey(DWORD index, LPTSTR pName, LPDWORD pNameLength, FILETIME* pLastWriteTime) const
    {
        assert(m_key);
        return ::RegEnumKeyEx(m_key, index, pName, pNameLength, 0, 0, 0, pLastWriteTime);
    }

    // Writes all the attributes of the specified open registry key into the registry.
    inline LONG CRegKey::Flush() const
    {
        assert(m_key);
        return ::RegFlushKey(m_key);
    }

    // Notifies the caller about changes to the attributes or contents of the registry key.
    inline LONG CRegKey::NotifyChangeKeyValue(BOOL watchSubtree, DWORD notifyFilter, HANDLE event, BOOL isAsync) const
    {
        assert(m_key);
        return ::RegNotifyChangeKeyValue(m_key, watchSubtree, notifyFilter, event, isAsync);
    }

    // Opens the specified registry key and assigns it to this CRegKey object.
    inline LONG CRegKey::Open(HKEY keyParent, LPCTSTR pKeyName, REGSAM samDesired)
    {
        assert(keyParent);
        Close();
        return ::RegOpenKeyEx(keyParent, pKeyName, 0, samDesired, &m_key);
    }

    // Retrieves the binary data for the specified value name.
    inline LONG CRegKey::QueryBinaryValue(LPCTSTR pValueName, void* pValue, ULONG* pBytes) const
    {
        assert(m_key);
        DWORD type = REG_BINARY;
        return ::RegQueryValueEx(m_key, pValueName, 0, &type, static_cast<LPBYTE>(pValue), pBytes);
    }

    // Retrieves the DWORD data for the specified value name.
    inline LONG CRegKey::QueryDWORDValue(LPCTSTR pValueName, DWORD& value) const
    {
        assert(m_key);
        DWORD type = REG_DWORD;
        DWORD bytes = sizeof(DWORD);
        return ::RegQueryValueEx(m_key, pValueName, 0, &type, reinterpret_cast<LPBYTE>(&value), &bytes);
    }

    // Retrieves the GUID data for the specified value name.
    inline LONG CRegKey::QueryGUIDValue(LPCTSTR pValueName, GUID& value) const
    {
        assert(m_key);

        TCHAR szGUID[64];
        value = GUID_NULL;
        ULONG count = 64;
        LONG result = QueryStringValue(pValueName, szGUID, &count);

        if (result == ERROR_SUCCESS)
        {
            HRESULT hr = ::CLSIDFromString(TtoOLE(szGUID), &value);

            if (FAILED(hr))
                result = ERROR_INVALID_DATA;
        }

        return result;
    }

    // Retrieves the multistring data for the specified value name.
    inline LONG CRegKey::QueryMultiStringValue(LPCTSTR pValueName, LPTSTR pValue, ULONG* pChars) const
    {
        assert(m_key);
        DWORD type = REG_MULTI_SZ;
        return ::RegQueryValueEx(m_key, pValueName, 0, &type, reinterpret_cast<LPBYTE>(pValue), pChars);
    }

    // Retrieves the string data for the specified value name.
    inline LONG CRegKey::QueryStringValue(LPCTSTR pValueName, LPTSTR pValue, ULONG* pChars) const
    {
        assert(m_key);
        DWORD type = REG_SZ;
        return ::RegQueryValueEx(m_key, pValueName, 0, &type, reinterpret_cast<LPBYTE>(pValue), pChars);
    }

    // Retrieves the data for the specified value name.
    inline LONG CRegKey::QueryValue(LPCTSTR pValueName, DWORD* pType, void* pData, ULONG* pBytes) const
    {
        assert(m_key);
        return ::RegQueryValueEx(m_key, pValueName, 0, pType, static_cast<LPBYTE>(pData), pBytes);
    }

    // Removes the specified key and any subkeys from the registry.
    inline LONG CRegKey::RecurseDeleteKey(LPCTSTR pKeyName) const
    {
        assert(m_key);
        assert(pKeyName);

        CRegKey Key;
        LONG result = Key.Open(m_key, pKeyName, KEY_READ | KEY_WRITE);
        if (result != ERROR_SUCCESS)
            return result;

        FILETIME time;
        DWORD size = MAX_PATH;
        TCHAR subKey[MAX_PATH];
        while (ERROR_SUCCESS == ::RegEnumKeyEx(Key, 0, subKey, &size, NULL, NULL, NULL, &time))
        {
            result = Key.RecurseDeleteKey(subKey);
            if (result != ERROR_SUCCESS)
                return result;
            size = MAX_PATH;
        }

        Key.Close();
        return DeleteSubKey(pKeyName);
    }

    // Sets the binary value of the registry key.
    inline LONG CRegKey::SetBinaryValue(LPCTSTR pValueName, const void* pValue, ULONG bytes) const
    {
        assert(m_key);
        return ::RegSetValueEx(m_key, pValueName, 0, REG_BINARY, static_cast<const BYTE*>(pValue), bytes);
    }

    // Sets the DWORD value of the registry key.
    inline LONG CRegKey::SetDWORDValue(LPCTSTR pValueName, DWORD value) const
    {
        assert(m_key);
        return ::RegSetValueEx(m_key, pValueName, 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(DWORD));
    }

    // Sets the GUID value of the registry key.
    inline LONG CRegKey::SetGUIDValue(LPCTSTR pValueName, REFGUID value) const
    {
        assert(m_key);
        OLECHAR szGUID[64];
        if (::StringFromGUID2(value, szGUID, 64) == 0)
            return ERROR_INSUFFICIENT_BUFFER;
        else
            return SetStringValue(pValueName, OLEtoT(szGUID));
    }

#if (WINVER >= 0x0600) && defined(RegSetKeyValue)

    // Stores data in a specified value field of a specified key.
    inline LONG CRegKey::SetKeyValue(LPCTSTR pKeyName, LPCTSTR pValue, LPCTSTR pValueName) const
    {
        assert(m_key);
        return ::RegSetKeyValue(m_key, pKeyName, pValueName, REG_SZ, pValue, lstrlen(pValue)*sizeof(TCHAR) );
    }

#endif

    // Sets the security of the registry key.
    inline LONG CRegKey::SetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd) const
    {
        assert(m_key);
        return ::RegSetKeySecurity(m_key, si, psd);
    }

    // Sets the multistring value of the registry key.
    inline LONG CRegKey::SetMultiStringValue(LPCTSTR pValueName, LPCTSTR pValue) const
    {
        assert(m_key);
        assert(pValue);

        // pszValue contains one or more null terminated strings.
        // Calculate the length of all strings including the terminating characters.
        ULONG bytes = 0;
        LPCTSTR pTemp = pValue;
        ULONG length = lstrlen(pTemp) +1; // +1 to include the terminating character

        while (length != 1)
        {
            pTemp += length;
            bytes += length *sizeof(TCHAR);
            length = lstrlen(pTemp) +1;
        }

        return ::RegSetValueEx(m_key, pValueName, 0, REG_MULTI_SZ, reinterpret_cast<const BYTE*>(pValue), bytes);
    }

    // Sets the string value of the registry key.
    inline LONG CRegKey::SetStringValue(LPCTSTR pValueName, LPCTSTR pValue, DWORD type) const
    {
        assert(m_key);
        return ::RegSetValueEx(m_key, pValueName, 0, type, reinterpret_cast<const BYTE*>(pValue), lstrlen(pValue)*sizeof(TCHAR));
    }

    // Sets the value of the registry key.
    inline LONG CRegKey::SetValue(LPCTSTR pValueName, DWORD type, const void* pValue, ULONG bytes) const
    {
        assert(m_key);
        return ::RegSetValueEx(m_key, pValueName, 0, type, reinterpret_cast<const BYTE*>(pValue), bytes);
    }

#ifdef REG_QWORD

    // Retrieves the QWORD data for a specified value name.
    inline LONG CRegKey::QueryQWORDValue(LPCTSTR pValueName, ULONGLONG& value) const
    {
        assert(m_key);
        DWORD type = REG_QWORD;
        DWORD bytes = sizeof(ULONGLONG);
        return ::RegQueryValueEx(m_key, pValueName, 0, &type, reinterpret_cast<LPBYTE>(&value), &bytes);
    }

    // Sets the QWORD value of the registry key.
    inline LONG CRegKey::SetQWORDValue(LPCTSTR pValueName, ULONGLONG value) const
    {
        assert(m_key);
        return ::RegSetValueEx(m_key, pValueName, 0, REG_QWORD, reinterpret_cast<const BYTE*>(&value), sizeof(ULONGLONG) );
    }

#endif

}


#endif // defined _WIN32XX_REGKEY_H_
