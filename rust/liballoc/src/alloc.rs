
pub use ::core::alloc::*;
use core::ptr::NonNull;

#[lang = "global_alloc"]
pub unsafe trait GlobalAlloc{
    unsafe fn alloc(&self,layout: Layout) -> *mut u8;
    unsafe fn dealloc(&self,ptr: *mut u8,layout: Layout);
    unsafe fn alloc_zeroed(&self,layout: Layout) -> *mut u8{
        let bytes = self.alloc(layout);
        ::__lccc::builtins::C::__builtin_memset(bytes,0,layout.size());
        bytes
    }

    unsafe fn realloc(&self,ptr: *mut u8,layout: Layout,mut new_size: usize) -> *mut u8{
        let align = layout.align();
        new_size += (align-(new_size%align))%align;
        let n_layout = Layout::from_size_align_unchecked(new_size,align);
        let ret = self.alloc(n_layout);
        if ret.is_null(){
            core::ptr::null_mut()
        }else{
            core::ptr::copy_nonoverlapping(ptr,ret,layout.size().min(new_size));
            self.dealloc(ptr,layout);
            ret
        }
    }
}

#[unstable(feature="allocator_api",issue="32838")]
pub struct AllocError;

#[unstable(feature="allocator_api",issue="32838")]
pub unsafe trait AllocRef{
    fn alloc(&self,layout: Layout) -> Result<NonNull<[u8]>,AllocError>;
    unsafe fn dealloc(&self,ptr: NonNull<u8>,layout: Layout);

    fn alloc_zeroed(&self,layout: Layout) -> Result<NonNull<[u8]>,AllocError>{
        let block = self.alloc(layout)?;
        ::__lccc::builtins::C::__builtin_memset(bytes.as_ptr() as *mut u8,0,layout.size());
        Ok(block)
    }

    unsafe fn grow(&self,ptr: NonNull<u8>,old_layout: Layout,new_layout: Layout) -> Result<NonNull<[u8]>,AllocError>{
        let block = self.alloc(new_layout)?;
        core::ptr::copy_nonoverlapping(ptr.as_ptr(),block.as_ptr() as *mut u8,old_layout.size());
        self.dealloc(ptr,old_layout);
        Ok(block)
    }

    unsafe fn grow_zeroed(&self,ptr: NonNull<u8>,old_layout: Layout,new_layout: Layout) -> Result<NonNull<[u8]>,AllocError>{
        let block = self.alloc_zeroed(new_layout)?;
        core::ptr::copy_nonoverlapping(ptr.as_ptr(),block.as_ptr() as *mut u8,old_layout.size());
        self.dealloc(ptr,old_layout);
        Ok(block)
    }

    unsafe fn shrink(&self,ptr: NonNull<u8>,old_layout: Layout,new_layout: Layout) -> Result<NonNull<[u8]>,AllocError>{
        let block = self.alloc(new_layout)?;
        core::ptr::copy_nonoverlapping(ptr.as_ptr(),block.as_ptr() as *mut u8,new_layout.size());
        self.dealloc(ptr,old_layout);
        Ok(block)
    }

    fn by_ref(&self) -> &Self{
        self
    }
}

unsafe impl<A: AllocRef> AllocRef for &'_ A{
    fn alloc(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        (*self).alloc(layout)
    }

    unsafe fn dealloc(&self, ptr: NonNull<u8>, layout: Layout) {
        (*self).dealloc(ptr,layout)
    }

    fn alloc_zeroed(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        (*self).alloc_zeroed(layout)
    }

    unsafe fn grow(&self, ptr: NonNull<u8>, old_layout: Layout, new_layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        (*self).grow(ptr,old_layout,new_layout)
    }

    unsafe fn grow_zeroed(&self, ptr: NonNull<u8>, old_layout: Layout, new_layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        (*self).grow_zeroed(ptr,old_layout,new_layout)
    }

    unsafe fn shrink(&self, ptr: NonNull<u8>, old_layout: Layout, new_layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        (*self).shrink(ptr,old_layout,new_layout)
    }
}

extern"Rust"{
    #[no_mangle]
    static __lccc_rust_global_alloc_impl: &dyn GlobalAlloc;
}

