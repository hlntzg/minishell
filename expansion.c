/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:21:32 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/17 16:21:34 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
function: expand env variables
1. check for quote status
2. check that the environmental variable is valid
3. expand variable
*/ 

/*
function: check quote status
1. make sure that it's not inside single quotes
2. may be inside double quotes.
may be able to do this part separately but might have to do it in the expand funct
*/


/* 
function: check valid env variable
1. check for $
2. check for no space
3. check for letter or number
4. check for ? or _
*/
