/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:07:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 13:37:36 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_nethwat.c"

void ft_netwhat(unsigned int ip, short netmask);

int main(int count, char** args)
{
	(void)count;
	union u_ipv4 ip = {0};

	ParseIp(args[1], &ip.sections);
	printmask(ip.raw);
	printf("\n");
	printip(ip.sections);
	printf("\n");

	//short netmask = atoi(args[1]);
	//int ip = atoi(args[2]);

	//ft_netwhat(ip, netmask);
}
