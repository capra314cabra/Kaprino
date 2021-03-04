use crate::ast::CodeGen;
use crate::ast::statements::if_object::IfObject;
use crate::ast::statements::let_object::LetObject;
use crate::ast::statements::ret_object::RetObject;
use crate::error::error_token::ErrorToken;

///
/// `StatementObject` is an object which represents a statement of sources.
///
#[derive(Debug,PartialEq)]
pub enum StatementObject {
    IfObject(Box<IfObject>),
    LetObject(Box<LetObject>),
    RetObject(Box<RetObject>)
}

impl<'ctx> StatementObject {
    ///
    /// Generate the part of the abstract syntax tree.
    ///
    pub fn codegen(&self, gen: &CodeGen<'ctx>) -> Result<(), ErrorToken> {
        match self {
            StatementObject::IfObject(obj) => obj.codegen(gen),
            StatementObject::LetObject(obj) => obj.codegen(gen),
            StatementObject::RetObject(obj) => obj.codegen(gen)
        }
    }
}

pub mod if_object;
pub mod let_object;
pub mod ret_object;
