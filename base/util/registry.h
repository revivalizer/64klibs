#pragma once

class ZRegistry
{
public:
	static char* GetKey(const char* const keyName, const char* const valueName);
	static void SetKey(const char* const keyName, const char* const valueName, const char* const buf);
	static bool CheckKey(const char* const keyName, const char* const valueName);
};

#ifndef SWIG	
	class ZScopedRegistryKey
	{
	public:
		ZScopedRegistryKey(const char* const keyName, const char* const valueName)
		: str(ZRegistry::GetKey(keyName, valueName))
		{
		}

		~ZScopedRegistryKey()
		{
			if (str)
				delete[] str;
		}

		const char* const str;

	private:
		ZScopedRegistryKey& operator=(const ZScopedRegistryKey&); // disallow assigment
	};
#endif
