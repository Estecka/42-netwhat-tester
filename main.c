/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:07:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/27 16:24:03 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_netwhat.c"

int main(int count, char** args)
{
	union ipv4 ip;
	union ipv4 netmask;

	if (count < 2) {
		printf("Not enough parameters");
		return 0;
	}

	if (!getIp(args[1], &netmask) && !getNetmask(atoi(args[1]), &netmask)){
		printf("Invalid network mask");
		return 0;
	}
	SetNetworkMask(netmask);

	if (count < 3)
		return 0;
	if (!getIp(args[2], &ip)){
		printf("Invalid primary ip");
		return 0;
	}

	SetIp(ip);
}
