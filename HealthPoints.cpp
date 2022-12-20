//
// Created by USER on 19/12/2022.
//

#include "HealthPoints.h"

HealthPoints::HealthPoints(int max_hp ) 
{
    if(max_hp<=0)
    {
    throw HealthPoints::InvalidArgument();
    }
m_max_hp=max_hp;
    m_hp=max_hp;
}
 bool operator==(const HealthPoints& h1, const HealthPoints& h2)
{if(h1.m_hp==h2.m_hp)
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
