/** \file Message.cpp
 *
 * \authors Tomasz Jakubczyk, ...
 * \brief Plik z implementacjami metod klasy Message.
 * \todo Andrzej napisze, a na razie zaślepki.
 */

#include "Message.hpp"

using namespace message;
using namespace std;

Message::Message( Category category ) : code( (unsigned char) category )
{

}

Message::~Message()
{

}


                                                        bool Message::checkMessage() const {}


unsigned char Message::getCode() const
{
	return code;
}

unsigned char Message::getCategory() const
{
	return 0;
}

unsigned char Message::getState() const
{
	return 0;
}

unsigned char Message::getSubcategory() const
{
	return 0;
}

hostMessage::hostMessage( HostSub su, State st, const std::vector<Ipv4> & addr ) :
	Message::Message( Category::HOST ),
	sub(su),
	state(st),
	addresses(addr)
{

}

hostMessage::hostMessage( State s ) :
	Message::Message( Category::HOST ),
	state(s)
{

}

unsigned short hostMessage::getAgentCount() const
{
	return addresses.size();
}

std::vector<Ipv4> & hostMessage::getAddresses()
{
	return addresses;
}

taskMessage::taskMessage( TaskSub sub,
						State s,
						bool rPriority,
						unsigned short priority,
						unsigned long tId,
						const std::chrono::steady_clock::time_point & timestamp ) :
							 Message::Message( Category::TASK ),
							 taskSub(sub),
							 state(s),
							 respectPriority(rPriority),
							 taskId(tId),
							 time(timestamp)

{

}

taskMessage::taskMessage( State s ) :
	Message::Message( Category::TASK ),
	state(s)
{

}

bool taskMessage::getRespectPriority()
{
	return respectPriority;
}

unsigned short taskMessage::getPriority() const
{
	return priority;
}

unsigned long taskMessage::getTaskId() const
{
	return taskId;
}

std::chrono::steady_clock::time_point & taskMessage::getTimestamp() const
{
	std::chrono::steady_clock::time_point t(time);
	return t;
}

depMessage::depMessage ( State state, std::vector<unsigned long> & tasks ) : Message::Message( Category::DEP )
{

}

depMessage::depMessage ( State state ) : Message::Message( Category::DEP )
{

}

unsigned short depMessage::getTaskCount()
{
	return 0;
}

std::vector<unsigned long> & depMessage::getTasks()
{
	std::vector<unsigned long> v;
	return v;
}

fileMessage::fileMessage(State s,
						bool isMainF,
						unsigned long tId,
						std::string filename ) :
							Message::Message( Category::FILE ),
							state(s),
							isMainFile(isMainF),
							taskId(tId),
							name(filename)
{
	//taskId=tId;
	//name=filename;
}

fileMessage::fileMessage ( State s ) :
	Message::Message( Category::FILE ),
	state(s)
{

}

bool fileMessage::getIsMainFile()
{
	return isMainFile;
}

unsigned long fileMessage::getTaskId()
{
	return taskId;
}

std::string fileMessage::getFilename()
{
	return name;
}

std::fstream & fileMessage::getFile()
{
	file.open(name.c_str(),std::fstream::out);
	return file;
}

retMessage::retMessage( State s,
					unsigned char exitStatus,
					unsigned long tId,
					std::string filename) :
						Message::Message( Category::RET ),
						state(s),
						taskId(tId),
						name(filename)
{

}

retMessage::retMessage ( State s ) :
	Message::Message( Category::RET ),
	state(s)
{

}

unsigned char retMessage::getExitStatus()
{
	return exitStatus;
}

unsigned long retMessage::getTaskId()
{
	return taskId;
}

std::string retMessage::getFilename()
{
	return name;
}

std::fstream & retMessage::getFile()
{
	file.open(name.c_str(),std::fstream::out);
	return file;
}

synMessage::synMessage ( State state ) : Message::Message( Category::SYN )
{

}

pingMessage::pingMessage ( State s ) :
	Message::Message( Category::PING ),
	state(s)
{

}

errMessage::errMessage ( ErrSub sub, State state, unsigned char errCode ) : Message::Message( Category::ERR )
{

}

errMessage::errMessage ( State state ) : Message::Message( Category::ERR )
{

}

unsigned char errMessage::getErrCode () const
{

}
























