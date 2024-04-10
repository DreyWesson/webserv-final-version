/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandle.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 01:28:32 by alappas           #+#    #+#             */
/*   Updated: 2024/04/10 02:55:26 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLE_HPP
# define CGIHANDLE_HPP

#include "./AllHeaders.hpp"

class RequestConfig;

class CgiHandle{
	private:
		std::map<std::string, std::string>	_env;
		RequestConfig	*_config;
		std::string	_cgi_path;
		pid_t		_cgi_pid;
		int			_exit_status;
		char		**_argv;
		char		**_envp;
		char 		*_path;
		int			pipe_in[2];
		int			pipe_out[2];
		
	public:
		CgiHandle();
		CgiHandle(RequestConfig *config);
		~CgiHandle();
		CgiHandle(const CgiHandle &other);
		CgiHandle &operator=(const CgiHandle &other);
		void    initEnv();
		void	createEnvArray();
		void	execCgi();
		int		setPipe();
		void	closePipe();
		std::string getIp();
		void setPath();
		void setArgv();
};

#endif