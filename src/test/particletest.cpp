#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include "../Particle.h"
#include <stdlib.h>

using namespace MetaOpt;

TEST_CASE( "Particle Init", "[Particle]" ) {
    // seed the random number generator for Eigen
    srand(50);

    Eigen::ArrayXd upper(3), lower(3);
    lower << 1.0, 1.0, 1.0;
    upper << 5.0, 5.0, 5.0;
    auto bounds = std::make_pair(lower, upper);

    Particle p(bounds);
    Eigen::ArrayXd pos = p.getPosition();
    Eigen::ArrayXd bstPos = p.getBestPosition();
    Eigen::ArrayXd vel = p.getVelocity();

    REQUIRE( pos(0) == Approx( 1.003 ).epsilon( 0.001 ) );
    REQUIRE( pos(1) == Approx( 3.307 ).epsilon( 0.001 ));
    REQUIRE( pos(2) == Approx( 4.121 ).epsilon( 0.001 ));

    REQUIRE( bstPos(0) == Approx( 1.003 ).epsilon( 0.001 ) );
    REQUIRE( bstPos(1) == Approx( 3.307 ).epsilon( 0.001 ));
    REQUIRE( bstPos(2) == Approx( 4.121 ).epsilon( 0.001 ));

    REQUIRE( vel(0) == Approx( 0.365 ).epsilon( 0.001 ) );
    REQUIRE( vel(1) == Approx( -0.223 ).epsilon( 0.001 ));
    REQUIRE( vel(2) == Approx( 0.395 ).epsilon( 0.001 ));
}
