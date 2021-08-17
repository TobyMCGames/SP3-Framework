#include "Zombie.h"
#include "SkeletonArcher.h"
#include "Player.h"
//#include "Turret.h"
//#include "Spider.h"
//#include "Boomer.h"
//#include "Demonlord.h"

template <typename T>

class Prototype
{
public:
	T* clone();
	return new T;
};

template<typename T>
inline T* Prototype<T>::clone()
{
	return nullptr;
}
