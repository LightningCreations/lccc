pub mod v1 {
    pub use crate::marker::{Copy, Send, Sized, Sync, Unpin};

    pub use crate::option::*;

    pub use crate::cmp::{Eq, Ord, Ordering, PartialEq, PartialOrd};

    pub use crate::result::*;

    pub use crate::ops::Drop;

    #[__lccc::builtin_macro]
    pub macro RustcDecodable($($tt:tt)*) {}

    #[__lccc::builtin_macro]
    pub macro RustcEncodable($($tt:tt)*) {}
}
