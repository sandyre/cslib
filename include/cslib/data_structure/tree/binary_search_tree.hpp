#ifndef CSLIB_DATA_STRUCTURE_TREE_BINARY_SEARCH_TREE_HPP
#define CSLIB_DATA_STRUCTURE_TREE_BINARY_SEARCH_TREE_HPP

namespace cslib {
namespace data_structure
{

	/* Name: Binary search tree
	 * Runtime operations complexity:
	 * - Access: O(log(n))
	 * - Search: O(log(n))
	 * - Insertion: O(log(n))
	 * - Deletion: O(log(n))
	 *
	 * Space complexity: O(n)
	 *
	 * Interesting fact: this is implementation of not self-balancing tree.
	 *
	 * TODO: implement
	 */

	template < typename KeyT, typename ValueT >
	class binary_search_tree
	{
	public:
		using value_type			= ValueT;
		using key_type				= KeyT;
		using pointer				= ValueT*;
		using const_pointer			= const ValueT*;
		using reference				= ValueT&;

	private:
		using KeyPassingT	= typename std::conditional<std::is_fundamental<KeyT>::value, KeyT, const KeyT&>::type;
		using ValuePassingT	= typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type;

		struct binary_tree_node
		{
			KeyT	Key;
			ValueT	Value;
		};

	private:
		binary_tree_node*	_root;

	public:
		reference at(KeyPassingT key);
		void insert(KeyPassingT key, ValuePassingT value);
		void remove(KeyPassingT key);
	};

}}

#endif
