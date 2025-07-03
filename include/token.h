/*
 * This file is part of tinycsharp.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2025 Faith (propenster) Olusegun.
 * Contact: https://propenster.github.io
 */
#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <string>
#include <ostream>

namespace tinycsharp
{
    enum class TokenKind
    {
        kTEndl,
        kTSemiColon,
        kTLParen,
        kTRParen,

        kTType,

        kTAnd,
        kTLogicalAnd,
        kTLogicalOr,
        kTLogicalNot,
        kTXor,

        kTEquality,
        kTAssign,
        kTLessOrEqual,
        kTLessThan,
        kTGreaterOrEqual,
        kTGreaterThan,
        kTHash, // #

        kTAmpersand,
        kTSLiteral,
        kTNLiteral,
        kTBLiteral,

        kTPlus,
        kTIncrement,
        kTPlusAssign,
        kTMinus,
        kTDecrement,   // --
        kTMinusAssign, // -=
        kTStar,
        kTFSlash,
        kTBSlash,
        kTColon,
        kTComma,
        kTLCurly,
        kTRCurly,
        kTLSquare,
        kTRSquare,

        kTNeq, // not equal !=
        kTNot, // not !
        kTOr,  // ||
        kTPipe,
        kTModulo, // %
        kTDot,

        kTIdent,

        // stmt
        kTIf,
        kTDo,
        kTWhile,
        kTReturn,
        // kTElseIf,
        kTElse,

        // wdl shits
        kTQuestion, //?
        kTEllipses, //~

        kTLShift,       //<<
        kTRShift,       //>>
        kTLShiftAssign, //<<<
        kTRShiftAssign, //>>> this to close the kTLShiftAssign
        kTCall,
        kTImport,
        kTAs,
        kTIn,
        kTScatter,
        kTDefault,

        kTSwitch,
        kTCase,
        kTBreak,
        kTContinue,
        kTThrow,
        kTCatch,
        kTFinally,
        kTTry,
        kTVar,
        kTConst,
        kTStruct,
        kTClass,
        kTUsing,
        kTNamespace,
        kTStatic,
        kTVoid,
        kTVirtual,
        kTReadonly,
        kTOverride,
        kTNew,
        kTPublic,
        kTPrivate,
        kTProtected,
        kTInternal,
        kTAbstract,
        kTSealed,
        kTAsync,
        kTAwait,
        kTGet,
        kTSet,
        kTDocComment,
        kTThis,
        kTArrow,

        kTEof,
        kTError,
    };

    // enum class TokenKind
    // {
    //     T_ENDL,
    //     T_SEMICOLON,
    //     T_LPAREN,
    //     T_RPAREN,

    //     T_TYPE, // Int, Float, String, Task, SomeCustomType

    //     T_AND,
    //     T_LOGICAL_AND,
    //     T_LOGICAL_OR,
    //     T_LOGICAL_NOT,
    //     T_XOR,

    //     T_EQUALITY,
    //     T_ASSIGN,
    //     T_LESS_OR_EQUAL,
    //     T_LESS_THAN,
    //     T_GREATER_OR_EQUAL,
    //     T_GREATER_THAN,
    //     T_HASH, // #

    //     T_AMPERSAND,
    //     T_SLITERAL,
    //     T_NLITERAL,
    //     T_BLITERAL, // boolean literal true/false

    //     T_PLUS,
    //     T_INCREMENT,   // ++
    //     T_PLUS_ASSIGN, // +=
    //     T_MINUS,
    //     T_DECREMENT,    // --
    //     T_MINUS_ASSIGN, // -=
    //     T_STAR,
    //     T_FSLASH,
    //     T_BSLASH,
    //     T_COLON,
    //     T_COMMA,
    //     T_LCURLY,
    //     T_RCURLY,
    //     T_LSQUARE,
    //     T_RSQUARE,

    //     T_NEQ, // not equal !=
    //     T_NOT, // not !
    //     T_OR,  // ||
    //     T_PIPE,
    //     T_MODULO, // %
    //     T_DOT,

    //     T_IDENT,

    //     // stmt
    //     T_IF,
    //     T_DO,
    //     T_WHILE,
    //     T_RETURN,
    //     // T_ELSE_IF,
    //     T_ELSE,

