#include <gtest/gtest.h>

#include <cslib/algorithm/hash/jenkins.hpp>

TEST(hash_jenkins, integer)
{
	ASSERT_EQ(cslib::algorithm::jenkins_hash(5), cslib::algorithm::jenkins_hash(5));
}
