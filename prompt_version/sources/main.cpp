/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 08:54:42 by aweaver           #+#    #+#             */
/*   Updated: 2022/05/14 19:26:02 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <set>
#include <fstream>
#include <algorithm>
#include <string>
#include "wordle.hpp"

Word::Word(std::string seek, std::string input)
{
	this->seek = seek;
	this->player_input = input;
	for (int i = 0; i < 5; i++)
	{
		this->letters[i] = 0;
		this->reference[i] = 0;
	}
}

Word::Word()
{
}

//this function is a debug function only used to print the whole dico
void	ft_print_all_set(std::set<std::string>dico)
{
	for (auto it = dico.begin(); it != dico.end(); it++)
	{
		std::cout << (*it) << std::endl;
	}
}

//transform the dico_file in an std::set
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
	if (line_number == 0)
	{
		std::cout << "The file you provided as a dictionnary contains no words"
			<< std::endl;
		exit (0);
	}
	//ft_print_all_set(dico);
}

int		ft_verify_ascii(std::string &player_input)
{
	int ret;

	ret = 1;
	std::for_each(player_input.begin(), player_input.end(), [&ret](char & c)
	{
		if (c < 'A' || c > 'z')
		{
			ret = 0;
		}
	});
	return (ret);
}

//transforms a string to lowercase
void	ft_string_tolower(std::string &player_input)
{
	std::for_each(player_input.begin(), player_input.end(), [](char & c)
	{
		c = std::tolower(c);
	});
}

//transforms a string to uppercase
void	ft_string_toupper(std::string &player_input)
{
	std::for_each(player_input.begin(), player_input.end(), [](char & c)
	{
		c = std::toupper(c);
	});
}

//checks the input of the player loops until the input is correct
int	ft_check_input(std::set<std::string> dico, std::string &player_input)
{
	player_input.clear();
	std::getline(std::cin, player_input);
	if (std::cin.eof() == 1)
	{
		std::cerr << "Error: Stdin closed cannot continue" << std::endl;
		exit (0);
	}
	//std::cin >> player_input; std::cin.ignore();
	ft_string_tolower(player_input);
	//std::cout << player_input << std::endl;
	//std::cout << "str_len:" << player_input.size() << std::endl;
	if (player_input.size() != 5 || ft_verify_ascii(player_input) == 0)
	{
		std::cout << RED << "You must give a 5 letter word containing no accented letters" << NOCOLOUR << std::endl;
		return (0);
	}
	else if (dico.find(player_input) == dico.end())
	{
		std::cout << RED << "Given word does not exist in our dictionary"
			<< ", please try again" << NOCOLOUR << std::endl;
		return (0);
	}
	else if (DEBUG)
	{
		std::cout << GREEN << "Word found all is clear" << NOCOLOUR << std::endl;
	}
	return (1);
}

void	ft_check_wrong_place(Word &checker)
{
	int i; //iterates in player_input
	int	j; //iterates in seek

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			if (i != j
					&& *(checker.player_input.begin() + i) == *(checker.seek.begin() + j)
					&& checker.reference[j] == 0 && checker.letters[i] == 0)
			{
				checker.reference[j] = 1;
				checker.letters[i] = 1;
			}
			j++;
		}
		i++;
	}
}

void	ft_check_correct_place(Word &checker)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (DEBUG)
		{
			std::cout << "player_letter =" << *(checker.player_input.begin() + i) 
					<< "seek_letter = " << *(checker.seek.begin() + i) << std::endl;
		}
		if (*(checker.player_input.begin() + i) ==  *(checker.seek.begin() + i))
		{
			if (checker.reference[i] == 0)
			{
				checker.letters[i] = 2;
				checker.reference[i] = 1;
			}
			if (DEBUG)
			{
				std::cout << "checker.reference[i] =" << checker.reference[i] << std::endl;
				std::cout << "I found a correct place" << std::endl;
			}
		}
		i++;
	}
}

void	ft_print_menu(std::vector<Word> words, int cols)
{
	system("clear");
	size_t attempts;

	attempts = words.size();
	for (int i = 0; i < ((cols - 20) / 16); i++)
		std::cout << "\t";
	std::cout << ORANGE << "Welcome dear friend!" << std::endl;
	for (int i = 0; i < ((cols - 57) / 16); i++)
		std::cout << "\t";
	std::cout << "You have " << 6 - attempts << " attempts remaining to beat the game, Good luck!"
			<< std::endl << std::endl << NOCOLOUR;
}

void	ft_print_first_menu(int cols)
{
	system("clear");
	size_t attempts;

	attempts = 0;
	for (int i = 0; i < ((cols - 20) / 16); i++)
		std::cout << "\t";
	std::cout << ORANGE << "Welcome dear friend!" << std::endl;
	for (int i = 0; i < ((cols - 57) / 16); i++)
		std::cout << "\t";
	std::cout << "You have " << 6 - attempts << " attempts remaining to beat the game, Good luck!"
			<< std::endl << std::endl << NOCOLOUR; //57
}

void	ft_print_victory_screen(int cols)
{
	for (int i = 0; i < ((cols - 29) / 16); i++)
		std::cout << "\t";
	std::cout << GREEN << "Well done chap(ess)! You won!" << NOCOLOUR << std::endl;
}

int	ft_print_coloured_attempt(std::vector<Word> &words, int cols)
{
	int ret;
	
	ret = 0;
	ft_print_menu(words, cols);
	for (size_t j = 0; j < words.size(); j++)
	{
		for (int i = 0; i < ((cols - 5) / 16); i++)
			std::cout << "\t";
		for (size_t i = 0; i < 5; i++)
		{
			if (words[j].letters[i] == 2)
			{
				std::cout << GREEN << *(words[j].player_input.begin() + i) << NOCOLOUR;
				ret++;
			}
			else if (words[j].letters[i] == 1)
				std::cout << ORANGE << *(words[j].player_input.begin() + i) << NOCOLOUR;
			else
				std::cout << *(words[j].player_input.begin() + i) << NOCOLOUR;
		}
		std::cout << std::endl;
		if (ret == 5)
		{
			ft_print_victory_screen(cols);
			return (1);
		}
	}
	return (0);
}

int	ft_ask_user(std::vector<Word> &words, std::set<std::string> dico, std::string seek, int cols)
{
	std::string player_input;

	while (1)
	{
		if (ft_check_input(dico, player_input) == 1)
			break;
	}
	Word checker(seek, player_input);
	ft_check_correct_place(checker);
	ft_check_wrong_place(checker);
	words.push_back(checker);
	return (ft_print_coloured_attempt(words, cols));
}

void	 ft_chose_random_word(std::set<std::string> dico, std::string &seek)
{
	int dico_size;
	int random;
	std::set<std::string>::iterator it;

	it = dico.begin();
	dico_size = dico.size();
	srand(time(NULL));
	random = rand() % dico_size;
	std::advance(it, random);
	seek = *it;
	if (PRINT_SEEK)
	std::cout << "The word to find is: " << seek << std::endl;
}

int	main(void)
{
	int	i;
	std::ifstream dico_file;
	std::set<std::string> dico;
	std::string seek;
	std::vector<Word> words;
	struct winsize window;
	int cols;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	cols = window.ws_col;


	i = 0;
	dico_file.open("words.txt");
	if (!dico_file)
	{
		std::cout << "file could not be opened" << std::endl;
		return (0);
	}
	ft_setify(dico_file, dico);
	dico_file.close();
	ft_chose_random_word(dico, seek);
	ft_print_first_menu(cols);
	while (i < 6)
	{
		if (ft_ask_user(words, dico, seek, cols) == 1)
			break ;
	}
	return (0);
}
