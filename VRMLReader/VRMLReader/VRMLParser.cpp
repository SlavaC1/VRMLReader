#include "VRMLParser.h"

#include <boost\spirit\include\qi.hpp>
#include <boost\fusion\include\adapt_struct.hpp>

CVRMLParser::CVRMLParser()
{
}

CVRMLParser::~CVRMLParser()
{
}





struct CoordIndex
{
	int a;
	int b;
	int c;

	CoordIndex() : a(0), b(0), c(0){}
};

BOOST_FUSION_ADAPT_STRUCT
(
	CoordIndex,
	(int, a)
	(int, b)
	(int, c)	
)

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct CoordIndexParser : boost::spirit::qi::grammar<Iterator, CoordIndex(), qi::space_type>
{
	CoordIndexParser() : CoordIndexParser::base_type(start)
	{
		start %= qi::lit("coordIndex") >> '[' >> qi::int_ >> qi::int_ >> qi::int_ >> qi::lit("-1");
	}

	qi::rule<Iterator, CoordIndex(), qi::space_type> start;
};




void CVRMLParser::Parse(const std::string &Data)
{
	namespace qi = boost::spirit::qi;

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


	
	CoordIndex coord;

	typedef std::string::const_iterator iterator_type;
	typedef CoordIndexParser<iterator_type> indexParser;

	indexParser g; 

	std::string::const_iterator iter = Data.begin();
	std::string::const_iterator end = Data.end();

	bool r = phrase_parse(iter, end, g, qi::space, coord);

}