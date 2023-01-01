//
// Created by USER on 19/12/2022.
//

#include "HealthPoints.h"
#define MIN_HP 0

HealthPoints::HealthPoints(int max_hp)
{
    if(max_hp<=MIN_HP)
    {
        throw HealthPoints::InvalidArgument();
    }
    m_hp=max_hp;
    m_max_hp=max_hp;
}

HealthPoints& HealthPoints::operator+=(const int health){
    if((this->m_hp+health)<MIN_HP){
        m_hp=MIN_HP;
    }
    else if((this->m_hp+health)>m_max_hp){
        m_hp=m_max_hp;
    }
    else{
        m_hp+=health;
    }
    return *this;
}

HealthPoints& HealthPoints::operator-=(const int health){
    if((this->m_hp-health)<MIN_HP){
        m_hp=MIN_HP;
    }
    else if((this->m_hp-health)>m_max_hp){
        m_hp=m_max_hp;
    }
    else{
        m_hp-=health;
    }
    return *this;
}

HealthPoints HealthPoints::operator+(const int health) const {
    HealthPoints temp(*this);
    return (temp+=health);
}

HealthPoints operator+(const int health1, HealthPoints& health2)
{
    HealthPoints result(health2+health1);
    return result;
}
HealthPoints HealthPoints::operator-(const int health) const {
    HealthPoints temp(*this);
    return (temp-=health);
}
HealthPoints operator-(const int health1, HealthPoints& health2)
{
    HealthPoints result(health2-health1);
    return result;
}
bool operator==(const HealthPoints& h1, const HealthPoints& h2)
{
    if(h1.m_hp==h2.m_hp)
    {
        return true;
    }
    return false;
}

bool operator!=(const HealthPoints& h1,const HealthPoints& h2)
{
    if(h1==h2)
    {
        return false;
    }
    return true;
}
bool operator<(const HealthPoints& h1, const HealthPoints& h2)
{
    if(h1.m_hp<h2.m_hp)
    {
        return true;
    }
    return false;
}

bool operator<=(const HealthPoints& h1,const HealthPoints& h2)
{
    if(h1<h2||h1==h2)
    {
        return true;
    }
    return false;
}
bool operator>=(const HealthPoints& h1,const HealthPoints& h2)
{
    if(h1<h2)
    {
        return false;
    }
    return true;

}
bool operator>(const HealthPoints& h1,const HealthPoints& h2)
{
    if(h1<=h2)
    {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os,const HealthPoints& health_point){
    return os << health_point.m_hp << '(' << health_point.m_max_hp << ')';
}
