#include "HealthPoints.h"

HealthPoints::HealthPoints(int maxHP){
  if(maxHP<=0){
    throw HealthPoints:InvalidArgument();
  }
  m_HP=maxHp;
  m_maxHP=maxHP;
}
