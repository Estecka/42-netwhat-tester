/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:07:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 17:47:10 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_netwhat.c"

void ft_netwhat(unsigned int ip, short netmask);

int main(int count, char** args)
{
	union u_ipv4 ip;
	union u_ipv4 netmask;

	if (count < 2) {
		printf("Not enough parameters");
		return 0;
	}

	if (!getIp(args[1], &netmask.sections) && !getNetmask(atoi(args[1]), &netmask.sections)){
		printf("Invalid network mask");
		return 0;
	}
	SetNetworkMask(netmask.sections);

	if (count < 3)
		return 0;
	if (!getIp(args[2], &ip.sections)){
		printf("Invalid primary ip");
		return 0;
	}

	SetIp(ip.sections);
}
