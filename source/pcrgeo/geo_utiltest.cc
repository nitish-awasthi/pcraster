#ifndef INCLUDED_STDDEFX
#include "stddefx.h"
#define INCLUDED_STDDEFX
#endif

#ifndef INCLUDED_GEO_UTILTEST
#include "geo_utiltest.h"
#define INCLUDED_GEO_UTILTEST
#endif

// Library headers.
#ifndef INCLUDED_BOOST_SHARED_PTR
#include <boost/shared_ptr.hpp>
#define INCLUDED_BOOST_SHARED_PTR
#endif

#ifndef INCLUDED_BOOST_TEST_TEST_TOOLS
#include <boost/test/test_tools.hpp>
#define INCLUDED_BOOST_TEST_TEST_TOOLS
#endif

#ifndef INCLUDED_BOOST_TEST_UNIT_TEST_SUITE
#include <boost/test/unit_test_suite.hpp>
#define INCLUDED_BOOST_TEST_UNIT_TEST_SUITE
#endif

// PCRaster library headers.
#ifndef INCLUDED_COM_MATH
#include "com_math.h"
#define INCLUDED_COM_MATH
#endif

// Module headers.
#ifndef INCLUDED_GEO_RASTERBOUNDARIES
#include "geo_rasterboundaries.h"
#define INCLUDED_GEO_RASTERBOUNDARIES
#endif

#ifndef INCLUDED_GEO_SIMPLERASTER
#include "geo_simpleraster.h"
#define INCLUDED_GEO_SIMPLERASTER
#endif

#ifndef INCLUDED_GEO_UTIL
#include "geo_util.h"
#define INCLUDED_GEO_UTIL
#endif



/*!
  \file
  This file contains the implementation of the UtilTest class.
*/



//------------------------------------------------------------------------------
// DEFINITION OF STATIC UTIL MEMBERS
//------------------------------------------------------------------------------

//! suite
boost::unit_test::test_suite*geo::UtilTest::suite()
{
  boost::unit_test::test_suite* suite = BOOST_TEST_SUITE(__FILE__);
  boost::shared_ptr<UtilTest> instance(new UtilTest());

  suite->add(BOOST_CLASS_TEST_CASE(&UtilTest::testRaster2Boundaries, instance));
  suite->add(BOOST_CLASS_TEST_CASE(&UtilTest::testMagnitude, instance));

  return suite;
}



//------------------------------------------------------------------------------
// DEFINITION OF UTIL MEMBERS
//------------------------------------------------------------------------------

//! ctor
geo::UtilTest::UtilTest()
{
}



//! setUp
void geo::UtilTest::setUp()
{
}

//! tearDown
void geo::UtilTest::tearDown()
{
}



