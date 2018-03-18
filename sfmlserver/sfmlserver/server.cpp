#include "server.h"

using boost::asio::ip::udp;
namespace pt = boost::property_tree;

server::server(std::string address, std::string port) : io_service(),
socket_(boost::make_shared<boost::asio::ip::udp::socket>
(io_service, udp::endpoint(udp::v4(), 80)))
{
	start_receive();
}

void server::run() {

	io_service.run();
}

void server::start_receive()
{
	socket_->async_receive_from(
		boost::asio::buffer(recv_buffer_), remote_endpoint_,
		boost::bind(&server::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void server::handle_receive(const boost::system::error_code& error,
	std::size_t bytes_transferred)
{
	if (!error || error == boost::asio::error::message_size)
	{
		
		std::string receive_json = std::string(recv_buffer_.begin(), 
			recv_buffer_.begin() + bytes_transferred);
		//std::cout << receive_json << std::endl;
		pt::ptree root;
		std::stringstream ss;
		ss << receive_json;

		try
		{
			pt::read_json(ss, root);
		}
		catch (std::exception &e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		std::string type = root.get<std::string>("type");
		if (type == "connection") {

			new_session.reset(new session(socket_, remote_endpoint_, room_));
			new_session->start();
		}
		else if (type == "movement") {
			float x = root.get<float>("x", 0);
			float y = root.get<float>("y", 0);
			room_.updatePosition(boost::lexical_cast<std::string>(remote_endpoint_.port()) , { x, y });
		}

		start_receive();
	}
}

void server::handle_send(boost::shared_ptr<std::string> message,
	const boost::system::error_code& error,
	std::size_t bytes_transferre)
{
	if (!error) {
		std::cout << *message << " was sent" << std::endl;
	}
	else {
		std::cout << error.message() << std::endl;
	}
}
