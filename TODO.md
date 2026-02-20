# TODO

## LinkedList — Memory Management

`_add` retains the stored object and `_dealloc` releases all of them, but the
strategy is not fully consistent:

- **`_delete` ownership is ambiguous.** When an object is removed and returned
  to the caller, it still carries the retain that `_add` acquired. The caller
  is implicitly responsible for releasing it, but nothing enforces or documents
  this contract. Options:
    - Release inside `_delete` and let the caller retain if they want to keep
      the object (safer, explicit).
    - Document the transfer-of-ownership convention so callers know they must
      release the returned value.

- **Node allocation bypasses the pool.** `struct Node_c` nodes are allocated
  with plain `malloc` / `free` instead of `D_mm_alloc` / `D_mm_pool_add`.
  This means they live outside the managed memory pool and won't participate
  in pool-level diagnostics or cleanup.