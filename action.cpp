#include "action.h"

Action::Action(const std::string & n, const std::string & t)
    : _name(n)
    , _type(t)
{
}

const std::string & Action::name() const
{
    return this->_name;
}

const std::string & Action::type() const
{
    return this->_type;
}

std::string Action::toString() const
{
    return "???";
}
