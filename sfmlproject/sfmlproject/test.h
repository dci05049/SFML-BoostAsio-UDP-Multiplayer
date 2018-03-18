#ifndef TEST_H
#define TEST_H

#include "game.h"
#include "player.h"
#include "EnemyPlayer.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace State
{

	class Test : public State_Base
	{
	public:
		Test(Game* game, boost::asio::io_service& io_service);

		~Test() {}

		void input(const double dt) override;

		void update(const double dt) override;

		void glDraw(const double dt) override;

		void sfDraw(const double dt) override;

		void start_receive() override;

	private:

		void sendToServer(std::string msg);

		void handle_receive(const boost::system::error_code& error,
			std::size_t /*bytes_transferred*/);

		void handle_send(boost::shared_ptr<std::string> /*message*/,
			const boost::system::error_code& /*error*/,
			std::size_t /*bytes_transferred*/);

		sf::Clock           timer;
		Player m_player;
		
		std::vector<std::unique_ptr<EnemyPlayer>> enemies;

		boost::asio::ip::udp::endpoint remote_endpoint_;

		boost::array<char, 256> recv_buffer_;

		boost::asio::ip::udp::socket sock_;
	};

}

#endif // TEST_H