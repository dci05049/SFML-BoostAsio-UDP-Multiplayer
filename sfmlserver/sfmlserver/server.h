#pragma once
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/make_shared.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <exception>
#include "room.h"
#include "participant.h"
#include "session.h"

class server
{
public:
	server(std::string address, std::string port);
	
	void run();

private:
	void start_receive();

	void handle_receive(const boost::system::error_code& error,
		std::size_t /*bytes_transferred*/);

	void handle_send(boost::shared_ptr<std::string> /*message*/,
		const boost::system::error_code& /*error*/,
		std::size_t /*bytes_transferred*/);

	boost::asio::io_service io_service;
	boost::shared_ptr<boost::asio::ip::udp::socket> socket_;
	boost::asio::ip::udp::endpoint remote_endpoint_;
	boost::array<char, 128> recv_buffer_;

	//The next connection to be accepted
	boost::shared_ptr<session> new_session;

	room room_;
};