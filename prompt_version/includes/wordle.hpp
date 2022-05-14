/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 08:56:42 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/14 15:53:21 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include <fstream>
#include <algorithm>
#include <string>

#define GREEN "\33[1;32m"
#define ORANGE "\33[1;33m"
#define RED "\33[1;31m"
#define NOCOLOUR "\33[m"
#define PRINT_SEEK 1
#define DEBUG 1

#define WRONG_SPOT 1
#define PERFECT_SPOT 2

class Word
{
	public:
		std::string	name;
		int letters[5];
		Word();
		Word(std::string name);
};
