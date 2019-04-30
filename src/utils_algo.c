#include "ft_ssl.h"

uint32_t	left_rotate(uint32_t x, uint32_t n)
{
	return ((x << n) | (x >> (32 - n)));
}
