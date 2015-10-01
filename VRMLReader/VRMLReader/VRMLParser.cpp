
//#define BOOST_SPIRIT_DEBUG

#include "VRMLParser.h"
#include <boost\chrono.hpp>
#include <boost\spirit\include\qi.hpp>
#include <boost\fusion\include\adapt_struct.hpp>
#include <boost\spirit\repository\include\qi_seek.hpp>
#include <boost\spirit\include\qi_repeat.hpp>

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

namespace qi   = boost::spirit::qi;
namespace repo = boost::spirit::repository;

template <typename Iterator>
struct CoordIndexParser : boost::spirit::qi::grammar<Iterator, std::vector<CoordIndex>(), qi::space_type>
{
	CoordIndexParser() : CoordIndexParser::base_type(start)
	{
		singleIndex  = qi::int_ >> qi::int_ >> qi::int_ >> qi::lit("-1");
		start       %= repo::seek[qi::lexeme[qi::skip[qi::lit("coordIndex") >> '[' >> qi::repeat[singleIndex]]]];

		//BOOST_SPIRIT_DEBUG_NODES((singleIndex)(start));
	}

	qi::rule<Iterator, CoordIndex(), qi::space_type>              singleIndex;
	qi::rule<Iterator, std::vector<CoordIndex>(), qi::space_type> start;	
};




void CVRMLParser::Parse(const std::string &Data)
{
	namespace qi = boost::spirit::qi;
	namespace ch = boost::chrono;

	CoordIndex coord;
	std::vector<CoordIndex> vec;

	typedef CoordIndexParser<std::string::const_iterator> indexParser;

	indexParser g;

	auto start = ch::high_resolution_clock::now();
	bool r = phrase_parse(Data.begin(), Data.end(), g, qi::space, vec);
	auto end = ch::high_resolution_clock::now();

	auto duration = ch::duration_cast<boost::chrono::milliseconds>(end - start).count();

	int i = 2;

	
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