ZINLINE uint32_t zstrlen(const char* const str)
{
	uint32_t i = 0;

	while (str[i])
		i++;

	return i;
}

ZINLINE char* zstrdup(const char* const str)
{
	uint32_t len = zstrlen(str);
	char* data = new char[len+1];
	zmemcpy(data, str, len+1);

	return data;
}

ZINLINE char* zstrcpy(char* dest, const char* src)
{
	char* d = dest;

	while (*src)
	{
		*d++ = *src++;
	}

	*d++ = '\0';

	return dest;
}

ZINLINE char* zstrcat(char *dest, const char *src)
{
	char *rdest = dest; 

	while (*dest)
		dest++;

	while ((*dest++ = *src++) != '\0')
		;

	return rdest;
}

ZINLINE int32_t zstrcmp(const char *s1, const char *s2)
{
	// This from http://en.wikibooks.org/wiki/C_Programming/Strings#The_strcmp_function
	unsigned char uc1, uc2;
	/* Move s1 and s2 to the first differing characters 
	in each string, or the ends of the strings if they
	are identical.  */
	while (*s1 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	/* Compare the characters as unsigned char and
	return the difference.  */
	uc1 = (*(unsigned char *) s1);
	uc2 = (*(unsigned char *) s2);
	return ((uc1 < uc2) ? -1 : (uc1 > uc2));
}

ZINLINE bool zstrequal(const char *str1, const char *str2)
{
	return zstrcmp(str1, str2)==0;
}