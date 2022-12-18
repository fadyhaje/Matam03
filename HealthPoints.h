#ifndef HEALTH_POINTS_H
#define HEALTH_POINTS_H

#include <stdio.h>
#include <stdbool.h>
#include <iostream>

#define DEFAULT_MAX_HP 100

class HealthPoints{
public:
    
    /* 
     * C'tor of HealthPoints class
     *
     *param max_hp
     *    the maximum healthpoints the object couldh have
     *    in case the usesr didn't send one it would be set as 100
     * @return
     *      A new Healthpoints object
     * .
    */ 

HealthPoints(int max_hp = DEFAULT_MAX_HP);

/*
* Error in case of an negative values 
*/
class InvalidArgument {} ;


/*
* param health
*   the health we need to add to the current health points
* return
*   reference to the object
* 
*/

HealthPoints& operator+=(const int health);


/*
*param health
*   the health we need to subtract to the current health points
* return
*   reference to the object
*/

HealthPoints& operator-=(const int health);

/*
* param health
*   the health we need to add to the current health points
* return
*    an object that was updated according to health
* 
*/

HealthPoints operator+(const int health) const ;

/*
*param health
*   the health we need to subtract to the current health points
* return
*    an object that was updated according to health
*/

HealthPoints operator-(const int health) const;

private:  
int m_hp;
int m_max_hp;

/*
*prints the current object's health points out of the maximum health points
* for example: 
*   current health points:100, maximum health points:150
*   prints 100(150)
*/

friend std :: ostream& operator<<(std:: ostream& os,const HealthPoints& object);

/*
*compares the health points of h1 and h2 
*  return :
*        true in case of equal health points
*        false, otherwise
*/
friend bool operator==(const HealthPoints& h1, const HealthPoints& h2); 

/*
*compares the health points of h1 and h2 
*param 
*  h1, the first object we want to compare with
*  h2, the second object we want to compare with
*  return :
*        true in case the first object(h1) has less health points than the second object(h2)
*        false, otherwise
*/

friend bool operator<(const HealthPoints& h1, const HealthPoints& h2); 

};

/*
*compares the health points of h1 and h2 
*param 
*  h1, the first object we want to compare with
*  h2, the second object we want to compare with
*  return :
*        true in case the two objects have different health points
*        false, otherwise
*/

bool operator!=(const HealthPoints& h1,const HealthPoints& h2);

/*
*compares the health points of h1 and h2 
*param 
*  h1, the first object we want to compare with
*  h2, the second object we want to compare with
*  return :
*        true in case the first object(h1) has less or equal health points than the second object(h2)
*        false, otherwise
*/

bool operator<=(const HealthPoints& h1,const HealthPoints& h2); 

/*
*compares the health points of h1 and h2 
*param 
*  h1, the first object we want to compare with
*  h2, the second object we want to compare with
*  return :
*        true in case the first object(h1) has more or equal health points than the second object(h2)
*        false, otherwise
*/

bool operator>=(const HealthPoints& h1,const HealthPoints& h2); 

/*
*compares the health points of h1 and h2 
*param 
*  h1, the first object we want to compare with
*  h2, the second object we want to compare with
*  return :
*        true in case the first object(h1) more health points than the second object(h2)
*        false, otherwise
*/

bool operator>(const HealthPoints& h1,const HealthPoints& h2); 

/*
*param num
*  the number we want to add to the object's health points 
*param object
*   the object we want to add certain amount(num) of health points to
* return
*    an object that was updated according to num
*/

HealthPoints operator+(const int num, HealthPoints& object);

#endif 
