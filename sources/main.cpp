/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 08:54:42 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/14 12:11:12 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include <fstream>
#include <algorithm>

void	ft_print_all_map(std::set<std::string>dico)
{
	for (auto it = dico.begin(); it != dico.end(); it++)
	{
		std::cout << (*it) << std::endl;
	}
}

void	ft_setify(std::ifstream &dico_file, std::set<std::string> &dico)
{
	int line_number;
	std::string line;

	line_number = 0;
	while (std::getline(dico_file, line))
	{
		dico.insert(line);
		line_number++;
	}
	//ft_print_all_map(dico);
}

int	ft_check_input(std::set<std::string> dico, std::string &player_input)
{
	std::cin >> player_input; std::cin.ignore();
	std::cout << player_input << std::endl;
	if (player_input.size() != 5)
	{
		std::cout << "You must give a 5 letter word" << std::endl;
		return (0);
	}
	if (dico.find(player_input) == dico.end())
	{
		std::cout << "Given word does not exist in our dictionary"
			<< ", please try again" << std::endl;
		return (0);
	}
	else
	{
		std::cout << "Word found all is clear" << std::endl;
		return (1);
	}
}

int	ft_ask_user(std::set<std::string> dico)
{
	std::string player_input;
	while (ft_check_input(dico, player_input) == 0)
	{}
	return (0);
}

int	main(void)
{
	std::ifstream dico_file;
	std::set<std::string> dico;

	dico_file.open("words.txt");
	if (!dico_file)
	{
		std::cout << "file could not be opened" << std::endl;
		return (0);
	}
	ft_setify(dico_file, dico);
	ft_ask_user(dico);
	return (0);
}
