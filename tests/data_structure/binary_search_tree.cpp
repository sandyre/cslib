#include <gtest/gtest.h>

#include <cslib/data_structure/tree/binary_search_tree.hpp>

TEST(binary_search_tree, empty_construction)
{
	cslib::data_structure::binary_search_tree<int, int> container;
}


TEST(binary_search_tree, insertion)
{
	cslib::data_structure::binary_search_tree<int, int> container;

	container.insert(5, 5);
	container.insert(5, 5);
}


TEST(binary_search_tree, access)
{
	cslib::data_structure::binary_search_tree<int, int> container;

	container.insert(5, 5);
	ASSERT_EQ(container.at(5), 5);
	container.insert(5, 6);
	ASSERT_EQ(container.at(5), 6);
}
