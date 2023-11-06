/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:23:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/06 22:25:42 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}