#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action
{
    std::string _name;
    std::string _type;
    
public:
    Action() = delete;
    Action(const std::string & n, const std::string & t);
    
    const std::string & name() const;
    const std::string & type() const;
    
    std::string toString() const;
};

#endif
