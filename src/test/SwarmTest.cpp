#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include "../Swarm.h"

using namespace MetaOpt;

TEST_CASE( "Swarm Setyp", "[Swarm.Swarm]" ) {
    Eigen::ArrayXd upper(3), lower(3);
    lower << 0.0, 0.0, 0.0;
    upper << 1.0, 1.0, 1.0;
    auto bounds = std::make_pair(lower, upper);

    REQUIRE_NOTHROW( Swarm sw(10, bounds) );
}
