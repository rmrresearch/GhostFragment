#include "ghostfragment/type_traits.hpp"
#include <catch2/catch.hpp>

using namespace ghostfragment;

using type_list = std::tuple<int, double, float, std::string>;

TEMPLATE_LIST_TEST_CASE("IsPartition", "", type_list) {
    using T =TestType;

    SECTION("Not a partition"){
        STATIC_REQUIRE_FALSE(detail_::IsPartition<T>::value); }
    SECTION("Is a partition") {
        STATIC_REQUIRE(detail_::IsPartition<type::partition<T>>::value);
    }
}

TEMPLATE_LIST_TEST_CASE("is_partition_v", "", type_list) {
    using T =TestType;

    SECTION("Not a partition"){
        STATIC_REQUIRE_FALSE(is_partition_v<T>); }
    SECTION("Is a partition") {
        STATIC_REQUIRE(is_partition_v<type::partition<T>>);
    }
}

TEMPLATE_LIST_TEST_CASE("PartitionedObject", "", type_list) {
    using T =TestType;
    SECTION("Not a partition"){
        using obj  = typename detail_::PartitionedObject<T, false>::type;
        using corr = T;
        STATIC_REQUIRE(std::is_same_v<obj, corr>);
    }
    SECTION("Is a partition"){
        using partition = type::partition<T>;
        using obj  = typename detail_::PartitionedObject<partition, true>::type;
        using corr = T;
        STATIC_REQUIRE(std::is_same_v<obj, corr>);
    }
}

TEMPLATE_LIST_TEST_CASE("partitioned_object_t", "", type_list) {
    using T =TestType;
    SECTION("Not a partition"){
        using obj  = partitioned_object_t<T>;
        using corr = T;
        STATIC_REQUIRE(std::is_same_v<obj, corr>);
    }
    SECTION("Is a partition"){
        using obj  = partitioned_object_t<type::partition<T>>;
        using corr = T;
        STATIC_REQUIRE(std::is_same_v<obj, corr>);
    }
}
