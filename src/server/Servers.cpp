/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alappas <alappas@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:28:07 by alappas           #+#    #+#             */
/*   Updated: 2024/05/25 22:37:34 by alappas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Servers.hpp"
#include "../../inc/HttpRequest.hpp"

Servers::Servers(ConfigDB &configDB) : _server_fds(), _domain_to_server(), _ip_to_server(), 
	_keyValues(), server_index(), server_fd_to_index(), client_to_server(), _client_amount(0),
	configDB_(configDB){
	_keyValues = configDB_.getKeyValue();
	createServers();
	initEvents();
}

Servers::~Servers() {
	std::cout << "Destructor called for servers!" << std::endl;
	for (std::vector<int>::iterator it = _server_fds.begin(); it != _server_fds.end(); ++it)
	{
		if (*it != -1)
			close(*it);
	}
    _server_fds.clear();
    if (_epoll_fds != -1)
        close(_epoll_fds);
}

Servers::Servers(const Servers &rhs)
    : _epoll_fds(rhs._epoll_fds),_server_fds(rhs._server_fds), 
      _domain_to_server(rhs._domain_to_server), _ip_to_server(rhs._ip_to_server),
      _keyValues(rhs._keyValues), server_index(rhs.server_index),
      server_fd_to_index(rhs.server_fd_to_index), _client_amount(rhs._client_amount),
	  configDB_(rhs.configDB_){}

Servers &Servers::operator=(const Servers &rhs) {
    if (this != &rhs) {
        _server_fds = rhs._server_fds;
        _epoll_fds = rhs._epoll_fds;
        _domain_to_server = rhs._domain_to_server;
        _ip_to_server = rhs._ip_to_server;
        _keyValues = rhs._keyValues;
        server_index = rhs.server_index;
        server_fd_to_index = rhs.server_fd_to_index;
		_client_amount = rhs._client_amount;
        configDB_ = rhs.configDB_;
    }
    return *this;
}

int Servers::createSocket(){
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		std::cerr << "Socket creation failed" << std::endl;
		return (0);
	}
	_server_fds.push_back(server_fd);
	return (1);
}

int Servers::bindSocket(std::string s_port){
	if (_server_fds.back() == -1)
	{
		std::cerr << "Socket binding impossible!" << std::endl;
		return (0);
	}
	std::stringstream ss;
	ss << s_port;
	int port;
	std::string ip_string;
	const char *c_ip = NULL;
	if (s_port.find(":") == std::string::npos)
	{
		port = std::atoi(s_port.c_str());
		_ip_to_server[_server_fds.back()] = "127.0.0.1:" + s_port;
	}
	else
	{
		_ip_to_server[_server_fds.back()] = s_port;
		getline(ss, ip_string, ':');
		ss >> port;
		c_ip = ip_string.c_str();
	}
	int opt = 1;
	setsockopt(_server_fds.back(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	struct sockaddr_in address;
	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	if (c_ip != NULL)
		address.sin_addr.s_addr = inet_addr(c_ip);
	else
		address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	address.sin_port = htons(port);
	if (bind(_server_fds.back(), (struct sockaddr *)&address, sizeof(address)) == -1) {
		std::cerr << "Bind failed" << std::endl;
		return (0);
	}
	for (std::map<int, std::vector<std::string> >::iterator it = server_index.begin(); it != server_index.end(); it++){
		for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){
			if (*it2 == s_port)
				server_fd_to_index[_server_fds.back()] = it->first;
		}
	}
	return (1);
}

void	Servers::createEpoll(){
	int epoll_fd = epoll_create1(0);
	this->_epoll_fds = epoll_fd;
	if (epoll_fd < 0) {
		std::cerr << "Epoll creation failed" << std::endl;
		exit(1);
	}
}

int Servers::listenSocket(){
	if (listen(_server_fds.back(), SOMAXCONN) == -1) {
		std::cerr << "Listen failed" << std::endl;
		return (0);
	}
	return (1);
}

int Servers::combineFds(int socket_fd){
	struct epoll_event event;
	std::memset(&event, 0, sizeof(event));
	event.events = EPOLLIN;
	event.data.fd = socket_fd;
	if (epoll_ctl(this->_epoll_fds, EPOLL_CTL_ADD, socket_fd, &event) == -1) {
		std::cerr << "Epoll_ctl failed" << std::endl;
		return (0);
	}
	return (1);
}

void Servers::createServers(){
	
	std::cout << "Creating servers" << std::endl;
	std::vector<std::string> ports;
	createEpoll();
	ports = getPorts();
	for (std::vector<std::string>::iterator it2 = ports.begin(); it2 != ports.end(); it2++) {
		if (!checkSocket(*it2)){
			if (createSocket()){
				if (!bindSocket(*it2) || !listenSocket() || !setNonBlocking(_server_fds.back()) || !combineFds(_server_fds.back()))
					_server_fds.pop_back();
				else
				{
					assignDomain(*it2, _server_fds.back());
					std::cout << "Server created on port " << _ip_to_server[_server_fds.back()] << ", server:" << _server_fds.back() << std::endl;
				}
			}
		}
	}
}

Listen getTargetIpAndPort(std::string requestedUrl) {
	size_t pos = requestedUrl.find(":");
	Listen listen;

	if (requestedUrl.empty())
		return (std::cout << "ERROR: empty host and port" <<std::endl, listen);

	if ( pos == std::string::npos)	
		return (std::cout << "Warning: default host and port used 127.0.0.1:80" <<std::endl, listen);

	std::string x_ip = requestedUrl.substr(0, pos);
	std::string x_port = requestedUrl.substr(pos + 1);
	uint32_t port_x;
	std::istringstream iss(x_port); 
	iss >> port_x;
	return Listen (x_ip, port_x);
}

// void Servers::handleIncomingConnection(int server_fd){
// 	struct sockaddr_in address;
// 	std::string request;
//     socklen_t addrlen = sizeof(address);
//     int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
// 	bool finish = false;
//     if (new_socket == -1) {
//         std::cerr << "Accept failed." << std::endl;
//         return;
//     }
//     std::cout << "Connection established on IP: " << _ip_to_server[server_fd] << ", server:" << server_fd << "\n" << std::endl;
// 	HttpRequest parser;
// 	int reqStatus = -1;
// 	while (!finish){
// 		finish = getRequest(new_socket, request);
// 		reqStatus = parser.parseRequest(request);
// 		if (reqStatus != 200) {
// 			finish = true;
// 		}
// 		if (!handleResponse(reqStatus, server_fd, new_socket, parser))
// 			return;
// 	}
//     if (close(new_socket) == -1)
// 		std::cerr << "Close failed with error: " << strerror(errno) << std::endl;
// 	else 
// 		std::cout << "Connection closed on IP: " << _ip_to_server[server_fd] << ", server:" << server_fd << "\n" << std::endl;
// }

void Servers::handleIncomingConnection(int server_fd){
	struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket == -1) {
        std::cerr << "Accept failed." << std::endl;
        return;
    }
	if (combineFds(new_socket) == 0)
	{
		if (close(new_socket) == -1)
			std::cerr << "Close failed with error: " << strerror(errno) << std::endl;
		return ;
	}
	client_to_server[new_socket] = server_fd;
	_client_data[new_socket] = HttpRequest();
	
    std::cout << "Connection established on IP: " << _ip_to_server[server_fd] << ", server:" << server_fd << ", client: " << new_socket << "\n" << std::endl;
	_client_amount++;
}

void Servers::handleIncomingData(int client_fd){
	// HttpRequest parser(_client_data.find(client_fd)->second);
	int reqStatus = -1;
	std::string request;
	int server_fd = client_to_server[client_fd];
	bool finish = false;
	finish = getRequest(client_fd, request);
	reqStatus = _client_data.find(client_fd)->second.parseRequest(request);
	if (reqStatus != 200) {
		finish = true;
	}
	if (!handleResponse(reqStatus, server_fd, client_fd, _client_data.find(client_fd)->second))
		return;
	// handleIncomingCgi(client_fd);
	if (finish && _cgi_clients.find(client_fd) == _cgi_clients.end())
		deleteClient(client_fd);
}



void Servers::initEvents(){
	while (true){
		try{
			struct epoll_event events[_server_fds.size() + _client_amount];
			int n = epoll_wait(this->_epoll_fds, events, _server_fds.size() + _client_amount, -1);
			if (n == -1) {
				std::cerr << "Epoll_wait failed" << std::endl;
				return ;
			}
			for (int i = 0; i < n; i++) {
				bool server = false;
				for (std::vector<int>::iterator it2 = _server_fds.begin(); it2 != _server_fds.end(); ++it2) {
					if (events[i].data.fd == *it2) {
						std::cout << "\nIncoming connection on server: " << *it2 << std::endl;
						handleIncomingConnection(*it2);
						server = true;
						break ;
					}
				}
				if (!server && events[i].events & EPOLLIN) {
					// std::cout << "\nIncoming data on client: " << events[i].data.fd << std::endl;
					// std::cout << "Event FD: " << events[i].data.fd << std::endl;
					if (_cgi_clients_childfd.find(events[i].data.fd) != _cgi_clients_childfd.end())
						handleIncomingCgi(events[i].data.fd);
					else if (_client_data.find(events[i].data.fd) != _client_data.end())
						handleIncomingData(events[i].data.fd);
				}
			}
		} catch (std::exception &e){
			std::cerr << e.what() << std::endl;
		}
	}
}

std::vector<std::string> Servers::getPorts(){
	
	std::map<std::string, std::vector<std::string> > config = getKeyValue();
	std::stringstream ss;
	std::vector<std::string> ports_temp;
	std::vector<std::string> ports;

	for (int i = 0; i != std::numeric_limits<int>::max(); i++){
		ss.str("");
		ss << i;
		std::string server_name = "server[" + ss.str() + "]";
		std::string server;
		std::map<std::string, std::vector<std::string> >::iterator it_server_name = config.end();
		for (std::map<std::string, std::vector<std::string> >::iterator it = config.begin(); it != config.end(); it++)
		{
			if (it->first.find(server_name) != std::string::npos){
				std::size_t pos = it->first.find(server_name);
				it_server_name = it;
				std::string prefix = it->first.substr(0, pos + server_name.length());
				server = prefix + ".listen";
				break;
			}
		}
		std::map<std::string, std::vector<std::string> >::iterator it_server = config.find(server);
		if (it_server != config.end()){
			ports_temp = it_server->second;
			for (std::vector<std::string>::iterator it2 = ports_temp.begin(); it2 != ports_temp.end(); it2++){
				if (std::find(ports.begin(), ports.end(), *it2) == ports.end())
				{
					ports.push_back(*it2);
					server_index[i].push_back(*it2);
				}
			}
		}
		else if (it_server_name != config.end() && it_server == config.end()){
			if (std::find(ports.begin(), ports.end(), "80") == ports.end())
			{
				ports.push_back("80");
				server_index[i].push_back("80");
			}
		}
		else
			return (ports);
	}
	return (ports);
}

// Getting local domains and saving them to a map for each server
void Servers::assignLocalDomain(int server_fd){
	std::map<std::string, std::vector<std::string> > config = getKeyValue();
	for (std::map<std::string, std::vector<std::string> >::iterator it_domain = config.begin(); it_domain != config.end(); it_domain++){
		if (it_domain->first.find("server_name") != std::string::npos){
			std::string server_name = it_domain->first;
			std::size_t pos = server_name.find("]");
			server_name = server_name.substr(0, pos + 1);
			std::string domain = server_name + ".listen";
			std::map<std::string, std::vector<std::string> >::iterator it_domain_listen = config.find(domain);
				if (it_domain_listen == config.end()){
					for (std::vector<std::string>::iterator it = it_domain->second.begin(); it != it_domain->second.end(); it++){
					if (std::find(_domain_to_server[server_fd].begin(), _domain_to_server[server_fd].end(), *it) == _domain_to_server[server_fd].end())
						_domain_to_server[server_fd].push_back(*it);
				}
			}
		}
	}
}

// Getting domains and saving them to a map for each server
void Servers::assignDomain(std::string port, int server_fd){
	if (port == "80")
		assignLocalDomain(server_fd);
	std::map<std::string, std::vector<std::string> > config = getKeyValue();
	for (std::map<std::string, std::vector<std::string> >::iterator it = config.begin(); it != config.end(); it++)
	{
		for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			if (*it2 == port){
				std::string server_name = it->first;
				std::size_t pos = server_name.find("]");
				server_name = server_name.substr(0, pos + 1);
				std::string domain = server_name + ".server_name";
				std::map<std::string, std::vector<std::string> >::iterator it_domain = config.find(domain);
				if (it_domain != config.end()){
					for (std::vector<std::string>::iterator it3 = it_domain->second.begin(); it3 != it_domain->second.end(); it3++){
						if (std::find(_domain_to_server[server_fd].begin(), _domain_to_server[server_fd].end(), *it3) == _domain_to_server[server_fd].end())
							_domain_to_server[server_fd].push_back(*it3);
					}
				}
				else{
					if (std::find(_domain_to_server[server_fd].begin(), _domain_to_server[server_fd].end(), "localhost") == _domain_to_server[server_fd].end())
						_domain_to_server[server_fd].push_back("localhost");
				}
			}
		}
	}
}

// Getter for config file
std::map<std::string, std::vector<std::string> > Servers::getKeyValue() const {
	return (this->_keyValues);
}

// Check if port is valid
int Servers::checkSocketPort(std::string port){
	for (std::string::iterator it = port.begin(); it != port.end(); it++)
	{
		if (!std::isdigit(*it) || std::atoi(port.c_str()) < 0 || std::atoi(port.c_str()) > 65535)
		{
			std::cerr << "Invalid port" << std::endl;
			return 1;
		}
	}
	return (0);
}

// Check if ip is valid
int Servers::checkSocket(std::string ip){
	std::string ip_string;
	std::string port_string;
	if (ip.find(":") == std::string::npos)
		return checkSocketPort(ip);
	else{
		std::stringstream ss_ip;
		std::stringstream ss_port;
		ss_ip << ip;
		getline(ss_ip, ip_string, ':');
		ss_ip >> port_string;
		if (checkSocketPort(port_string) == 1)
			return 1;
	}
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, ip_string.c_str(), &(sa.sin_addr));
	if (result == 0) {
		std::cerr << "Invalid address" << std::endl;
		return 1;
	}
	else if (result == -1) {
		std::cerr << "Address conversion failed" << std::endl;
		return 1;
	}
	return 0;
}

bool Servers::getRequest(int client_fd, std::string &request){
	
	char buffer[4096];
	request.clear();
	// std::cout << "I read many times!" << std::endl;
	int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes > 0)
	{
		buffer[bytes] = '\0';
		request.append(buffer, bytes);
	}
	else if (bytes == -1)
	{
		std::cerr << "Recv failed" << std::endl;
		return true;
	}
	return false;
}

size_t Servers::handleResponse(int reqStatus, int server_fd, int new_socket, HttpRequest &parser) {
		std::string response;
		if (reqStatus != 200)
		{
			Listen host_port = getTargetIpAndPort(_ip_to_server[server_fd]);

			DB db = {configDB_.getServers(), configDB_.getRootConfig()};
			Client client(db, host_port, parser, server_fd_to_index[server_fd], reqStatus);
			client.setupResponse();
			// std::cout << "***isCGI: " << client.getCgi() << std::endl;
			if (client.getCgi())
			{
				// std::cout << "I am created here\n";
				// std::cout << "HTTP Request: " << &parser << std::endl;
				_cgi_clients[new_socket] = new CgiClient(client, this->_epoll_fds);
				_cgi_clients_childfd[_cgi_clients[new_socket]->getPipeOut()] =  new_socket;
				// std::cout << "CGI PIPE FD: " << _cgi_clients_childfd[new_socket] << std::endl;
				// std::cout << "Client FD: " << new_socket << std::endl;
				return (1);
			}
			response = client.getResponseString();
		}
		ssize_t bytes = write(new_socket, response.c_str(), response.size());
		if (bytes == -1) {
			std::cerr << "Write failed with error: " << strerror(errno) << std::endl;
			return 0;
		}
		return 1;
}

void Servers::deleteClient(int client_fd)
{
	if (epoll_ctl(this->_epoll_fds, EPOLL_CTL_DEL, client_fd, NULL) == -1) {
        std::cerr << "Failed to remove client file descriptor from epoll instance." << std::endl;
    }
    if (close(client_fd) == -1)
		std::cerr << "Close failed with error: " << strerror(errno) << std::endl;
	if (_client_amount > 0)
		_client_amount--;
	if (_cgi_clients.find(client_fd) != _cgi_clients.end())
	{
		delete _cgi_clients[client_fd];
		_cgi_clients.erase(client_fd);
	}
	std::cout << "Connection closed on IP: " << _ip_to_server[client_to_server[client_fd]] << ", server:" << client_to_server[client_fd] << "\n" << std::endl;
	_client_data.erase(client_fd);
	client_to_server.erase(client_fd);
}

void Servers::deleteChild(int child_fd)
{
	if (epoll_ctl(this->_epoll_fds, EPOLL_CTL_DEL, child_fd, NULL) == -1) {
		std::cerr << "Failed to remove client file descriptor from epoll instance." << std::endl;
	}
	_cgi_clients_childfd.erase(child_fd);
}

int Servers::setNonBlocking(int fd){
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1)
	{
		std::cerr << "Fcntl failed" << std::endl;
		return (0);
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		std::cerr << "Fcntl failed" << std::endl;
		return (0);
	}
	if (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
    {
        std::cerr << "Fcntl failed" << std::endl;
        return (0);
    }
	return (1);
}

void Servers::setConnectionTimeout(int client_fd){
	_client_time[client_fd] = time(NULL);
}

int Servers::handleIncomingCgi(int child_fd){
	std::string response;
	int	client_fd;
	// while (_cgi_clients[client_fd]->getStatusCode() != 200)
	
	for (std::map<int, int>::iterator it = _cgi_clients_childfd.begin(); it != _cgi_clients_childfd.end(); it++)
	{
		if (it->first == child_fd)
		{
			client_fd = it->second;
			break;
		}
	}
	// std::cout << "True Client FD for CGI: " << client_fd << std::endl;
	// std::cout << "Client FD for CGI: " << child_fd << std::endl;
	_cgi_clients[client_fd]->HandleCgi();
	// std::cout << "Status code: " << _cgi_clients[client_fd]->getStatusCode() << std::endl;
	if (_cgi_clients[client_fd]->getStatusCode() == 200 || _cgi_clients[client_fd]->getStatusCode() == 500)
	{
		_cgi_clients[client_fd]->getResponse().createResponse();
		response = _cgi_clients[client_fd]->getResponseString();
		// std::cout << "Response: " << response << std::endl;
		ssize_t bytes = write(client_fd, response.c_str(), response.size());
		if (bytes == -1) {
			std::cerr << "Write failed with error: " << strerror(errno) << std::endl;
			return 0;
		}
		deleteClient(client_fd);
		deleteChild(child_fd);
	}
	std::cout << "I stop here\n";
	return 1;
}