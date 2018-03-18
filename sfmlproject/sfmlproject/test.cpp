#include "test.h"
#include "EnemyPlayer.h"

#include <thread>
#include <iostream>


using namespace boost::property_tree;

namespace State
{

	Test::Test(Game* game, boost::asio::io_service& io_service)
		: State_Base(game), m_player(game, { 0,0 }), sock_(io_service)
	{

		try {
			boost::asio::ip::udp::resolver resolver(io_service);
			boost::asio::ip::udp::resolver::query query("127.0.0.1", "80");
			remote_endpoint_ = *resolver.resolve(query);

			ptree root;
			root.put("type", "connection");

			std::ostringstream buf;
			write_json(buf, root, false);
			std::string data = buf.str();

			sock_.open(boost::asio::ip::udp::v4());
			sock_.send_to(boost::asio::buffer(data), remote_endpoint_);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	void Test::input(const double dt)
	{
		m_player.input(dt);
	}

	//Always update lights, and then tiles and then entities
	void Test::update(const double dt)
	{
		m_player.update(dt);
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->update(dt);
		}
	}

	void Test::glDraw(const double dt)
	{

	}

	void Test::sfDraw(const double dt)
	{
		m_player.draw(m_game->getwindow().get());
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i]->draw(m_game->getwindow().get());
		}
	}

	void Test::start_receive()
	{
		//initialize the rmoete_endpoint_
		boost::asio::ip::udp::endpoint sender_endpoint;
		sock_.async_receive_from(
			boost::asio::buffer(recv_buffer_), sender_endpoint,
			boost::bind(&Test::handle_receive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void Test::handle_receive(const boost::system::error_code& error,
		std::size_t bytes_transferred)
	{

		if (!error || error == boost::asio::error::message_size)
		{
			std::string receive_json = std::string(recv_buffer_.begin(),
				recv_buffer_.begin() + bytes_transferred);
			ptree root;
			std::stringstream ss;
			ss << receive_json;

			try
			{
				read_json(ss, root);
			}
			catch (std::exception &e)
			{
				std::cout << "Error: " << e.what() << std::endl;
			}

			std::string playerid = root.get<std::string>("id");
			float x = root.get<int>("x");
			float y = root.get<int>("y");

			std::string type = root.get<std::string>("type");
			if (type == "moveplayer") {
				m_player.setPosition({ x,y });
			}
			else if (type == "moveother") {
				for (int i = 0; i < enemies.size(); i++) {
					if (enemies[i]->getId() == playerid) {
						enemies[i]->setPosition({ x, y });
					}
				}
			}
			else if (type == "newplayer") {
				sf::Vector2f initialpos{ x,y };
				std::cout << "player id" + playerid << std::endl;
				enemies.push_back(std::make_unique<EnemyPlayer>(m_game, playerid, initialpos));
			}

			start_receive();
		}
		else {
			std::cout << error.message() << std::endl;
		}
	}

	void Test::handle_send(boost::shared_ptr<std::string> message,
		const boost::system::error_code& error,
		std::size_t bytes_transferre)
	{
	}

	void Test::sendToServer(std::string msg) {
		sock_.send_to(boost::asio::buffer(msg), remote_endpoint_);
	}

} //Namespace State