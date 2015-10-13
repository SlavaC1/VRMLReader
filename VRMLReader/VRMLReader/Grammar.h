#pragma once

#include <boost\spirit\include\qi.hpp>	

struct TPoint
{
	double x;
	double y;
	double z;

	TPoint() : x(0.0), y(0.0), z(0.0){}
};

struct TCoordIndex
{
	int x;
	int y;
	int z;

	TCoordIndex() : x(0), y(0), z(0){}
};

using namespace boost::spirit::qi;
using namespace std;

struct TModel
{
	vector<TPoint>      points;
	vector<TCoordIndex> indexes;
};

class CPointGrammar : public grammar<string::const_iterator, std::vector<TPoint>(), space_type>
{
private:
	rule<string::const_iterator, TPoint(), space_type>         m_SinglePointRule;
	rule<string::const_iterator>                               m_CommentRule;
	rule<string::const_iterator, space_type>                   m_PrefixRule;
	rule<string::const_iterator, vector<TPoint>(), space_type> m_StartRule;

public:
	CPointGrammar();
};


class CCoordIndexGrammar : public grammar<string::const_iterator, vector<TCoordIndex>(), space_type>
{
private:
	rule<string::const_iterator, TCoordIndex(), space_type>         m_SingleIndexRule;
	rule<string::const_iterator>                                    m_CommentRule;
	rule<string::const_iterator, space_type>                        m_PrefixRule;
	rule<string::const_iterator, vector<TCoordIndex>(), space_type> m_StartRule;

public:
	CCoordIndexGrammar();
};

class CModelGrammar : public grammar<string::const_iterator, TModel(), space_type>
{
private:
	CPointGrammar                                      m_PointGrammar;
	CCoordIndexGrammar                                 m_CoordIndexGrammar;
	rule<string::const_iterator, TModel(), space_type> m_StartRule;

public:
	CModelGrammar();
};
