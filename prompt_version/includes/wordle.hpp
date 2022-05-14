/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 08:56:42 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/14 18:05:46 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

#define GREEN "\33[1;32m"
#define ORANGE "\33[1;33m"
#define RED "\33[1;31m"
#define NOCOLOUR "\33[m"
#define PRINT_SEEK 1
#define DEBUG 0

#define WRONG_SPOT 1
#define PERFECT_SPOT 2

class Word
{
	public:
		std::string	seek;
		std::string player_input;
		int letters[5]; //counting player_input letters
		int	reference[5]; //counting seek letters
		Word();
		Word(std::string name, std::string input);
};
