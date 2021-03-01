#include <gtest/gtest.h>

#include <cslib/data_structure/tensor.hpp>

TEST(Tensor, construction)
{
	cslib::data_structure::Tensor<int> tensor({5, 3});

	ASSERT_EQ(tensor.size(), 15);
	ASSERT_EQ(container.shape(), std::vector<size_t>({5, 3}));
}


TEST(Tensor, tensor_slicing)
{
	cslib::data_structure::Tensor<int> tensor({5, 3});
    cslib::data_structure::Tensor<int> sub_tensor = tensor[2];

	ASSERT_EQ(sub_tensor.size(), 3);
	ASSERT_EQ(sub_tensor.shape(), std::vector<size_t>({3}));
}


TEST(Tensor, constant_addition)
{
	cslib::data_structure::Tensor<int> tensor({5, 3});
    tensor[2] = 1;
    tensor[3] = tensor[2] + 2;

	ASSERT_EQ(tensor[3][0], 3);
    ASSERT_EQ(tensor[3][1], 3);
    ASSERT_EQ(tensor[3][2], 3);
}
