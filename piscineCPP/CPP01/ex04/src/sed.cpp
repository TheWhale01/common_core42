#include "sed.hpp"

void replace(std::string &str, std::string const &search, std::string const &replace)
{
	size_t i = 0;

	while (1)
	{
		if (search.empty() || (i = str.find(search, i)) == std::string::npos)
			break;
		str.erase(i, search.length());
		str.insert(i, replace);
		i+=replace.length();
	}
}

bool is_empty(std::ifstream &stream)
{
	return (stream.peek() == std::ifstream::traits_type::eof());
}

void sed(std::string const &name, std::string const &s1, std::string const &s2)
{
	std::ifstream infile;
	std::string filename;
	std::string content;
	
	infile.open(name.c_str(), std::ifstream::in);
	if (!infile)
	{
		std::cerr << "Error while opening file: " << name <<  std::endl;
		return ;
	}
	filename = name + ".replace";
	std::ofstream outfile(filename.c_str());
	while (infile.good() && !is_empty(infile))
	{
		std::getline(infile, content);
		content += "\n";
		replace(content, s1, s2);
		outfile << content;
	}
	outfile.close();
	infile.close();
}
