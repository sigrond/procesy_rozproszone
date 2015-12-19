/** \file Message.cpp
 *
 * \authors Tomasz Jakubczyk, ...
 * \brief Plik z implementacjami metod klasy Message.
 * \todo Andrzej napisze, a na razie zaślepki.
 */

#include "Message.hpp"

using namespace message;

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
						State state,
						bool respectPriority,
						unsigned short priority,
						unsigned long taskId,
						const std::chrono::steady_clock::time_point & timestamp ) : Message::Message( Category::TASK )
{

}

taskMessage::taskMessage( State state ) : Message::Message( Category::TASK )
{

}

bool taskMessage::getRespectPriority()
{
	return 0;
}

unsigned short taskMessage::getPriority() const
{
	return 0;
}

unsigned long taskMessage::getTaskId() const
{
	return 0;
}

std::chrono::steady_clock::time_point & taskMessage::getTimestamp() const
{
	std::chrono::steady_clock::time_point t;
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
						unsigned long taskId,
						std::string filename,
						const std::ifstream & file ) : Message::Message( Category::FILE )
{

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
	return 0;
}

std::string fileMessage::getFilename()
{
	return std::string();
}

std::ofstream & fileMessage::getFile()
{
	std::ofstream o("file",std::ofstream::out);
	return o;
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
























