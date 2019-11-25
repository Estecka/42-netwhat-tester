/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nethwat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:02:17 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 13:49:22 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

struct s_ipv4
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
};

union u_ipv4
{
	unsigned int raw;
	struct s_ipv4 sections;
};


/*
** Parses the given text `src`, and writes the corresponding ip into `dst`.
** Returns 0 if pasing failed.
*/
static short ParseIp(char *src, struct s_ipv4 *dst)
{
	unsigned char *ip = (unsigned char*)dst;

	for (int i=3; i>=0; i--)
	{
		unsigned short value = 0;
		for ((void)src; isdigit(*src); src++)
			value = (value * 10) + (*src - '0');
		if (value > 255)
			return (0);
		if (*src != (i==0 ? '\0' : '.'))
			return (0);
		ip[i] = value;
		src++;
	}
	return (1);
}

/*
** Prints the given int32 as binary.
*/
static void printmask(unsigned int mask)
{
	for (int i=3; i>=0; i--)
	for (int j=7; j>=0; j--)
	{
		short index = j + (i*8);
		short bit = (mask & 1<<index) ? 1 : 0;
		printf("%d", bit);
		if (j == 0 && i != 0)
			printf(" ");
	}
}

/*
** Prints the given ip in a human-readable format.
*/
static void printip(struct s_ipv4 ip)
{
	printf("%u.%u.%u.%u", ip.d, ip.c, ip.b, ip.a);
}


void ft_netwhat(unsigned int rawip, short maskvalue)
{
	union u_ipv4 ip;
	union u_ipv4 netmask;

	printmask(rawip);
	printf("\n");

	ip.raw = rawip;
	printf("ip: \t");
	printip(ip.sections);
	printf(" / %hu\n", maskvalue);

	netmask.raw = 0;
	for (int i=0; i<32; i++)
		if (maskvalue >= 32-i)
			netmask.raw |= 1<<i;

	printmask(netmask.raw);
	printf("\nnetmask:\t");
	printip(netmask.sections);
	printf("\n");
}