pub unsafe fn alloc(layout: Layout) -> *mut u8{
    __lccc_rust_global_alloc_impl_symbol.alloc(layout)
}

pub unsafe fn alloc_zeroed(layout: Layout) -> *mut u8{
    __lccc_rust_global_alloc_impl_symbol.alloc_zeroed(layout)
}

pub unsafe fn dealloc(ptr: *mut u8,layout: Layout){
    __lccc_rust_global_alloc_impl_symbol.dealloc(ptr,layout)
}

pub unsafe fn realloc(ptr: *mut u8,old_layout: Layout,new_size: usize) -> *mut u8{
    __lccc_rust_global_alloc_impl_symbol.realloc(ptr,old_layout,new_size)
}

pub fn handle_alloc_error(layout: Layout) -> !{
    extern"Rust"{
        #[no_mangle]
        fn __lccc_rust_handle_alloc_error_impl(_: Layout) -> !;
    }
    unsafe{__lccc_rust_handle_alloc_error_impl(layout)}
}

#[no_mangle]
#[lccc::weak]
extern"Rust" fn __lccc_rust_handle_alloc_error_impl(_: Layout) -> !{
    ::__lccc::builtins::C::__builtin_trap()
}

#[unstable(feature="allocator_api",issue="32838")]
pub struct Global;

unsafe impl AllocRef for Global{
    fn alloc(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        if layout.size()==0{
            Ok(unsafe{NonNull::new_unchecked(core::ptr::slice_from_raw_parts_mut(1usize as *mut u8,0))})
        }else {
            let ptr = unsafe { self::alloc(layout) };
            if ptr.is_null() {
                Err(AllocError)
            } else {
                unsafe { NonNull::new_unchecked(core::ptr::slice_from_raw_parts_mut(ptr, layout.size())) }
            }
        }
    }

    unsafe fn dealloc(&self, ptr: NonNull<u8>, layout: Layout) {
        if layout.size()==0{
            ()
        }else {
            self::dealloc(ptr.as_ptr(), layout)
        }
    }

    fn alloc_zeroed(&self, layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        if layout.size()==0{
            Ok(unsafe{NonNull::new_unchecked(core::ptr::slice_from_raw_parts_mut(1usize as *mut u8,0))})
        }else {
            let ptr = unsafe { self::alloc_zeroed(layout) };
            if ptr.is_null() {
                Err(AllocError)
            } else {
                unsafe { NonNull::new_unchecked(core::ptr::slice_from_raw_parts_mut(ptr, layout.size())) }
            }
        }
    }

    unsafe fn grow(&self, ptr: NonNull<u8>, old_layout: Layout, new_layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        if old_layout.size()==0{
            self.alloc(new_layout)
        }else{
            let ptr = self::realloc(ptr.as_ptr(),old_layout,new_layout.size());
            if ptr.is_null(){
                Err(AllocError)
            }else{
                Ok(NonNull::new_unchecked(core::slice::from_raw_parts_mut(ptr,new_layout.size())))
            }
        }
    }

    unsafe fn grow_zeroed(&self, ptr: NonNull<u8>, old_layout: Layout, new_layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        if old_layout.size()==0{
            self.alloc(new_layout)
        }else{
            let ptr = self::realloc(ptr.as_ptr(),old_layout,new_layout.size());
            if ptr.is_null(){
                Err(AllocError)
            }else{
                ::__lccc::builtins::C::__builtin_memset(ptr.add(old_layout.size()),0,new_layout.size()-old_layout.size());
                Ok(NonNull::new_unchecked(core::slice::from_raw_parts_mut(ptr,new_layout.size())))
            }
        }
    }


    unsafe fn shrink(&self, ptr: NonNull<u8>, old_layout: Layout, new_layout: Layout) -> Result<NonNull<[u8]>, AllocError> {
        if new_layout.size()==0{
            self.dealloc(ptr,old_layout);
            Ok(unsafe{NonNull::new_unchecked(core::ptr::slice_from_raw_parts_mut(1usize as *mut u8,0))})
        }else{
            let ptr = self::realloc(ptr.as_ptr(),old_layout,new_layout.size());
            if ptr.is_null(){
                Err(AllocError)
            }else{
                Ok
            }
        }
    }
}