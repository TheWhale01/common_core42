#pragma once
#include "AMateria.hpp"

class IMateriaSource
{
	public:
		virtual ~IMateriaSource() {}
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria* createMateria(std::string const & type) = 0;	
};

class MateriaSource: public IMateriaSource
{
	public:
		MateriaSource(void);
		MateriaSource(MateriaSource const &rhs);
		~MateriaSource(void);

		MateriaSource &operator=(MateriaSource const &rhs);

		void learnMateria(AMateria *m);
		AMateria *createMateria(std::string const &type);

	private:
		AMateria *_tmp[4];
		int _index;
};