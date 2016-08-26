#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include "../types.h"
#include "../Swarm.h"
#include "../functions.h"
#include "../arrayhelpers.h"

using namespace MetaOpt;

TEST_CASE( "Swarm Setup", "[Swarm.Swarm]" ) {
    auto bounds = makeBounds(3, 1, 5);
    REQUIRE_NOTHROW( Swarm sw(10, bounds, 50) );
}

TEST_CASE ( "Swarm Optimize", "[Swarm.Optimize]" ) {
    auto bounds = makeBounds(3, 1, 5);
    Swarm sw(10, bounds, 50);

    CostFunction func = rosen;
    REQUIRE_NOTHROW( sw.optimize(func) );
    auto solution = sw.getBestSolution();

    REQUIRE( func(solution) == Approx( 181.646 ).epsilon( 0.001 ) );
    REQUIRE( solution(0) == Approx( 1.805 ).epsilon( 0.001 ) );
    REQUIRE( solution(1) == Approx( 1.960 ).epsilon( 0.001 ));
    REQUIRE( solution(2) == Approx( 3.503 ).epsilon( 0.001 ));
}
