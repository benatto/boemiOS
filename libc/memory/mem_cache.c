/*
    This file is part of BoemioS.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BoemiOS.  If not, see <http://www.gnu.org/licenses/>.

Authors:
	- Marco A Benatto <marco.antonio.780@gmail.com>

*/



#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <kernel/pagealloc.h>

#include <memory/memtypes.h>
#include <memory/mem_cache.h>
#include <lib/bitops.h>


void *mem_cache_create(char *name, size_t len) {
	void *ret = NULL;

	return ret;
}

static int malloc_init() {
	/* We start with just one page */
	mdata.current_page = get_page(PAGE_SIZE);

	if (!mdata.current_page) {
		printf("Could not init malloc...\n");
		set_bit(&mdata.flags, MALLOC_INITIALIZED);
		clear_bit(&mdata.flags, MALLOC_HAS_SPACE);

		return -1;
	}

	set_bit(&mdata.flags, MALLOC_INITIALIZED);
	set_bit(&mdata.flags, MALLOC_VALID);
	set_bit(&mdata.flags, MALLOC_HAS_SPACE);

	mdata.num_pages++;
	mdata.offset = sizeof(malloc_data_t);

	/* TODO: init page lists here */
	return 0;
}

void *malloc(size_t size) {
	void *ret;

	ret = NULL;

	if (!test_bit(&mdata.flags, MALLOC_INITIALIZED)) {
		if (malloc_init())
			goto out;
	}

	if (!(test_bit(&mdata.flags, MALLOC_HAS_SPACE)) ||
		((mdata.num_pages * PAGE_SIZE) < mdata.offset + size)) {
		/* TODO: if we don't fit the allocation on current memory
 		 * poll we need to alloc more*/
		printf("ran out of memory, alloc more will be implemented soon\n");
		printf("flags: %d, len: %lu, offset: %d, page: 0x%x, addr: 0x%x\n", mdata.flags,
									size, mdata.offset, (unsigned int)mdata.current_page,
										(unsigned int)(mdata.current_page + mdata.offset));

		clear_bit(&mdata.flags, MALLOC_HAS_SPACE);
		goto out;
	}

	ret = mdata.current_page + mdata.offset;
	mdata.offset += size;
out:
	return ret;
}
