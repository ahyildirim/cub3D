#include "../../includes/cub3d.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	i = -1;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s) - start;
	substring = (char *)malloc(sizeof(char) * len + 1);
	if (!substring)
		return (NULL);
	while (++i < len)
		substring[i] = s[start + i];
	substring[i] = '\0';
	return (substring);
}
