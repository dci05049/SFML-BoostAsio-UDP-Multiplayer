#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "participant.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <set>

class room {
public: 
	void join(boost::shared_ptr<participant> participant);

	void leave(boost::shared_ptr<participant> participant);

	void deliver(const std::string message);

	void updatePosition(const std::string sender_id, position new_pos);

private:
	void update_participants();

	std::vector<boost::shared_ptr<participant>> participants;
};

#endif // !ROOM_H