void geo::UtilTest::testRaster2Boundaries()
{
  {
    // Create raster:
    // 1 2 3
    // 4 5 6
    // 7 8 9
    SimpleRaster<double> raster(3, 3);
    raster.cell(0, 0) = 1.0;
    raster.cell(0, 1) = 2.0;
    raster.cell(0, 2) = 3.0;
    raster.cell(1, 0) = 4.0;
    raster.cell(1, 1) = 5.0;
    raster.cell(1, 2) = 6.0;
    raster.cell(2, 0) = 7.0;
    raster.cell(2, 1) = 8.0;
    raster.cell(2, 2) = 9.0;

    // Create RasterBoundaries object.
    RasterBoundaries<double> boundaries(3, 3);

    // Convert to boundary values.
    raster2Boundaries(raster, boundaries);

    // Test.
    // Vertical boundaries.
    BOOST_CHECK(boundaries.leftBoundary(0, 0) == 1.0);
    BOOST_CHECK(boundaries.rightBoundary(0, 0) == 1.5);
    BOOST_CHECK(boundaries.rightBoundary(0, 1) == 2.5);
    BOOST_CHECK(boundaries.rightBoundary(0, 2) == 3.0);
    BOOST_CHECK(boundaries.leftBoundary(1, 0) == 4.0);
    BOOST_CHECK(boundaries.rightBoundary(1, 0) == 4.5);
    BOOST_CHECK(boundaries.rightBoundary(1, 1) == 5.5);
    BOOST_CHECK(boundaries.rightBoundary(1, 2) == 6.0);
    BOOST_CHECK(boundaries.leftBoundary(2, 0) == 7.0);
    BOOST_CHECK(boundaries.rightBoundary(2, 0) == 7.5);
    BOOST_CHECK(boundaries.rightBoundary(2, 1) == 8.5);
    BOOST_CHECK(boundaries.rightBoundary(2, 2) == 9.0);

    // Horizontal boundaries.
    BOOST_CHECK(boundaries.topBoundary(0, 0) == 1.0);
    BOOST_CHECK(boundaries.topBoundary(0, 1) == 2.0);
    BOOST_CHECK(boundaries.topBoundary(0, 2) == 3.0);
    BOOST_CHECK(boundaries.bottomBoundary(0, 0) == 2.5);
    BOOST_CHECK(boundaries.bottomBoundary(0, 1) == 3.5);
    BOOST_CHECK(boundaries.bottomBoundary(0, 2) == 4.5);
    BOOST_CHECK(boundaries.bottomBoundary(1, 0) == 5.5);
    BOOST_CHECK(boundaries.bottomBoundary(1, 1) == 6.5);
    BOOST_CHECK(boundaries.bottomBoundary(1, 2) == 7.5);
    BOOST_CHECK(boundaries.bottomBoundary(2, 0) == 7.0);
    BOOST_CHECK(boundaries.bottomBoundary(2, 1) == 8.0);
    BOOST_CHECK(boundaries.bottomBoundary(2, 2) == 9.0);
  }

  {
    // Create raster:
    // 1  2 3
    // 4 MV 6
    // 7  8 9
    SimpleRaster<double> raster(3, 3);
    raster.cell(0, 0) = 1.0;
    raster.cell(0, 1) = 2.0;
    raster.cell(0, 2) = 3.0;
    raster.cell(1, 0) = 4.0;
    pcr::setMV(raster.cell(1, 1));
    raster.cell(1, 2) = 6.0;
    raster.cell(2, 0) = 7.0;
    raster.cell(2, 1) = 8.0;
    raster.cell(2, 2) = 9.0;

    // Create RasterBoundaries object.
    RasterBoundaries<double> boundaries(3, 3);

    // Convert to boundary values.
    raster2Boundaries(raster, boundaries);

    // Test.
    // Vertical boundaries.
    BOOST_CHECK(boundaries.leftBoundary(0, 0) == 1.0);
    BOOST_CHECK(boundaries.rightBoundary(0, 0) == 1.5);
    BOOST_CHECK(boundaries.rightBoundary(0, 1) == 2.5);
    BOOST_CHECK(boundaries.rightBoundary(0, 2) == 3.0);

    BOOST_CHECK(boundaries.leftBoundary(1, 0) == 4.0);
    BOOST_CHECK(boundaries.rightBoundary(1, 0) == 4.0);
    BOOST_CHECK(boundaries.rightBoundary(1, 1) == 6.0);
    BOOST_CHECK(boundaries.rightBoundary(1, 2) == 6.0);
    BOOST_CHECK(boundaries.leftBoundary(2, 0) == 7.0);
    BOOST_CHECK(boundaries.rightBoundary(2, 0) == 7.5);
    BOOST_CHECK(boundaries.rightBoundary(2, 1) == 8.5);
    BOOST_CHECK(boundaries.rightBoundary(2, 2) == 9.0);

    // Horizontal boundaries.
    BOOST_CHECK(boundaries.topBoundary(0, 0) == 1.0);
    BOOST_CHECK(boundaries.topBoundary(0, 1) == 2.0);
    BOOST_CHECK(boundaries.topBoundary(0, 2) == 3.0);
    BOOST_CHECK(boundaries.bottomBoundary(0, 0) == 2.5);
    BOOST_CHECK(boundaries.bottomBoundary(0, 1) == 2.0);
    BOOST_CHECK(boundaries.bottomBoundary(0, 2) == 4.5);

    BOOST_CHECK(boundaries.bottomBoundary(1, 0) == 5.5);
    BOOST_CHECK(boundaries.bottomBoundary(1, 1) == 8.0);
    BOOST_CHECK(boundaries.bottomBoundary(1, 2) == 7.5);

    BOOST_CHECK(boundaries.bottomBoundary(2, 0) == 7.0);
    BOOST_CHECK(boundaries.bottomBoundary(2, 1) == 8.0);
    BOOST_CHECK(boundaries.bottomBoundary(2, 2) == 9.0);
  }

  {
    // Create raster:
    // MV MV MV
    // MV MV  6
    // MV MV MV
    SimpleRaster<double> raster(3, 3);
    pcr::setMV(raster.cell(0, 0));
    pcr::setMV(raster.cell(0, 1));
    pcr::setMV(raster.cell(0, 2));
    pcr::setMV(raster.cell(1, 0));
    pcr::setMV(raster.cell(1, 1));
    raster.cell(1, 2) = 6.0;
    pcr::setMV(raster.cell(2, 0));
    pcr::setMV(raster.cell(2, 1));
    pcr::setMV(raster.cell(2, 2));

    // Create RasterBoundaries object.
    RasterBoundaries<double> boundaries(3, 3);

    // Convert to boundary values.
    raster2Boundaries(raster, boundaries);

    // Test.
    // Vertical boundaries.
    BOOST_CHECK(pcr::isMV(boundaries.leftBoundary(0, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.rightBoundary(0, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.rightBoundary(0, 1)));
    BOOST_CHECK(pcr::isMV(boundaries.rightBoundary(0, 2)));

    BOOST_CHECK(pcr::isMV(boundaries.leftBoundary(1, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.rightBoundary(1, 0)));
    BOOST_CHECK(boundaries.rightBoundary(1, 1) == 6.0);
    BOOST_CHECK(boundaries.leftBoundary(1, 2) == 6.0);
    BOOST_CHECK(boundaries.rightBoundary(1, 2) == 6.0);

    BOOST_CHECK(pcr::isMV(boundaries.leftBoundary(2, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.rightBoundary(2, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.rightBoundary(2, 1)));
    BOOST_CHECK(pcr::isMV(boundaries.rightBoundary(2, 2)));

    // Horizontal boundaries.
    BOOST_CHECK(pcr::isMV(boundaries.topBoundary(0, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.topBoundary(0, 1)));
    BOOST_CHECK(pcr::isMV(boundaries.topBoundary(0, 2)));

    BOOST_CHECK(pcr::isMV(boundaries.bottomBoundary(0, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.bottomBoundary(0, 1)));
    BOOST_CHECK(boundaries.bottomBoundary(0, 2) == 6.0);

    BOOST_CHECK(pcr::isMV(boundaries.bottomBoundary(1, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.bottomBoundary(1, 1)));
    BOOST_CHECK(boundaries.topBoundary(1, 2) == 6.0);
    BOOST_CHECK(boundaries.bottomBoundary(1, 2) == 6.0);

    BOOST_CHECK(pcr::isMV(boundaries.bottomBoundary(2, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.bottomBoundary(2, 1)));
    BOOST_CHECK(pcr::isMV(boundaries.bottomBoundary(2, 2)));

    BOOST_CHECK(pcr::isMV(boundaries.topBoundary(2, 0)));
    BOOST_CHECK(pcr::isMV(boundaries.topBoundary(2, 1)));
    BOOST_CHECK(boundaries.topBoundary(2, 2) == 6.0);
  }
}



void geo::UtilTest::testMagnitude()
{
  RasterBoundaries<double> velocity(3, 3);

  velocity.leftBoundary(0, 0) = 1.0;
  velocity.leftBoundary(1, 0) = 3.0;
  velocity.leftBoundary(2, 0) = 4.0;
  velocity.rightBoundary(0, 0) = 3.0;
  velocity.rightBoundary(0, 1) = 4.0;
  velocity.rightBoundary(0, 2) = 1.0;
  velocity.rightBoundary(1, 0) = 4.0;
  velocity.rightBoundary(1, 1) = 1.0;
  velocity.rightBoundary(1, 2) = 3.0;
  velocity.rightBoundary(2, 0) = 1.0;
  velocity.rightBoundary(2, 1) = 3.0;
  velocity.rightBoundary(2, 2) = 4.0;

  velocity.topBoundary(0, 0) = 1.0;
  velocity.topBoundary(0, 1) = 3.0;
  velocity.topBoundary(0, 2) = 4.0;
  velocity.bottomBoundary(0, 0) = 3.0;
  velocity.bottomBoundary(0, 1) = 4.0;
  velocity.bottomBoundary(0, 2) = 1.0;
  velocity.bottomBoundary(1, 0) = 4.0;
  velocity.bottomBoundary(1, 1) = 1.0;
  velocity.bottomBoundary(1, 2) = 3.0;
  velocity.bottomBoundary(2, 0) = 1.0;
  velocity.bottomBoundary(2, 1) = 3.0;
  velocity.bottomBoundary(2, 2) = 4.0;

  RasterBoundaries<double> magnitude(3, 3);
  geo::magnitude(velocity, velocity, magnitude);

  // Vertical boundaries.
  BOOST_CHECK(com::equal_epsilon(magnitude.leftBoundary(0, 0),  std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.leftBoundary(1, 0),  std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.leftBoundary(2, 0),  std::sqrt(32.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(0, 0), std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(0, 1), std::sqrt(32.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(0, 2), std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(1, 0), std::sqrt(32.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(1, 1), std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(1, 2), std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(2, 0), std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(2, 1), std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.rightBoundary(2, 2), std::sqrt(32.0)));

  // Horizontal boundaries.
  BOOST_CHECK(com::equal_epsilon(magnitude.topBoundary(0, 0), std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.topBoundary(0, 1), std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.topBoundary(0, 2), std::sqrt(32.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(0, 0), std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(0, 1), std::sqrt(32.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(0, 2), std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(1, 0), std::sqrt(32.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(1, 1), std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(1, 2), std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(2, 0), std::sqrt( 2.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(2, 1), std::sqrt(18.0)));
  BOOST_CHECK(com::equal_epsilon(magnitude.bottomBoundary(2, 2), std::sqrt(32.0)));
}
