/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:07:51 by abaur             #+#    #+#             */
/*   Updated: 2019/11/25 10:54:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void ft_netwhat(int ip, short netmask);

int main(int count, char** args)
{
	(void)count;
	short netmask = atoi(args[1]);
	int ip = atoi(args[2]);

	ft_netwhat(ip, netmask);
}
