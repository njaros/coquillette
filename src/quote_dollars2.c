#include "coquillette.h"

int	ft_quote_switch(int quote, char c)
{
	static int	dquote = 0;

	if (!quote && c == 34)
		dquote = ft_switch(dquote);
	if (!dquote && c == 39)
		return (ft_switch(quote));
	return (quote);
}