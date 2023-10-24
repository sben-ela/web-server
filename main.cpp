/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:25:06 by aybiouss          #+#    #+#             */
/*   Updated: 2023/10/23 18:16:27 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/Servers.hpp"
//testing !!

void sig_handler(int sig) {
    (void)sig;
    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc == 1 || argc == 2) {
		try 
		{
            signal(SIGINT, sig_handler);
            Servers configFile;
            std::string		config;
            config = (argc == 1 ? "default.conf" : argv[1]);
            configFile.ConfigFileParse(config);
        }
        catch (std::string& e)
        {
            std::cout << e << std::endl;
            return (1);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else 
	{
		std::cerr << "Error: wrong arguments" << std::endl;
		return (1);
	}
}