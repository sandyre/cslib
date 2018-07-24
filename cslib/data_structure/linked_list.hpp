#ifndef CSLIB_DATA_STRUCTURE_LINKED_LIST_HPP
#define CSLIB_DATA_STRUCTURE_LINKED_LIST_HPP

#include <algorithm>

namespace cslib {
namespace data_structure
{

	/* Name: Singly linked list
	 *
	 * TODO:
	 * 1. operations complexity
	 */

	template < typename ValueT >
	class singly_linked_list
	{
		using PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type;

	private:
		struct list_node
		{
			ValueT		Value;
			list_node*	Next;

		public:
			list_node(PassingValueT value, list_node* next = std::nullptr)
				:	Value(value),
					Next(next)
			{ }
		};

	private:
		list_node*		_root;

	public:
		singly_linked_list()
			:	_root(std::nullptr),
				_size()
		{ }

		~singly_linked_list()
		{ clear(); }

		void push_front(PassingValueT value)
		{ _root = new list_node(value, _root); }

		void pop_front()
		{
			if (!_root)
				return;

			list_node* newRoot = _root->Next;
			delete _root;
			_root = newRoot;
		}

		/* void erase_after(iterator); */
		/* void insert_after(iterator); */
		/* void swap(iterator, iterator); */

		void clear()
		{
			while (_root)
				pop_front();
		}
	};

}}

#endif
