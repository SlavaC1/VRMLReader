
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


template <typename Iterator>
struct PointParser : boost::spirit::qi::grammar<Iterator, std::vector<Point>(), qi::space_type>
{
	PointParser() : PointParser::base_type(start, "PointGrammar")
	{
		singlePoint = qi::double_ >> qi::double_ >> qi::double_ >> qi::lit(",");
		comment     = qi::lit("#") >> *(qi::char_ - qi::eol);
		prefix      = repo::seek[qi::lexeme[qi::skip[qi::lit("point") >> qi::lit("[") >> comment]]];
		start      %= prefix >> qi::repeat[singlePoint];

		singlePoint.name("SinglePointRule");
		comment.name("CommentRule");
		start.name("StartRule");

		BOOST_SPIRIT_DEBUG_NODES((singlePoint));
	}

	qi::rule<Iterator, Point(), qi::space_type>              singlePoint;
	qi::rule<Iterator, std::string(), qi::space_type>        comment;
	qi::rule<Iterator, std::string(), qi::space_type>        prefix;
	qi::rule<Iterator, std::vector<Point>(), qi::space_type> start;
};

template <typename Iterator>
struct CoordIndexParser : boost::spirit::qi::grammar<Iterator, std::vector<CoordIndex>(), qi::space_type>
{
	CoordIndexParser() : CoordIndexParser::base_type(start, "CoordIndexGrammar")
	{
		singleIndex  = qi::int_ >> qi::int_ >> qi::int_ >> qi::lit("-1");
		start       %= repo::seek[qi::lexeme[qi::skip[qi::lit("coordIndex") >> qi::lit("[") >> qi::repeat[singleIndex]]]];

		singleIndex.name("SingleIndexRule");
		start.name("StartRule");

		//BOOST_SPIRIT_DEBUG_NODES((singleIndex)(start));
	}

	qi::rule<Iterator, CoordIndex(), qi::space_type>              singleIndex;
	qi::rule<Iterator, std::vector<CoordIndex>(), qi::space_type> start;	
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

	auto start = ch::high_resolution_clock::now();
	bool r = phrase_parse(Data.begin(), Data.end(), g2, qi::space, points);
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