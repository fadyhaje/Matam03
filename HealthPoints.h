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
     *    max_hp eqaulls the maximum healthpoint,default=100
     * @return
     *      a new healthoint
     * .
    */

    HealthPoints(int max_hp = DEFAULT_MAX_HP);

/*
* class for non positive or zero values 
*/
    class InvalidArgument {} ;


/*
* param health
*   the health equalls healthponits that we want to add to *this
* return
*   reference of the object
* 
*/
    int get()
    {
        return m_hp;
    }
    HealthPoints& operator+=(const int health);


/*
*param health
*   the health equalls healthponits we want to subtract from *this
* return
*   reference of the object
*/

    HealthPoints& operator-=(const int health);

/*
* param health
*   the health equalls healthponits that we want to add to *this
* return
*    the updated object after adding health
* 
*/

    HealthPoints operator+(const int health) const ;

/*
*param health
*   the health equalls healthponits we want to subtract from *this
* return
*    the updated object after subtracting health
*/

    HealthPoints operator-(const int health) const;

private:
    int m_hp;
    int m_max_hp;

/*
*prints the the healthpoints of the object with max_hp
*/

    friend std :: ostream& operator<<(std:: ostream& os,const HealthPoints& object);

/*
*checks if the health points of h1 and h2 are equall
*  return :
*        equall healthponits between h1 &h2 =true 
*        otherwsie =false, otherwise
*/
    friend bool operator==(const HealthPoints& h1, const HealthPoints& h2);

/*
*checks if  the health points of h1 are smaller than h2 
*param 
*  h1, the first object 
*  h2, the second object 
*  return :
*        healthponits of h1 is smaller than h2 =true 
*        otherwise=false
*/

    friend bool operator<(const HealthPoints& h1, const HealthPoints& h2);

};

/*
*checks if  the health points of h1 and h2 are different
*param
*  h1, the first object 
*  h2, the second object 
*  return :
*        the healthpoints of h1 &h2 are equal=true 
*        otherwise=false
*/

bool operator!=(const HealthPoints& h1,const HealthPoints& h2);

/*
*checks if the health points of h1 is samller or equall to h2 healthponits
*param 
*  h1, the first object 
*  h2, the second object
*  return :
*        the healthpoints of h1 is smaller or equall to h2 =true  
*        otherwise=false
*/

bool operator<=(const HealthPoints& h1,const HealthPoints& h2);

/*
*checks if the health points of h1 is bigger or equal than h2 
*param 
*  h1, the first object 
*  h2, the second object 
*  return :
*        the healthpoints of h1 is bigger or equall to h2 =true in  
*        otherwise=false
*/

bool operator>=(const HealthPoints& h1,const HealthPoints& h2);

/*
*checks if the health points of h1 is bigger than h2 
*param 
*  h1, the first object 
*  h2, the second object
*  return :
*        the healthponits of h1 is bigger than h2=true 
*        otherwise=false
*/

bool operator>(const HealthPoints& h1,const HealthPoints& h2);

/*
*param num
*  health1 we want to add to the health2 health points 
*param object
*   object the object we want to increase his healthpoints
* return
*    object after beign updated
*/

HealthPoints operator+(const int health1, HealthPoints& object) ;
/*
*param num
*  health1 we want to subtract to the health2 health points 
*param object
*   object the object we want to decrease his healthpoints
* return
*   object after beign updated
*/

HealthPoints operator-(const int health1, HealthPoints& object) ;


#endif 