    //     // wdl shits
    //     T_QUESTION, //?
    //     T_ELLIPSES, //~
    //     // T_INPUT,
    //     // T_OUTPUT,
    //     // T_RUNTIME,
    //     // T_META,
    //     // T_COMMAND,
    //     // T_THEN,
    //     T_LSHIFT,        //<<
    //     T_RSHIFT,        //>>
    //     T_LSHIFT_ASSIGN, //<<<
    //     T_RSHIFT_ASSIGN, //>>> this to close the T_LSHIFT_ASSIGN
    //     T_COMMENT,       // until when I can fix/ skipping comments, let's have this T_COMMENT here... for # or //

    //     T_CALL,
    //     T_IMPORT,
    //     T_AS,
    //     T_IN,
    //     T_SCATTER,
    //     T_DEFAULT,

    //     T_SWITCH,
    //     T_CASE,
    //     T_BREAK,
    //     T_CONTINUE,
    //     T_THROW,
    //     T_CATCH,
    //     T_FINALLY,
    //     T_TRY,
    //     T_VAR,
    //     T_CONST,
    //     T_STRUCT,
    //     T_CLASS,
    //     T_USING,
    //     T_NAMESPACE,
    //     T_STATIC,
    //     T_VOID,
    //     T_VIRTUAL,
    //     T_READONLY,
    //     T_OVERRIDE,
    //     T_NEW,
    //     T_PUBLIC,
    //     T_PRIVATE,
    //     T_PROTECTED,
    //     T_INTERNAL,
    //     T_ABSTRACT,
    //     T_SEALED,
    //     T_ASYNC,
    //     T_AWAIT,
    //     T_GET,
    //     T_SET,
    //     T_DOC_COMMENT, // this guy in c# /// <summary>...</summary>
    //     T_THIS,
    //     T_ARROW,

    //     T_EOF,
    //     T_ERROR,

    // };

