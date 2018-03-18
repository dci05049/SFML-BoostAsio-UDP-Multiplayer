#include "session.h"

namespace pt = boost::property_tree;
session::session(boost::shared_ptr<boost::asio::ip::udp::socket> socket,
	boost::asio::ip::udp::endpoint endpoint, room& room) :
	socket_(socket), room_(room), remote_endpoint_(endpoint), player_(get_id())
{

}

void session::start() {
	room_.join(shared_from_this());
}

boost::asio::ip::udp::socket& session::socket()
{
	return *socket_;
}

void session::deliver(std::string message) {

	bool write_in_progress = !message_queue.empty();
	message_queue.push_back(message);
	if (!write_in_progress) {
		socket_->async_send_to(boost::asio::buffer(message_queue.front()), remote_endpoint_,
			boost::bind(&session::handle_send, this, message_queue.front(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
			
}

void session::handle_send(std::string message,
	const boost::system::error_code& error,
	std::size_t bytes_transferre) 
{
	if (!error) {
		if (!message_queue.empty()) {
			message_queue.pop_front();
			if (!message_queue.empty()) {
				socket_->async_send_to(boost::asio::buffer(message_queue.front()), remote_endpoint_,
					boost::bind(&session::handle_send, this, message_queue.front(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			}
		}
	}
}

std::string session::get_id()
{
	return boost::lexical_cast<std::string>(remote_endpoint_.port());
}

player& session::get_playerdata() {
	return player_;
}

