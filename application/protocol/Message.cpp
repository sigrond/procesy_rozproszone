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

hostMessage::hostMessage( HostSub sub, State state, const std::vector<Ip> & addresses ) : Message::Message( Category::HOST )
{

}

hostMessage::hostMessage( State state ) : Message::Message( Category::HOST )
{

}

unsigned short hostMessage::getAgentCount() const
{
	return 0;
}

std::vector<Ip> & hostMessage::getAddresses() const
{
	std::vector<Ip> v;
	return v;
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

fileMessage::fileMessage(State state,
						bool isMainFile,
						unsigned long tId,
						std::string filename ) : Message::Message( Category::FILE )
{
	taskId=tId;
	name=filename;
}

fileMessage::fileMessage ( State state ) : Message::Message( Category::FILE )
{

}

bool fileMessage::getIsMainFile()
{
	return 0;
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

retMessage::retMessage( State state,
					unsigned char exitStatus,
					unsigned long taskId,
					std::string filename,
					const std::ifstream & file ) : Message::Message( Category::RET )
{

}

retMessage::retMessage ( State state ) : Message::Message( Category::RET )
{

}

unsigned char retMessage::getExitStatus()
{
	return 0;
}

unsigned long retMessage::getTaskId()
{

}

std::string retMessage::getFilename()
{
	return std::string();
}

std::ofstream & retMessage::getFile()
{
	std::ofstream o("file",std::ofstream::out);
	return o;
}

synMessage::synMessage ( State state ) : Message::Message( Category::SYN )
{

}

pingMessage::pingMessage ( State state ) : Message::Message( Category::PING )
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
























