


/*
 * Only zone implementors should depend on the layout of this structure;
 * Regular callers should use the access functions below
 */
typedef struct _malloc_zone_t {
	void *reserved1;	/* RESERVED FOR CFAllocator DO NOT USE */
	void *reserved2;	/* RESERVED FOR CFAllocator DO NOT USE */

    //functions
	size_t (* MALLOC_ZONE_FN_PTR(size))(struct _malloc_zone_t *zone, const void * __unsafe_indexable ptr);
	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(malloc))(struct _malloc_zone_t *zone, size_t size);
	void * __sized_by_or_null(num_items * size) (* MALLOC_ZONE_FN_PTR(calloc))(struct _malloc_zone_t *zone, size_t num_items, size_t size); //initializes to zero
	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(valloc))( struct _malloc_zone_t *zone, size_t size);  //guaranteed to be page-aligned
	void (* MALLOC_ZONE_FN_PTR(free))(struct _malloc_zone_t *zone, void * __unsafe_indexable ptr);
	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(realloc))(struct _malloc_zone_t *zone, void * __unsafe_indexable ptr, size_t size);
	void (* MALLOC_ZONE_FN_PTR(destroy))(struct _malloc_zone_t *zone);

	const char * __null_terminated zone_name;

	/* Optional batch callbacks; these may be NULL */
	unsigned (* MALLOC_ZONE_FN_PTR(batch_malloc))(struct _malloc_zone_t *zone, size_t size, void * __unsafe_indexable * __counted_by(num_requested) results, unsigned num_requested);
	void (* MALLOC_ZONE_FN_PTR(batch_free))(struct _malloc_zone_t *zone, void * __unsafe_indexable * __counted_by(num_to_be_freed) to_be_freed, unsigned num_to_be_freed);

	struct malloc_introspection_t * MALLOC_INTROSPECT_TBL_PTR(introspect);
	unsigned version;

	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(memalign))(struct _malloc_zone_t *zone, size_t alignment, size_t size);
	void (* MALLOC_ZONE_FN_PTR(free_definite_size))(struct _malloc_zone_t *zone, void * __sized_by(size) ptr, size_t size);
	size_t (* MALLOC_ZONE_FN_PTR(pressure_relief))(struct _malloc_zone_t *zone, size_t goal);
	boolean_t (* MALLOC_ZONE_FN_PTR(claimed_address))(struct _malloc_zone_t *zone, void * __unsafe_indexable ptr);
	void (* MALLOC_ZONE_FN_PTR(try_free_default))(struct _malloc_zone_t *zone, void * __unsafe_indexable ptr);
	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(malloc_with_options))(struct _malloc_zone_t *zone, size_t align, size_t size, uint64_t options);


	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(malloc_type_malloc))(struct _malloc_zone_t *zone, size_t size, malloc_type_id_t type_id);
	void * __sized_by_or_null(count * size) (* MALLOC_ZONE_FN_PTR(malloc_type_calloc))(struct _malloc_zone_t *zone, size_t count, size_t size, malloc_type_id_t type_id);
	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(malloc_type_realloc))(struct _malloc_zone_t *zone, void * __unsafe_indexable ptr,size_t size, malloc_type_id_t type_id);
	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(malloc_type_memalign))(struct _malloc_zone_t *zone, size_t alignment, size_t size, malloc_type_id_t type_id);
	void * __sized_by_or_null(size) (* MALLOC_ZONE_FN_PTR(malloc_type_malloc_with_options))(struct _malloc_zone_t *zone, size_t align, size_t size, uint64_t options, malloc_type_id_t type_id);
} malloc_zone_t;


typedef struct szone_s {	  // vm_allocate()'d, so page-aligned to begin with.
	malloc_zone_t basic_zone; // first page will be given read-only protection
	uint8_t pad[PAGE_MAX_SIZE - sizeof(malloc_zone_t)];

	unsigned long cpu_id_key; // unused
	// remainder of structure is R/W (contains no function pointers)
	unsigned debug_flags;
	void *log_address;

	/* Allocation racks per allocator type. */
	struct rack_s tiny_rack;
	struct rack_s small_rack;
	struct rack_s medium_rack;

	/* large objects: all the rest */
	_malloc_lock_s large_szone_lock MALLOC_CACHE_ALIGN; // One customer at a time for large
	unsigned num_large_objects_in_use;
	unsigned num_large_entries;
	large_entry_t *large_entries; // hashed by location; null entries don't count
	size_t num_bytes_in_large_objects;

#if CONFIG_LARGE_CACHE
	int large_entry_cache_oldest;
	int large_entry_cache_newest;
	large_entry_t large_entry_cache[LARGE_ENTRY_CACHE_SIZE_HIGH]; // "death row" for large malloc/free
	int large_cache_depth;
	size_t large_cache_entry_limit;
	boolean_t large_legacy_reset_mprotect;
	size_t large_entry_cache_reserve_bytes;
	size_t large_entry_cache_reserve_limit;
	size_t large_entry_cache_bytes; // total size of death row, bytes
#endif
	bool is_medium_engaged;
	uintptr_t cookie;
	struct szone_s *helper_zone;
	boolean_t flotsam_enabled;
} szone_t;


typedef struct tiny_region {
	// This must be first (because TINY_REGION_METADATA assumes it).
	region_trailer_t trailer;

	// The interleaved bit arrays comprising the header and inuse bitfields.
	// The unused bits of each component in the last pair will be initialized to sentinel values.
	tiny_header_inuse_pair_t pairs[CEIL_NUM_TINY_BLOCKS_WORDS];

	// Indices of the first and last free block in this region. Value is the
	// block index + 1 so that 0 indicates no free block in this region for the
	// corresponding slot.
	region_free_blocks_t free_blocks_by_slot[NUM_TINY_SLOTS];

	uint8_t pad[TINY_REGION_PAD];

	// Intended to catch backward overspills from the heap into this structure.
	region_cookie_t region_cookie;

	tiny_block_t blocks[NUM_TINY_BLOCKS];
} * tiny_region_t;