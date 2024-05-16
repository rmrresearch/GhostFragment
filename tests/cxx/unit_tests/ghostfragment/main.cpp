#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <parallelzone/parallelzone.hpp>

int main(int argc, char* argv[]) {
    auto rt = parallelzone::runtime::RuntimeView(argc, argv);

    int res = Catch::Session().run(argc, argv);

    return res;
}
