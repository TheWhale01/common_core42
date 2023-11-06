#include "Materias.hpp"
#include "MateriaSource.hpp"

int main() //MAIN TEST
{
	IMateriaSource* src = new MateriaSource();
	ICharacter* me = new Character("me");
	ICharacter* bob = new Character("bob");
	AMateria* tmp;
	AMateria* tmp3;
	AMateria* tmp4;
	AMateria* tmp5;



	std::cout << "\n*******************LEARN TEST********************\n" << std::endl;
	std::cout << "Learn Ice in 0/3 emplacement" << std::endl; 
	src->learnMateria(new Ice());

	std::cout << "Learn Cure in 1/3 emplacement" << std::endl;
	src->learnMateria(new Cure());

	std::cout << "Learn Ice in 2/3 emplacement" << std::endl;
	src->learnMateria(new Ice());

	std::cout << "Learn Cure in 3/3 emplacement" << std::endl;
	src->learnMateria(new Cure());



	std::cout << "\n***************CREATE AND EQUIP TEST**************\n" << std::endl;
	std::cout << "create and equip Ice in 0/3 emplacement" << std::endl; 
	tmp = src->createMateria("ice");
	me->equip(tmp);

	std::cout << "equip the same Ice in 1/3 emplacement" << std::endl; 
	me->equip(tmp);

	std::cout << "create and equip Cure in 2/3 emplacement" << std::endl; 
	tmp3 = src->createMateria("cure");
	me->equip(tmp3);

	std::cout << "create and equip Cure in 3/3 emplacement" << std::endl; 
	tmp4 = src->createMateria("cure");
	me->equip(tmp4);

	std::cout << "Try to create and equip two more materia but it's impossible" << std::endl;
	tmp5 = src->createMateria("Wrong_Materia");
	me->equip(tmp5);
	tmp5 = src->createMateria("cure");
	me->equip(tmp5);
	delete tmp5;
	



	std::cout << "\n*********************USE TEST*********************\n" << std::endl;
	std::cout << "Using the zero Inventory Item " << std::endl; 
	me->use(0, *bob);

	std::cout << "\nUsing the first Inventory Item " << std::endl; 
	me->use(1, *bob);

	std::cout << "\nUsing the second Inventory Item " << std::endl; 
	me->use(2, *bob);

	std::cout << "\nUsing the third Inventory Item " << std::endl; 
	me->use(3, *bob);
	



	std::cout << "\n******************UNEQUIP TEST******************\n" << std::endl;
	std::cout << "Unequip the zero Inventory Item and try to use it " << std::endl; 
	me->unequip(0);
	me->use(0, *bob);

	std::cout << "Unequip the first Inventory Item and try to use it " << std::endl;
	me->unequip(1);
	me->use(1, *bob);

	std::cout << "Unequip the second Inventory Item (Ice) and equip with the first learn emplacement (Cure) and use it" << std::endl; 
	me->unequip(2);
	tmp5 = src->createMateria("cure");
	me->equip(tmp5);
	me->use(0, *bob);

	std::cout << "Unequip all, more and wrong index" << std::endl; 
	me->unequip(0);
	me->unequip(1);
	me->unequip(2);
	me->unequip(3);
	me->unequip(-1);
	me->unequip(4);

	delete tmp;
	delete tmp3;
	delete tmp4;
	delete tmp5;
	delete me;
	delete bob;
	delete src;
	return (0);
}