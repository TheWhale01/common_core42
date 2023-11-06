#include "conversion.hpp"

int get_precision(std::string const &str)
{
	size_t index;
	size_t count;

	count = 0;
	index = str.find('.');
	if (index == std::string::npos
		|| str.find_first_not_of("0f", ++index) == std::string::npos)
		return (0);
	while (str[index + count] && str[index + count] != 'f')
		count++;
	return (count);
}

void checkForm(std::string &str)
{
	bool check_f = false;
	size_t i = 0;

	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i && str[i] == '.' && str[i - 1] != '+' && str[i - 1] != '-')
	{
		check_f = true;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (check_f && str[i] == 'f')
		i++;
	if (i != str.length())
		throw (FormatNotValidException());
}

void print_char(double nb)
{
	char c;

	std::cout << "Char: ";
	if (nb < 0 || nb > 127 || std::isnan(nb))
	{
		std::cout << "Impossible." << std::endl;
		return ;
	}
	if (nb < 32 || nb == 127)
	{
		std::cout << "Non displayable." << std::endl;
		return ;
	}
	c = static_cast<char>(nb);
	std::cout << c << std::endl;
}

void print_int(double nb)
{
	int n;

	std::cout << "Int: ";
	if (nb < std::numeric_limits<int>::min() || nb > std::numeric_limits<int>::max()
		|| std::isnan(nb))
	{
		std::cout << "Impossible." << std::endl;
		return ;
	}
	n = static_cast<int>(nb);
	std::cout << n << std::endl;
}

void print_float(double nb, size_t prec)
{
	float f;

	std::cout << "Float: ";

	f = static_cast<float>(nb);
	std::cout << std::fixed << std::setprecision(prec) << f << (prec ? "f" : ".0f") << std::endl;
}

void print_double(double nb, size_t prec)
{
	std::cout << "Double: ";
	std::cout << std::fixed << std::setprecision(prec) << nb << (prec ? "" : ".0") << std::endl;
}

void get_type(std::string &str)
{
	double nb;
	size_t prec;
	std::stringstream stream(str);

	try
	{
		if (str == "-inf" || str == "+inf"
			|| str == "+inff" || str == "-inff")
		{
			nb = std::numeric_limits<double>::infinity();
			if (str == "-inf" || str == "-inff")
				nb *= -1;
		}
		else if (str == "nan" || str == "nanf")
			nb = std::numeric_limits<double>::quiet_NaN();
		else
		{
			checkForm(str);
			stream >> nb;
		}
		prec = get_precision(str);
		print_char(nb);
		print_int(nb);
		print_float(nb, prec);
		print_double(nb, prec);
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}
}