    inline const char *TokenKindToString(TokenKind kind)
    {
        using TK = TokenKind;
        switch (kind)
        {
        case TK::kTEndl:
            return "kTEndl";
        case TK::kTSemiColon:
            return "kTSemiColon";
        case TK::kTLParen:
            return "kTLParen";
        case TK::kTRParen:
            return "kTRParen";
        case TK::kTType:
            return "kTType";
        case TK::kTAnd:
            return "kTAnd";
        case TK::kTLogicalAnd:
            return "kTLogicalAnd";
        case TK::kTLogicalOr:
            return "kTLogicalOr";
        case TK::kTLogicalNot:
            return "kTLogicalNot";
        case TK::kTXor:
            return "kTXor";
        case TK::kTEquality:
            return "kTEquality";
        case TK::kTAssign:
            return "kTAssign";
        case TK::kTLessOrEqual:
            return "kTLessOrEqual";
        case TK::kTLessThan:
            return "kTLessThan";
        case TK::kTGreaterOrEqual:
            return "kTGreaterOrEqual";
        case TK::kTGreaterThan:
            return "kTGreaterThan";
        case TK::kTHash:
            return "kTHash";
        case TK::kTAmpersand:
            return "kTAmpersand";
        case TK::kTSLiteral:
            return "kTSLiteral";
        case TK::kTNLiteral:
            return "kTNLiteral";
        case TK::kTBLiteral:
            return "kTBLiteral";
        case TK::kTPlus:
            return "kTPlus";
        case TK::kTIncrement:
            return "kTIncrement";
        case TK::kTPlusAssign:
            return "kTPlusAssign";
        case TK::kTMinus:
            return "kTMinus";
        case TK::kTDecrement:
            return "kTDecrement";
        case TK::kTMinusAssign:
            return "kTMinusAssign";
        case TK::kTStar:
            return "kTStar";
        case TK::kTFSlash:
            return "kTFSlash";
        case TK::kTBSlash:
            return "kTBSlash";
        case TK::kTColon:
            return "kTColon";
        case TK::kTComma:
            return "kTComma";
        case TK::kTLCurly:
            return "kTLCurly";
        case TK::kTRCurly:
            return "kTRCurly";
        case TK::kTLSquare:
            return "kTLSquare";
        case TK::kTRSquare:
            return "kTRSquare";
        case TK::kTNeq:
            return "kTNeq";
        case TK::kTNot:
            return "kTNot";
        case TK::kTOr:
            return "kTOr";
        case TK::kTPipe:
            return "kTPipe";
        case TK::kTModulo:
            return "kTModulo";
        case TK::kTDot:
            return "kTDot";
        case TK::kTIdent:
            return "kTIdent";
        case TK::kTIf:
            return "kTIf";
        case TK::kTDo:
            return "kTDo";
        case TK::kTWhile:
            return "kTWhile";
        case TK::kTReturn:
            return "kTReturn";
        case TK::kTElse:
            return "kTElse";
        case TK::kTQuestion:
            return "kTQuestion";
        case TK::kTEllipses:
            return "kTEllipses";
        case TK::kTLShift:
            return "kTLShift";
        case TK::kTRShift:
            return "kTRShift";
        case TK::kTLShiftAssign:
            return "kTLShiftAssign";
        case TK::kTRShiftAssign:
            return "kTRShiftAssign";
        case TK::kTCall:
            return "kTCall";
        case TK::kTImport:
            return "kTImport";
        case TK::kTAs:
            return "kTAs";
        case TK::kTIn:
            return "kTIn";
        case TK::kTScatter:
            return "kTScatter";
        case TK::kTDefault:
            return "kTDefault";
        case TK::kTSwitch:
            return "kTSwitch";
        case TK::kTCase:
            return "kTCase";
        case TK::kTBreak:
            return "kTBreak";
        case TK::kTContinue:
            return "kTContinue";
        case TK::kTThrow:
            return "kTThrow";
        case TK::kTCatch:
            return "kTCatch";
        case TK::kTFinally:
            return "kTFinally";
        case TK::kTTry:
            return "kTTry";
        case TK::kTVar:
            return "kTVar";
        case TK::kTConst:
            return "kTConst";
        case TK::kTStruct:
            return "kTStruct";
        case TK::kTClass:
            return "kTClass";
        case TK::kTUsing:
            return "kTUsing";
        case TK::kTNamespace:
            return "kTNamespace";
        case TK::kTStatic:
            return "kTStatic";
        case TK::kTVoid:
            return "kTVoid";
        case TK::kTVirtual:
            return "kTVirtual";
        case TK::kTReadonly:
            return "kTReadonly";
        case TK::kTOverride:
            return "kTOverride";
        case TK::kTNew:
            return "kTNew";
        case TK::kTPublic:
            return "kTPublic";
        case TK::kTPrivate:
            return "kTPrivate";
        case TK::kTProtected:
            return "kTProtected";
        case TK::kTInternal:
            return "kTInternal";
        case TK::kTAbstract:
            return "kTAbstract";
        case TK::kTSealed:
            return "kTSealed";
        case TK::kTAsync:
            return "kTAsync";
        case TK::kTAwait:
            return "kTAwait";
        case TK::kTGet:
            return "kTGet";
        case TK::kTSet:
            return "kTSet";
        case TK::kTDocComment:
            return "kTDocComment";
        case TK::kTThis:
            return "kTThis";
        case TK::kTArrow:
            return "kTArrow";
        case TK::kTEof:
            return "kTEof";
        case TK::kTError:
            return "kTError";
        default:
            return "UNKNOWN";
        }
    }

    // this Token object...
    // ref
    struct Token
    {
    public:
        TokenKind kind;
        std::string lexeme;
        std::shared_ptr<Token> next;
        std::shared_ptr<int> int_val;
        std::shared_ptr<double> float_val;
        int line; // current line this Token is in..
        int column;

        Token(TokenKind kind, const std::string &literal) : kind(kind), lexeme(literal), next(nullptr), int_val(nullptr), float_val(nullptr) {}
        Token(TokenKind kind, const std::string &literal, int int_val) : kind(kind), lexeme(literal), next(nullptr), int_val(std::make_shared<int>(int_val)), float_val(nullptr) {}
        Token(TokenKind kind, const std::string &literal, double float_val) : kind(kind), lexeme(literal), next(nullptr), int_val(nullptr), float_val(std::make_shared<double>(float_val)) {}

        Token() = default;
        ~Token() = default;
        Token(Token &&) = default;
        Token &operator=(Token &&) = default;
        Token(const Token &) = delete;
        Token &operator=(const Token &) = delete;
    };

    inline std::ostream &operator<<(std::ostream &os, const Token &tok)
    {
        os << "Token(kind=" << TokenKindToString(tok.kind) << ", lexeme=\"" << tok.lexeme << "\"" << ", line=" << tok.line << ", column=" << tok.column;

        if (tok.int_val)
        {
            os << ", int_val=" << *tok.int_val;
        }
        if (tok.float_val)
        {
            os << ", float_val=" << *tok.float_val;
        }
        os << ")";
        return os;
    }

}

#endif