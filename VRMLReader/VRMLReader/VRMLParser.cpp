
#define BOOST_SPIRIT_DEBUG

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


struct Point
{
	double a;
	double b;
	double c;

	Point() : a(0.0), b(0.0), c(0.0){}
};

BOOST_FUSION_ADAPT_STRUCT
(
	Point,
	(double, a)	
	(double, b)
	(double, c)
)


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

struct VRML_t
{
	std::vector<Point>      points;
	std::vector<CoordIndex> indexes;
};

BOOST_FUSION_ADAPT_STRUCT
(
	VRML_t,
	(std::vector<Point>,      points)
	(std::vector<CoordIndex>, indexes)
)


template <typename Iterator>
struct PointParser : qi::grammar<Iterator, std::vector<Point>(), qi::space_type>
{
	PointParser() : PointParser::base_type(start, "PointGrammar")
	{
		singlePoint = qi::double_ >> qi::double_ >> qi::double_ >> *qi::lit(",");
		comment     = "#" >> *(qi::ascii::char_ - qi::eol);
		prefix      = repo::seek[qi::lit("point") >> "[" >> *comment];
		start      %= prefix >> *singlePoint;		

		//BOOST_SPIRIT_DEBUG_NODES((prefix)(comment)(singlePoint)(start));
	}

	qi::rule<Iterator, Point(), qi::space_type>              singlePoint;
	qi::rule<Iterator>                                       comment;
	qi::rule<Iterator, qi::space_type>                       prefix;
	qi::rule<Iterator, std::vector<Point>(), qi::space_type> start;
};

template <typename Iterator>
struct CoordIndexParser : qi::grammar<Iterator, std::vector<CoordIndex>(), qi::space_type>
{
	CoordIndexParser() : CoordIndexParser::base_type(start, "CoordIndexGrammar")
	{
		singleIndex  = qi::int_ >> qi::int_ >> qi::int_ >> qi::lit("-1") >> *qi::lit(",");
		comment      = "#" >> *(qi::ascii::char_ - qi::eol);
		prefix       = repo::seek[qi::lit("coordIndex") >> "[" >> *comment];
		start       %= prefix >> *singleIndex;		

		//BOOST_SPIRIT_DEBUG_NODES((start)(prefix)(singleIndex));
	}

	qi::rule<Iterator, CoordIndex(), qi::space_type>              singleIndex;
	qi::rule<Iterator>                                            comment;
	qi::rule<Iterator, qi::space_type>                            prefix;
	qi::rule<Iterator, std::vector<CoordIndex>(), qi::space_type> start;	
};


template <typename Iterator>
struct VRMLParser : qi::grammar<Iterator, VRML_t(), qi::space_type>
{
	VRMLParser() : VRMLParser::base_type(start, "VRMLGrammar")
	{
		start %= pointParser >> coordIndexParser;
	}

	PointParser<Iterator>      pointParser;
	CoordIndexParser<Iterator> coordIndexParser;
	qi::rule<Iterator, VRML_t(), qi::space_type> start;
	
};



void CVRMLParser::Parse(const std::string &Data)
{
	namespace qi = boost::spirit::qi;
	namespace ch = boost::chrono;	
	
	std::vector<CoordIndex> indexes;
	//vec.reserve(170000);

	typedef CoordIndexParser<std::string::const_iterator> indexParser;	
	indexParser g;


	std::vector<Point> points;
	typedef PointParser<std::string::const_iterator> pointParser;
	pointParser g2;

	VRML_t VRML;
	typedef VRMLParser<std::string::const_iterator> finalParser;
	finalParser g3;

	auto start = ch::high_resolution_clock::now();	
	bool r = phrase_parse(Data.begin(), Data.end(), g3, qi::space, VRML);	
	auto end = ch::high_resolution_clock::now();

	auto duration = ch::duration_cast<boost::chrono::milliseconds>(end - start).count();

	std::cout << "The duration is: " << duration << " msec" << std::endl;
	
	std::cout << "Parsed indexes: " << VRML.indexes.size() << std::endl << "Parsed points: " << VRML.points.size() << std::endl;

	

	
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