#ifndef HealthPoints_hpp
#define HealthPoints_hpp

#include <stdio.h>
#include <iostream>

class HealthPoints
{
private:
    int m_HP;
    int m_maxHP;
    int getHP() const;
    int getMaxHP()const;
public:
    HealthPoints& operator=(const HealthPoints& HP);
    HealthPoints(int maxHP=100);
    HealthPoints& operator+=(int HP);
    HealthPoints& operator-=(int HP);
    friend std::ostream& operator<<(std::ostream& os,const HealthPoints& healthPoint);
    friend bool operator==(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
    friend bool operator<(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
class InvalidArgument{};
};
HealthPoints operator+(int HP,const HealthPoints& healthPoint2);
HealthPoints operator+(const HealthPoints& healthPoint1,int HP);
HealthPoints operator-(const HealthPoints& healthPoint1,int HP);

bool operator!=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
bool operator>(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
bool operator>=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);
bool operator<=(const HealthPoints& healthPoint1,const HealthPoints& healthPoint2);

#endif /* HealthPoints_hpp *
