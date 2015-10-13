#include "Grammar.h"

#include <boost\fusion\include\adapt_struct.hpp>
#include <boost\spirit\repository\include\qi_seek.hpp>
#include <boost\spirit\include\qi_repeat.hpp>


using namespace boost::spirit::repository;

BOOST_FUSION_ADAPT_STRUCT
(
	TPoint,
	(double, x)
	(double, y)
	(double, z)
)

BOOST_FUSION_ADAPT_STRUCT
(
	TCoordIndex,
	(int, x)
	(int, y)
	(int, x)
)

BOOST_FUSION_ADAPT_STRUCT
(
	TModel,
	(std::vector<TPoint>, points)
	(std::vector<TCoordIndex>, indexes)
)

CPointGrammar::CPointGrammar() : CPointGrammar::base_type(m_StartRule, "PointGrammar")
{
	m_SinglePointRule = double_ >> double_ >> double_ >> *lit(",");	
	m_PrefixRule = seek[lit("point") >> "[" >> *m_CommentRule];
	m_CommentRule = "#" >> *(ascii::char_ - eol);
	m_StartRule %= m_PrefixRule >> *m_SinglePointRule;

	//BOOST_SPIRIT_DEBUG_NODES((m_PrefixRule)(m_CommentRule)(m_SinglePointRule)(m_StartRule));
}

CCoordIndexGrammar::CCoordIndexGrammar() : base_type(m_StartRule, "CoordIndexGrammar")
{
	m_SingleIndexRule = int_ >> *lit(",") >> int_ >> *lit(",") >> int_ >> *lit(",") >> lit("-1") >> *lit(",");	
	m_PrefixRule = seek[lit("coordIndex") >> "[" >> *m_CommentRule];
	m_CommentRule = "#" >> *(ascii::char_ - eol);
	m_StartRule %= m_PrefixRule >> *m_SingleIndexRule;

	//BOOST_SPIRIT_DEBUG_NODES((m_StartRule)(m_PrefixRule)(singleIndexm_SingleIndexRule));
}

CModelGrammar::CModelGrammar() : base_type(m_StartRule, "ModelGrammar")
{
	m_StartRule %= m_PointGrammar >> m_CoordIndexGrammar;
}

