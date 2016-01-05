
namespace message
{
class Command
{
    public:
    Task();
    ~Task();

    private:

};

class SynCommand: public Command
{
    public:
    SynCommand(Message *msg);
    private:

    synMessage sMessage;
};

class TaskCommand: public Command
{
};

class DepCommand: public Command
{
};

class FileCommand: public Command
{

};

class PingCommand: public Command
{
};
}
