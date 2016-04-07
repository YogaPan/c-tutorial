#include <stdio.h>
#include <string.h>

int main(void)
{
	const char *url;
	char protocol[100];
	char site[100];
	char path[100];

	/* strcpy(path, "/"); */
	url = "https://www.shoes.com/";
	sscanf(url, "%[^:]:%*2[/]%[^/]%[a-zA-Z0-9._/-]", protocol, site, path);
	printf("protocol=%s site=%s path=%s\n", protocol, site, path);

	url = "http://www.google.com/123/456";
	sscanf(url, "%[^:]:%*2[/]%[^/]%[a-zA-Z0-9._/-]", protocol, site, path);
	printf("protocol=%s site=%s path=%s\n", protocol, site, path);


	return 0;
}
