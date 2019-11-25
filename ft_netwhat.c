/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nethwat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:02:17 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 15:39:13 by abaur            ###   ########.fr       */
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


static union u_ipv4 networkmask;
static union u_ipv4 primaryip;

static union u_ipv4 netip;
static union u_ipv4 broadip;

static union u_ipv4 netlobound;
static union u_ipv4 nethibound;


/*
** Parses the given text `src`, and writes the corresponding ip into `dst`.
** Returns 0 if pasing failed.
*/
short getIp(char *src, struct s_ipv4 *dst)
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
void printmask(unsigned int mask)
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
void printip(struct s_ipv4 ip)
{
	printf("%u.%u.%u.%u", ip.d, ip.c, ip.b, ip.a);
}

/*
** Computes the network mask matching the given range.
** Returns 0 if the range is invalid.
*/
short getNetmask(int range, struct s_ipv4 *dst)
{
	if (range < 0 || 32 < range)
		return 0;

	int* mask = (int*)dst;
	*mask = 0;
	for (int i=0; i<32; i++)
		if (range >= 32-i)
			*mask |= 1<<i;
	return 1;
}

static inline void printipFull(union u_ipv4 ip) {
	printmask(ip.raw);
	printf("\t");
	printip(ip.sections);
	printf("\n");
}

void SetHome(struct s_ipv4 ip, struct s_ipv4 netmask)
{
	networkmask.sections = netmask;
	primaryip.sections = ip;

	netip.raw   = primaryip.raw & networkmask.raw;
	broadip.raw = netip.raw | ~networkmask.raw;

	netlobound.raw = netip.raw + 1;
	nethibound.raw = broadip.raw - 1;

	printf("IP : \n");
	printipFull(primaryip);

	printf("\nNetwork Mask : \n");
	printipFull(networkmask);

	printf("\nNetwork IP :\n");
	printipFull(netip);

	printf("\nBroadcast IP : \n");
	printipFull(broadip);

	printf("\nHost Range: \n");
	printf("There are %d possible hosts\n", nethibound.raw - netip.raw);
	printipFull(netlobound);
	printipFull(nethibound);

}
