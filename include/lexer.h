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
#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <iostream>
#include "token.h"

namespace tinycsharp
{

    struct Lexer
    {

    public:
        int position;
        unsigned char c_char;
        unsigned char n_char;
        std::string source;
        std::shared_ptr<int> line;
        std::shared_ptr<int> column;

        Lexer(std::string);
        Lexer() = default;
        ~Lexer() = default;

        Token Lex();
        void NextToken();
        char Peek();
        void ConsumeWhitespace();
        void SkipSingleLineComment();
        void SkipMultiLineComment();
        void SkipComments();
        Token MakeIdentifierToken();
        void MakeReservedWordToken(Token &);
        Token MakeStringLiteralToken();
        Token MakeNumericLiteralToken();
        Token NewToken(const TokenKind &, const std::string &, int);
        Token NewToken(const TokenKind &, const std::string &, int, int);
        Token NewToken(const TokenKind &, const std::string &, int, double);
        std::unique_ptr<Lexer> Clone() const;

        bool IsReservedWord(const std::string &);
        bool IsTypeToken(const std::string &);

    private:
        static bool IsNewlineChar(unsigned char);
        bool IsUnicode(const char &);
        bool IsCharAValidIdentElem(char32_t);
        std::string PadSourceStr(const std::string &);
        Token MakeErrorToken(const std::string &, int);
    };

}

#endif