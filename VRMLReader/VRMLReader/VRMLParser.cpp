

#include "VRMLParser.h"
#include "Grammar.h"
#include <boost\chrono.hpp>


CVRMLParser::CVRMLParser()
{
}

CVRMLParser::~CVRMLParser()
{
}


void CVRMLParser::Parse(const std::string &Data)
{	
	namespace ch = boost::chrono;	
	
	std::vector<TCoordIndex> indexes;	
	CCoordIndexGrammar g;	
	
	std::vector<TPoint> points;	
	CPointGrammar g2;

	TModel VRML;	
	CModelGrammar g3;

	auto start = ch::high_resolution_clock::now();	
	bool r = phrase_parse(Data.begin(), Data.end(), g3, space, VRML);	
	auto end = ch::high_resolution_clock::now();

	auto duration = ch::duration_cast<ch::milliseconds>(end - start).count();

	std::cout << "Parsing time: " << duration << " msec" << std::endl;
	//std::cout << "Parsed indexes: " << indexes.size() << std::endl;
	
	std::cout << "Parsed indexes: " << VRML.indexes.size() << std::endl << "Parsed points:  " << VRML.points.size() << std::endl;

	

	
	/*
	// Parses doubles into vector
	std::vector<double> value;
	std::string str = "2.5 3.6 89.456";
	bool status = qi::phrase_parse(str.begin(), str.end(), +qi::double_, qi::space, value);
	*/

	/*
	// Parses comma separated doubles
	std::vector<double> value;
	std::string str = "2.5,3.6,89.456";
	bool status = qi::phrase_parse(str.begin(), str.end(), qi::double_ >> *(',' >> qi::double_), qi::space, value);
	*/

	/*
	// Parses int and uses function object to print
	struct print_action
	{
		void operator()(double const& i, qi::unused_type, qi::unused_type) const
		{
			std::cout << i << std::endl;
		}
	};

	double value;
	std::string str = "{ 2.5 }";
	bool status = qi::phrase_parse(str.begin(), str.end(), '{' >> qi::double_[print_action()] >> '}', qi::space, value);
	*/

	/*
	// Parses comma separated doubles with shortcut
	std::vector<double> value;
	std::string str = "2.5,3.6,89.456";
	bool status = qi::phrase_parse(str.begin(), str.end(), qi::double_ % ',', qi::space, value);	
	*/


	
	

}