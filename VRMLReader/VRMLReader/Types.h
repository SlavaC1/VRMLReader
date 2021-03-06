#pragma once

#include <vector>
#include <boost\fusion\include\adapt_struct.hpp>

namespace VRMLDoc
{
	using namespace std;

	enum class TGeometryType
	{
		geoBox,
		geoCone,
		geoCylinder,
		geoElevationGrid,
		geoExtrusion,
		geoIndexedFaceSet,
		geoIndexedLineSet,
		geoPointSet,
		geoSphere,
	};

	struct TPoint
	{
		double x;
		double y;
		double z;

		TPoint() : x(0.0), y(0.0), z(0.0) {}
	};

	struct TCoordIndex
	{
		int x;
		int y;
		int z;

		TCoordIndex() : x(0), y(0), z(0) {}
	};

	struct TGeometry
	{
		std::string         geometryType;
		vector<TPoint>      points;
		vector<TCoordIndex> indexes;
	};	
}

BOOST_FUSION_ADAPT_STRUCT(VRMLDoc::TPoint, x, y, z)
BOOST_FUSION_ADAPT_STRUCT(VRMLDoc::TCoordIndex, x, y, z)
BOOST_FUSION_ADAPT_STRUCT(VRMLDoc::TGeometry, geometryType, points, indexes)
