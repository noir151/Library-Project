#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member {
public:
    int id;
    std::string name;
    std::string email;
    std::string address;

    Member();

    void addMember();

    int generateMemberId();
};

#endif // MEMBER_H