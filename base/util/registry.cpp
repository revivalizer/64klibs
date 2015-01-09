#include "pch.h"

char* ZRegistry::GetKey(const char* const keyName, const char* const valueName)
{
	// Open key
	HKEY hkey;
	LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyName, 0, KEY_QUERY_VALUE, &hkey);

	// Check could open key
	if (result==ERROR_SUCCESS)
	{
		// Get key size
		DWORD dwType = REG_SZ, dwSize = 0;
		LONG result = RegQueryValueExA(hkey, valueName, NULL, &dwType, NULL, &dwSize);

		// Check result
		if (result!=ERROR_SUCCESS)
		{
			zcriticalerror("Error: ZRegistry::GetKey queried key; but couldn't find '%s'; error no %d\n", valueName, result);
			return NULL;
		}

		// Read key
		char* buf = new char[dwSize];
		RegQueryValueExA(hkey, valueName, NULL, &dwType, (PBYTE)buf, &dwSize);

		// Close key and return
		RegCloseKey(hkey);

		return buf;
	}
	else
	{
		// Couldn't open key
		zcriticalerror("Error: ZRegistry::GetKey couldn't open registry key; HKEY_LOCAL_MACHINE\\%s; error no %d\n", keyName, result);
		return NULL;
	}
}

bool ZRegistry::CheckKey(const char* const keyName, const char* const valueName)
{
	// Open key
	HKEY hkey;
	LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyName, 0, KEY_QUERY_VALUE, &hkey);

	// Check could open key
	if (result==ERROR_SUCCESS)
	{
		// Get key size
		DWORD dwType = REG_SZ, dwSize = 0;
		LONG result = RegQueryValueExA(hkey, valueName, NULL, &dwType, NULL, &dwSize);

		// Check result
		if (result==ERROR_SUCCESS)
		{
			return true;
		}

		// Close key and return
		RegCloseKey(hkey);
	}
	
	// Didn't open key
	return false;
}

void ZRegistry::SetKey(const char* const keyName, const char* const valueName, const char* const buf)
{
	// Open key
	HKEY hkey;
	LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyName, 0, KEY_SET_VALUE, &hkey);

	// Check could open key
	if (result==ERROR_SUCCESS)
	{
		result = RegSetValueExA(hkey, valueName, NULL, REG_SZ, reinterpret_cast<const BYTE* const>(buf), strlen(buf)+1);

		if (result!=ERROR_SUCCESS)
		{
			zcriticalerror("Error: ZRegistry::SetKey couldn't write registry value; HKEY_LOCAL_MACHINE\\%s; error no %d\n", keyName, result);
		}

		// Close key 
		RegCloseKey(hkey);
	}
	else
	{
		// Couldn't open key
		zcriticalerror("Error: ZRegistry::SetKey couldn't open registry key; HKEY_LOCAL_MACHINE\\%s; error no %d\n", keyName, result);
	}
}
