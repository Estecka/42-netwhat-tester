/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nethwat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:02:17 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 18:01:32 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

struct s_ipv4
{
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
};

union ipv4
{
	unsigned int raw;
	struct s_ipv4 bytes;
};

static union ipv4 networkmask = { 0 };
static union ipv4 primaryip = { 0 };

static union ipv4 netip;
static union ipv4 broadip;

static union ipv4 netlobound;
static union ipv4 nethibound;


/*
** Parses the given text `src`, and writes the corresponding ip into `dst`.
** Returns 0 if pasing failed.
*/
short getIp(char *src, union ipv4 *dst)
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
void printip(union ipv4 ip)
{
	printf("%u.%u.%u.%u", ip.bytes.b3, ip.bytes.b2, ip.bytes.b1, ip.bytes.b0);
}

/*
** Computes the network mask matching the given range.
** Returns 0 if the range is invalid.
*/
short getNetmask(int range, union ipv4 *dst)
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

void printclass(union ipv4 ip)
{
	union ipv4 class;

	class.bytes = (struct s_ipv4){0,0,0,127};
	if (ip.raw < class.raw)
			return (void)printf("Class A\n");

	class.bytes = (struct s_ipv4){0,0,0,128};
	if (ip.raw < class.raw)
			return (void)printf("Localhost IP\n");

	class.bytes = (struct s_ipv4){0,0,0,192};
	if (ip.raw < class.raw)
			return (void)printf("Class B\n");

	class.bytes = (struct s_ipv4){0,0,0,224};
	if (ip.raw < class.raw)
			return (void)printf("Class C\n");

	class.bytes = (struct s_ipv4){0,0,0,240};
	if (ip.raw < class.raw)
			return (void)printf("Class D (multicast)\n");

	class.bytes = (struct s_ipv4){0,0,0,255};
	if (ip.raw < class.raw)
			return (void)printf("Class E (RnD)\n");

	printf("Broadcast class\n");
}

static inline void printipFull(union ipv4 ip) {
	printmask(ip.raw);
	printf("\t");
	printip(ip);
	printf("\n");
}

void SetNetworkMask(union ipv4 netmask)
{
	networkmask = netmask;

	printf("\nNetwork Mask : \n");
	printipFull(networkmask);
	printf("There are %d possible hosts on this network. \n", (~networkmask.raw) - 1);
}

void SetIp(union ipv4 ip)
{
	primaryip = ip;

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
