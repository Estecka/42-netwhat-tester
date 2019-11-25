/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nethwat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:02:17 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 11:22:17 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

struct s_ipv4
{
	unsigned char d;
	unsigned char c;
	unsigned char b;
	unsigned char a;
};

union u_ipv4
{
	unsigned int raw;
	struct s_ipv4 sections;
};

static void printmask(unsigned int mask)
{
	for (int i=3; i>=0; i--)
	for (int j=7; j>=0; j--)
	{
		short index = j + (i*8);
		short bit = (mask & 1<<index) ? 1 : 0;
		printf("%d", bit);
		if (j == 0)
			printf(" ");
	}
}

static void printip(struct s_ipv4 ip)
{
	printf("%u.%u.%u.%u", ip.a, ip.b, ip.c, ip.d);
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
