#include "room.h"
namespace pt = boost::property_tree;

void room::join(boost::shared_ptr<participant> participant) {

	for (auto p : participants) {
		pt::ptree root;
		root.put("id", participant->get_id());
		root.put("x", 0);
		root.put("y", 0);
		root.put("type", "newplayer");

		std::stringstream ss;
		pt::write_json(ss, root);
		p->deliver(ss.str());
	}

	for (auto p : participants) {
		pt::ptree root;
		root.put("id", p->get_id());
		root.put("x", p->get_playerdata().pos.x);
		root.put("y", p->get_playerdata().pos.y);
		root.put("type", "newplayer");
		std::cout << p->get_id() << std::endl;

		std::stringstream ss;
		pt::write_json(ss, root);
		participant->deliver(ss.str());
	}

	participants.push_back(participant);
}

void room::leave(boost::shared_ptr<participant> participant) {

}

void room::deliver(std::string message) {

}

void room::update_participants() {
	std::string clientmessage = boost::lexical_cast<std::string > (participants.size());
	std::for_each(participants.begin(), participants.end(),
		boost::bind(&participant::deliver, _1, clientmessage));
}

void room::updatePosition(std::string id, position new_pos) {

	pt::ptree root;
	root.put("id", id);

	for (int i = 0; i < participants.size(); i++) {
		if (id == participants[i]->get_id()) {
			player& data = participants[i]->get_playerdata();
			data.pos.x = new_pos.x;
			data.pos.y = new_pos.y;
		}
	}

	root.put("x", new_pos.x);
	root.put("y", new_pos.y);

	for (int i = 0; i < participants.size(); i++) {
		if (participants[i]->get_id() == id) {

		}
		else {
			root.put("type", "moveother");
			std::stringstream ss;
			pt::write_json(ss, root);
			participants[i]->deliver(ss.str());
		}
	}
}