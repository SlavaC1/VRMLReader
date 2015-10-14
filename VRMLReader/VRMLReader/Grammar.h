#pragma once

#include "Types.h"
#include <boost\spirit\include\qi.hpp>	

namespace VRMLDoc
{
	using namespace boost::spirit::qi;
	using namespace std;	

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

	class CGeometryGrammar : public grammar<string::const_iterator, TModel(), space_type>
	{
	private:
		CPointGrammar                                      m_PointGrammar;
		CCoordIndexGrammar                                 m_CoordIndexGrammar;
		rule<string::const_iterator, space_type>           m_PrefixRule;
		rule<string::const_iterator, TModel(), space_type> m_StartRule;

	public:
		CGeometryGrammar();
	};
}
