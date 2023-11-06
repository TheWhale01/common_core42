#include "Cat.hpp"
#include "Dog.hpp"

int main(void)
{
	int nb_animals = 2;
	Animal *zoo[nb_animals];

	// SUBJECT
	for (int i = 0; i < nb_animals; i++)
	{
		if (i % 2)
			zoo[i] = new Cat();
		else
			zoo[i] = new Dog();
		std::cout << std::endl;
	}
	for (int i = 0; i < nb_animals; i++)
	{
		delete zoo[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// DEEP COPY
	Cat cat;
	Cat copy;

	cat.setIdea(1, "bonsoir");
	copy = cat;
	std::cout << "Original: " << cat.getIdea(1) << std::endl;
	std::cout << "Copy: " << copy.getIdea(1) << std::endl;
	copy.setIdea(1, "salut !");
	std::cout << "Original: " << cat.getIdea(1) << std::endl;
	std::cout << "Copy: " << copy.getIdea(1) << std::endl << std::endl;
	Animal *new_cat = new Cat();
	new_cat->makeSound();
	std::cout << std::endl;
	delete new_cat;
	return 0;
}
