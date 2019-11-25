/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nethwat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:02:17 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 17:47:23 by abaur            ###   ########.fr       */
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

static union u_ipv4 networkmask = { 0 };
static union u_ipv4 primaryip = { 0 };

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

void printclass(union u_ipv4 ip)
{
	union u_ipv4 class;

	class.sections = (struct s_ipv4){0,0,0,127};
	if (ip.raw < class.raw)
			return (void)printf("Class A\n");

	class.sections = (struct s_ipv4){0,0,0,128};
	if (ip.raw < class.raw)
			return (void)printf("Localhost IP\n");

	class.sections = (struct s_ipv4){0,0,0,192};
	if (ip.raw < class.raw)
			return (void)printf("Class B\n");

	class.sections = (struct s_ipv4){0,0,0,224};
	if (ip.raw < class.raw)
			return (void)printf("Class C\n");

	class.sections = (struct s_ipv4){0,0,0,240};
	if (ip.raw < class.raw)
			return (void)printf("Class D (multicast)\n");

	class.sections = (struct s_ipv4){0,0,0,255};
	if (ip.raw < class.raw)
			return (void)printf("Class E (RnD)\n");

	printf("Broadcast class\n");
}

static inline void printipFull(union u_ipv4 ip) {
	printmask(ip.raw);
	printf("\t");
	printip(ip.sections);
	printf("\n");
}

void SetNetworkMask(struct s_ipv4 netmask)
{
	networkmask.sections = netmask;

	printf("\nNetwork Mask : \n");
	printipFull(networkmask);
	printf("There are %d possible hosts on this network. \n", (~networkmask.raw) - 1);
}

void SetIp(struct s_ipv4 ip)
{
	primaryip.sections = ip;

	netip.raw   = primaryip.raw & networkmask.raw;
	broadip.raw = netip.raw | ~networkmask.raw;

	netlobound.raw = netip.raw + 1;
	nethibound.raw = broadip.raw - 1;

	printf("\n IP : \n");
	printipFull(primaryip);
	printclass(primaryip);

	printf("\nNetwork IP :\n");
	printipFull(netip);

	printf("\nBroadcast IP : \n");
	printipFull(broadip);

	printf("\nHost Range: \n");
	printipFull(netlobound);
	printipFull(nethibound);
}
