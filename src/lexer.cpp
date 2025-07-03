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

#include "lexer.h"
#include "utils.h"
#include <iostream>
#include <sstream>
#include <exception>
#include <cctype>

namespace tinycsharp
{

    Lexer::Lexer(std::string input)
        : source(PadSourceStr(input)), position(-1), line(std::make_shared<int>(1)), column(std::make_shared<int>(-1))
    {
        if (input.empty() || std::all_of(input.begin(), input.end(), ::isspace))
        {
            throw std::invalid_argument("Input source cannot be empty");
        }
        // std::cout << "the input source to be Tokenized is >>> " << source << std::endl;

        NextToken();
    }
    std::string Lexer::PadSourceStr(const std::string &input)
    {
        std::ostringstream ss;
        ss << " " << input << " ";
        return ss.str();
    }
    std::unique_ptr<Lexer> Lexer::Clone() const
    {
        return std::make_unique<Lexer>(*this);
    }
    char Lexer::Peek()
    {
        if (position + 1 >= source.length())
        {
            return '\0';
        }
        return source[position + 1];
    }

    Token Lexer::Lex()
    {
        if (source.empty())
        {
            return Token{TokenKind::kTError, "[ERROR] Input source is empty"};
        }
        Token tok{TokenKind::kTEof, "\0"};
        NextToken();
        ConsumeWhitespace();
        std::string l(1, c_char);
        if (c_char == ';')
        {
            return NewToken(TokenKind::kTSemiColon, l, position);
        }
        else if (c_char == '\0')
        {
            return tok;
        }
        else if (c_char == '(')
        {
            return NewToken(TokenKind::kTLParen, l, position);
        }
        else if (c_char == ')')
        {
            return NewToken(TokenKind::kTRParen, l, position);
        }
        else if (c_char == '{')
        {
            return NewToken(TokenKind::kTLCurly, l, position);
        }
        else if (c_char == '}')
        {
            return NewToken(TokenKind::kTRCurly, l, position);
        }
        else if (c_char == '[')
        {
            return NewToken(TokenKind::kTLSquare, l, position);
        }
        else if (c_char == ']')
        {
            return NewToken(TokenKind::kTRSquare, l, position);
        }
        else if (std::isalpha(c_char) || c_char == '_')
        {
            tok = MakeIdentifierToken();
            if (IsReservedWord(tok.lexeme))
            {
                MakeReservedWordToken(tok);
            }
            return tok;
        }
        else if (c_char == '=')
        {
            n_char = Peek();
            if (n_char == '=')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTEquality, l, position);
            }
            else if (n_char == '>')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTArrow, l, position);
            }
            return NewToken(TokenKind::kTAssign, l, position);
        }
        else if (c_char == '<')
        {
            n_char = Peek();
            if (n_char == '=')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTLessOrEqual, l, position);
            }
            else if (n_char == '<')
            {
                l += n_char;
                NextToken();
                if (c_char == '<')
                {
                    l += c_char;
                    NextToken();

                    return NewToken(TokenKind::kTLShiftAssign, l, position);
                }

                return NewToken(TokenKind::kTLShift, l, position);
            }
            return NewToken(TokenKind::kTLessThan, l, position);
        }
        else if (c_char == '>')
        {
            n_char = Peek();
            if (n_char == '=')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTGreaterOrEqual, l, position);
            }
            else if (n_char == '>')
            {
                l += n_char;
                NextToken();
                if (c_char == '>')
                {
                    l += c_char;
                    NextToken();

                    return NewToken(TokenKind::kTRShiftAssign, l, position);
                }

                return NewToken(TokenKind::kTRShift, l, position);
            }
            return NewToken(TokenKind::kTGreaterThan, l, position);
        }
        else if (c_char == '#')
        {
            return NewToken(TokenKind::kTHash, l, position);
        }
        else if (c_char == '&')
        {
            n_char = Peek();
            if (n_char == '&')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTLogicalAnd, l, position);
            }
            return NewToken(TokenKind::kTAmpersand, l, position);
        }
        else if (c_char == '\"' || c_char == '\'')
        {
            return MakeStringLiteralToken();
        }
        else if (std::isdigit(c_char))
        {
            return MakeNumericLiteralToken();
        }
        else if (c_char == '+')
        {
            n_char = Peek();
            if (n_char == '+')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTIncrement, l, position);
            }
            else if (n_char == '=')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTPlusAssign, l, position);
            }
            return NewToken(TokenKind::kTPlus, l, position);
        }
        else if (c_char == '-')
        {
            n_char = Peek();
            if (n_char == '-')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTDecrement, l, position);
            }
            else if (n_char == '=')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTMinusAssign, l, position);
            }

            return NewToken(TokenKind::kTMinus, l, position);
        }
        else if (c_char == '*')
        {
            return NewToken(TokenKind::kTStar, l, position);
        }
        else if (c_char == '?')
        {
            return NewToken(TokenKind::kTQuestion, l, position);
        }
        else if (c_char == '|' && Peek() == '|')
        {
            l += Peek();
            NextToken();
            return NewToken(TokenKind::kTLogicalOr, l, position);
        }
        else if (c_char == '^')
        {
            return NewToken(TokenKind::kTXor, l, position);
        }
        else if (c_char == '/')
        {
            n_char = Peek();
            if (n_char == '/')
            {
                l += n_char;
                NextToken();
                if (Peek() == '/') // doc_comment
                {
                    l += Peek();
                    NextToken();
                    while (c_char != '\0' && Peek() != '\n')
                    {
                        NextToken();
                        l += c_char;
                    }
                    return NewToken(TokenKind::kTDocComment, l, position);
                }

                SkipSingleLineComment();
                return Lex();
            }
            if (n_char == '*')
            {
                SkipMultiLineComment();
                return Lex();
            }
            return NewToken(TokenKind::kTFSlash, l, position);
        }
        else if (c_char == ':')
        {
            return NewToken(TokenKind::kTColon, l, position);
        }
        else if (c_char == ',')
        {
            return NewToken(TokenKind::kTComma, l, position);
        }
        else if (c_char == '!')
        {
            int start_pos = position;
            n_char = Peek();
            if (n_char == '=')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTNeq, l, start_pos);
            }
            return NewToken(TokenKind::kTNot, l, start_pos);
        }
        else if (c_char == '|')
        {
            int start_pos = position;
            n_char = Peek();
            if (n_char == '|')
            {
                l += n_char;
                NextToken();
                return NewToken(TokenKind::kTOr, l, start_pos);
            }
            return NewToken(TokenKind::kTPipe, l, start_pos);
        }
        else if (c_char == '%')
        {
            return NewToken(TokenKind::kTModulo, l, position);
        }
        else if (c_char == '.')
        {
            return NewToken(TokenKind::kTDot, l, position);
        }

        return tok;
    }
    Token Lexer::NewToken(const TokenKind &kind, const std::string &lexeme, int start_pos)
    {
        Token tok{kind, lexeme};
        tok.line = *line;
        tok.column = *column - (position - start_pos);
        return tok;
    }
    Token Lexer::NewToken(const TokenKind &kind, const std::string &lexeme, int start_pos, int int_val)
    {
        Token tok = NewToken(kind, lexeme, start_pos);
        tok.int_val = std::make_unique<int>(std::move(int_val));
        return tok;
    }
    Token Lexer::NewToken(const TokenKind &kind, const std::string &lexeme, int start_pos, double float_val)
    {
        Token tok = NewToken(kind, lexeme, start_pos);
        tok.float_val = std::make_unique<double>(std::move(float_val));
        return tok;
    }
    void Lexer::NextToken()
    {
        position++;
        if (position >= source.length())
        {
            c_char = '\0';
        }
        else
        {
            c_char = source[position];
            if (c_char == '\n')
            {
                (*line)++;
                (*column) = 0;
            }
            else
            {
                (*column)++;
            }
        }
    }
    Token Lexer::MakeStringLiteralToken()
    {
        char stop_char = c_char;
        NextToken();
        int curr_pos = position;
        while (c_char != '\0' && Peek() != stop_char)
        {
            NextToken();
        }
        NextToken();

        std::string l = source.substr(curr_pos, position - curr_pos);
        return NewToken(TokenKind::kTSLiteral, l, curr_pos - 1);
    }

    Token Lexer::MakeErrorToken(const std::string &message, int position)
    {
        std::ostringstream os;
        os << "[ERROR] Invalid Token: " << message;
        return NewToken(TokenKind::kTError, os.str(), position);
    }
    Token Lexer::MakeIdentifierToken()
    {
        int start_pos = position;
        while ((std::isalnum(c_char) || c_char == '_') && IsCharAValidIdentElem(Peek()))
        {
            NextToken();
        }
        std::string ident = source.substr(start_pos, position + 1 - start_pos);
        return NewToken(TokenKind::kTIdent, ident, start_pos);
    }

    Token Lexer::MakeNumericLiteralToken()
    {
        int start_pos = position;
        bool is_float = false;

        while (c_char != '\0' && util::array_contains_char(Peek()))
        {
            if (c_char == '.')
            {
                is_float = true;
            }
            NextToken();
        }

        std::string number_literal = source.substr(start_pos, position - start_pos + 1);

        if (std::count(number_literal.begin(), number_literal.end(), '.') > 1)
        {
            throw std::runtime_error("Invalid number format: " + number_literal);
        }
        if (is_float)
        {
            return NewToken(TokenKind::kTNLiteral, number_literal, start_pos, std::stod(number_literal));
        }
        return NewToken(TokenKind::kTNLiteral, number_literal, start_pos, std::stoi(number_literal));
    }
    bool Lexer::IsCharAValidIdentElem(char32_t n_char)
    {
        return std::isalnum(n_char) || n_char == '_' || n_char == '?';
    }
    void Lexer::ConsumeWhitespace()
    {
        while (std::isspace(c_char))
        {
            if (IsNewlineChar(c_char))
            {
                (*line)++;
                (*column) = 1;
            }
            NextToken();
        }
    }
    void Lexer::SkipSingleLineComment()
    {
        while (c_char != '\0' && !IsNewlineChar(c_char))
        {
            NextToken();
        }
    }
    void Lexer::SkipMultiLineComment()
    {
        bool ended = false;
        while (!ended)
        {
            if (c_char == '\0')
            {
                ended = true;
            }

            if (c_char == '*' && Peek() == '/')
            {
                ended = true;
                NextToken();
            }
            NextToken();
        }
    }
    void Lexer::SkipComments()
    {
        if (IsNewlineChar(c_char))
        {
            (*line)++;
            (*column) = 1;
            return;
        }
        if (c_char != '\0' && (c_char == '#' || (c_char = '/' && n_char == '/')))
        {
            NextToken();
            while (c_char != '\0' && !IsNewlineChar(c_char))
            {
                NextToken();
            }
        }
    }
    void Lexer::MakeReservedWordToken(Token &tok)
    {
        std::string l = util::to_lowercase(tok.lexeme);
        if (l == "as")
        {
            tok.kind = TokenKind::kTAs;
        }
        else if (l == "true" || l == "false")
        {
            tok.kind = TokenKind::kTBLiteral;
        }
        else if (l == "default")
        {
            tok.kind = TokenKind::kTDefault;
        }
        else if (l == "xor")
        {
            tok.kind = TokenKind::kTXor;
        }
        else if (IsTypeToken(l))
        {
            tok.kind = TokenKind::kTType;
        }
        else if (l == "if")
        {
            tok.kind = TokenKind::kTIf;
        }
        else if (l == "else")
        {
            tok.kind = TokenKind::kTElse;
        }
        else if (l == "do")
        {
            tok.kind = TokenKind::kTDo;
        }
        else if (l == "while")
        {
            tok.kind = TokenKind::kTWhile;
        }
        else if (l == "return")
        {
            tok.kind = TokenKind::kTReturn;
        }

        else if (l == "in")
        {
            tok.kind = TokenKind::kTIn;
        }
        else if (l == "default")
        {
            tok.kind = TokenKind::kTDefault;
        }
        else if (l == "const")
        {
            tok.kind = TokenKind::kTConst;
        }
        else if (l == "struct")
        {
            tok.kind = TokenKind::kTStruct;
        }
        else if (l == "class")
        {
            tok.kind = TokenKind::kTClass;
        }
        else if (l == "switch")
        {
            tok.kind = TokenKind::kTSwitch;
        }
        else if (l == "case")
        {
            tok.kind = TokenKind::kTCase;
        }
        else if (l == "break")
        {
            tok.kind = TokenKind::kTBreak;
        }
        else if (l == "continue")
        {
            tok.kind = TokenKind::kTContinue;
        }
        else if (l == "throw")
        {
            tok.kind = TokenKind::kTThrow;
        }
        else if (l == "catch")
        {
            tok.kind = TokenKind::kTCatch;
        }
        else if (l == "finally")
        {
            tok.kind = TokenKind::kTFinally;
        }
        else if (l == "try")
        {
            tok.kind = TokenKind::kTTry;
        }
        else if (l == "var")
        {
            tok.kind = TokenKind::kTVar;
        }
        else if (l == "using")
        {
            tok.kind = TokenKind::kTUsing;
        }
        else if (l == "namespace")
        {
            tok.kind = TokenKind::kTNamespace;
        }
        else if (l == "static")
        {
            tok.kind = TokenKind::kTStatic;
        }
        else if (l == "virtual")
        {
            tok.kind = TokenKind::kTVirtual;
        }
        else if (l == "readonly")
        {
            tok.kind = TokenKind::kTReadonly;
        }
        else if (l == "new")
        {
            tok.kind = TokenKind::kTNew;
        }
        else if (l == "public")
        {
            tok.kind = TokenKind::kTPublic;
        }
        else if (l == "private")
        {
            tok.kind = TokenKind::kTPrivate;
        }
        else if (l == "protected")
        {
            tok.kind = TokenKind::kTProtected;
        }
        else if (l == "internal")
        {
            tok.kind = TokenKind::kTInternal;
        }

        else if (l == "override")
        {
            tok.kind = TokenKind::kTOverride;
        }
        else if (l == "abstract")
        {
            tok.kind = TokenKind::kTAbstract;
        }
        else if (l == "sealed")
        {
            tok.kind = TokenKind::kTSealed;
        }
        else if (l == "async")
        {
            tok.kind = TokenKind::kTAsync;
        }
        else if (l == "await")
        {
            tok.kind = TokenKind::kTAwait;
        }
        else if (l == "get")
        {
            tok.kind = TokenKind::kTGet;
        }
        else if (l == "set")
        {
            tok.kind = TokenKind::kTSet;
        }
        else if (l == "this")
        {
            tok.kind = TokenKind::kTThis;
        }
        else if (l == "void")
        {
            tok.kind = TokenKind::kTVoid;
        }
        else
        {
            tok.kind = TokenKind::kTIdent;
        }
    }
    bool Lexer::IsNewlineChar(unsigned char chr)
    {
        return chr == '\n';
    }
    bool Lexer::IsReservedWord(const std::string &word)
    {
        const std::array<std::string, 70> reserved_words = {"and", "or", "xor", "not", "task", "struct", "int", "byte", "short", "long", "float", "string", "bool", "object", "char", "class", "if", "else", "while", "return", "do", "input", "output", "runtime", "parameter_meta", "command", "then", "array", "file", "true", "false", "boolean", "workflow", "call", "import", "as", "map", "in", "scatter", "pair", "default", "var", "const", "switch", "case", "break", "continue", "throw", "catch", "finally", "try", "using", "namespace", "static", "virtual", "readonly", "new", "public", "private", "protected", "internal", "override", "abstract", "sealed", "async", "await", "get", "set", "this", "void"};
        for (const auto &i : reserved_words)
        {
            if (i == util::to_lowercase(word))
                return true;
        }
        return false;
    }
    bool Lexer::IsTypeToken(const std::string &word)
    {
        const std::array<std::string, 21> reserved_words = {
            "int",
            "float",
            "string",
            "bool",
            "char",
            "struct",
            "task",
            "class",
            "array",
            "file",
            "input",
            "output",
            "boolean",
            "workflow",
            "byte",
            "short",
            "long",
            "object",
            "map",
            "struct",
            "pair"};
        for (const auto &i : reserved_words)
        {
            if (i == util::to_lowercase(word))
                return true;
        }
        return false;
    }
    bool Lexer::IsUnicode(const char &chr)
    {
        char t = chr;
        char32_t unicode = static_cast<char32_t>(static_cast<unsigned char>(chr));

        const std::array<char32_t, 3> unicode_chars = {U'\u2227', U'\u2228', U'\u00AC'};
        for (const auto &i : unicode_chars)
        {
            if (i == unicode)
                return true;
        }
        return false;
    }

}
