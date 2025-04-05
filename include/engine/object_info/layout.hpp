#ifndef __LAYOUT_HPP__
# define __LAYOUT_HPP__ 1

# include <vector>
# include <stddef.h>

class Layout
{
	public:
		struct Format
		{
			public:
				size_t			count;
				unsigned int	type;
				unsigned int	size;
				unsigned int	normalize;
		};

	public:
		std::vector<Layout::Format> format_list;
		size_t						stride;

	public:
		Layout();
		virtual ~Layout();

	public:
		void add_layout(size_t count, unsigned int type, unsigned int size, unsigned int normalize);
		void clear();
};

#endif /* __LAYOUT_HPP__ */