#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <string>
#include "structdata.h"
#include <boost\shared_ptr.hpp>

class participant {
public: 
	virtual ~participant() {}
	virtual void deliver(std::string message) = 0;
	virtual std::string get_id() = 0;
	virtual player& get_playerdata() = 0;

	//player player_;
};

#endif