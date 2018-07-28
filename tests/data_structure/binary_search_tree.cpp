#include <gtest/gtest.h>

#include <cslib/data_structure/tree/binary_search_tree.hpp>

#include <vector>

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


TEST(binary_search_tree, deletion)
{
	cslib::data_structure::binary_search_tree<int, int> container;

	container.insert(5, 10);
	container.insert(3, 20);
	container.insert(10, 30);
	container.insert(9, 40);
	container.insert(20, 50);
	container.insert(19, 60);

	// deletion case 0: zero child
	container.remove(3);
	ASSERT_EQ(container.at(5), 10);

	// deletion case 1: one child
	container.remove(20);
	ASSERT_EQ(container.at(19), 60);

	// deletion case 2: two child
	container.remove(10);
	ASSERT_EQ(container.at(9), 40);
	ASSERT_EQ(container.at(19), 60);
}


TEST(binary_search_tree, access)
{
	cslib::data_structure::binary_search_tree<int, int> container;

	container.insert(5, 5);
	ASSERT_EQ(container.at(5), 5);
	container.insert(5, 6);
	ASSERT_EQ(container.at(5), 6);
}


TEST(binary_search_tree, inorder_traverse)
{
	cslib::data_structure::binary_search_tree<int, int> container;

	container.insert(5, 20);
	container.insert(3, 30);
	container.insert(9, 20);
	container.insert(6, 30);

	std::vector<int> test_vector;
	for (auto iter = container.begin(); iter != container.end(); iter++)
		test_vector.push_back((*iter).first);

	EXPECT_TRUE(test_vector == std::vector<int>({ 3, 5, 6, 9 }));
}
