#![feature(lang_items,intrinsics,no_core,optin_builtin_traits)]
#![feature(rustc_attrs,const_fn,reciever_trait)]
#![feature(lccc_const_transmute,lccc_slice_layout,lccc_const_zeroed)]
#![feature(unsize,negative_impls,no_niche,untagged_unions,prelude_import)]
#![feature(lccc_borrowck_helpers)]
#![feature(lccc_trait_object)]
#![feature(lccc_lang_items)]
#![feature(fn_traits)]
#![no_core]

#[prelude_import]
pub use prelude::v1::*;


mod bool;
mod unit;

pub mod marker;
pub mod clone;
pub mod cmp;
pub mod cell;
pub mod borrow;
pub mod slice;
pub mod intrinsics;
pub mod ops;
pub mod mem;
pub mod primitive;
pub mod option;
pub mod prelude;
pub mod ptr;
pub mod alloc;
pub mod raw;
pub mod result;
pub mod convert;
pub mod default;
pub mod iter;

#[rustc_builtin_macro]
#[allow_internal_unstable(core_intrinsics)]
pub macro panic($($input:tt),*){}