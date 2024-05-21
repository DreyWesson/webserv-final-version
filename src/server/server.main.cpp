/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 01:23:03 by alappas           #+#    #+#             */
/*   Updated: 2024/05/21 21:31:41 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/AllHeaders.hpp"

// int	g_signal;
// Servers *servers = NULL;

// void	handle_servers(int signo)
// {
// 	if (signo == SIGINT) {
// 		std::cout << "server address: " << servers << std::endl;
// 		delete servers;
// 		std::cout << "Server stopped" << std::endl;
// 		servers = NULL;
// 		exit(0);
// 	}
// }

// void	handle_signal(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = handle_servers;
// 	sa.sa_flags = SA_RESTART | SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// }

int serverMain(int argc, char **argv) {
	if (argc < 2)
		ft_errors(argv[0],1); 
	ConfigDB base;
	base.execParser(argv);    
	/**
	 * @brief print your choice of data.
	 * void ConfigDB::printChoice(bool allRootData, int rootDataIdx, bool allServersData, int serverDataIdx, bool allConfig)
	 * @param allRootData true prints all root data
	 * @param rootDataIdx prints root data at n index. where n >= 0
	 * @param allServersData true prints all server data
	 * @param rootDataIdx prints server data at n index. where n >= 0
	 * 
	 * @return NULL;
	 */
	base.printChoice(false, -1, false, -1, false);
	// handle_signal();
	Servers servers(base);
	// servers = new Servers(base);
	// delete servers;
	// servers = NULL;
	return 0;
}
