use nom::error::VerboseError;
use nom::IResult;
use nom::branch::alt;
use crate::ast::statements::StatementObject;
use crate::parsers::Span;
use crate::parsers::statements::if_object::if_parser;
use crate::parsers::statements::let_object::let_parser;
use crate::parsers::statements::ret_object::ret_parser;

///
/// Parse a statement into `StatementObject`.
///
pub fn statement_parser(text: Span) -> IResult<Span, StatementObject, VerboseError<Span>> {
    alt((
        if_parser,
        let_parser,
        ret_parser
    ))(text)
}

pub mod if_object;
pub mod let_object;
pub mod ret_object;
