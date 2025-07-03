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
#include <gtest/gtest.h>
#include "lexer.h"
#include "token.h"

#include <vector>
#include <string>
#include <stdexcept>

namespace tinycsharp_test
{

    // Demonstrate some basic assertions.
    TEST(HelloTest, BasicAssertions)
    {
        // Expect two strings not to be equal.
        EXPECT_STRNE("hello", "world");
        // Expect equality.
        EXPECT_EQ(7 * 6, 42);
    }

    class LexerTest : public ::testing::Test
    {
    protected:
        const std::string input = R"(
var five = 5;
var ten = 10;
var add = func(x, y) {
    x + y;
};
var result = add(five, ten);

!-*/5;
5 < 10 > 5;

if (5 < 10) {
    return true;
} else {
    return false;
}

10 == 10;
10 != 9;

"foobar"
"foo bar"

/* multiline comment */

[1, 2];

{"foo": "bar"}

true && false;
true || false;

// This is a comment above the number 10
10

10 // This is a comment to the right of 10

const cantChangeMe = "neato";

10 % 3;

five++
five--

5 >= 5;
5 <= 5;

/*
    multiline comment
*/

var snake_case_with_question_mark? = true;
)";

        const std::string actual_csharp_code = R"(
using JinianNet.JNTemplate;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Net;
using System.Runtime.CompilerServices;
using System.Text;

namespace Veal
{
    /// <summary>
    /// HttpResponder represents are response returned to an HTTP-call received via any of the configured 
    /// </summary>
    public class HttpResponder //<T> where T : class, new()
    {
        public int StatusCode { get; set; }
        public bool SendChunked { get; set; }
        public string StatusDescription { get; set; }
        public long ContentLength { get; set; }
        public string ContentType { get; set; }
        public Encoding Encoding { get; set; } = Encoding.UTF8;
        public string Language { get; set; } = "en-US";
        public string ContentDisposition { get; set; }
        public static Dictionary<string, object> ViewData { get; set; } = new Dictionary<string, object>();
        public object Value { get; set; }
        public bool KeepAlive { get; set; }
        /// <summary>
        /// Add a view data to the viewData collection. Used with HttpResponder that returns HTML views
        /// </summary>
        /// <param name="key">key of the data</param>
        /// <param name="value">object that represents the value</param>
        /// <returns></returns>
        public HttpResponder With(string key, object value)
        {
            if(!ViewData.ContainsKey(key)) ViewData.Add(key, value); return this;
        }
        
        public HttpResponder DataToList(){
            var list = await _db.ToListAsync();
            var newList = list.Select(x => new {
                Key = x.Key,
                Value = x.Value
            }).ToList();
        }
    }
}
)";
    };

    TEST_F(LexerTest, ShouldTokenizeCorrectlyBasedOnLexerRules)
    {
        struct ExpectedToken
        {
            tinycsharp::TokenKind kind;
            std::string lexeme;
        };

        const std::vector<ExpectedToken> expected_tokens = {
            {tinycsharp::TokenKind::kTVar, "var"},
            {tinycsharp::TokenKind::kTIdent, "five"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTVar, "var"},
            {tinycsharp::TokenKind::kTIdent, "ten"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTVar, "var"},
            {tinycsharp::TokenKind::kTIdent, "add"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTIdent, "func"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTIdent, "x"},
            {tinycsharp::TokenKind::kTComma, ","},
            {tinycsharp::TokenKind::kTIdent, "y"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTIdent, "x"},
            {tinycsharp::TokenKind::kTPlus, "+"},
            {tinycsharp::TokenKind::kTIdent, "y"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTVar, "var"},
            {tinycsharp::TokenKind::kTIdent, "result"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTIdent, "add"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTIdent, "five"},
            {tinycsharp::TokenKind::kTComma, ","},
            {tinycsharp::TokenKind::kTIdent, "ten"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTNot, "!"},
            {tinycsharp::TokenKind::kTMinus, "-"},
            {tinycsharp::TokenKind::kTStar, "*"},
            {tinycsharp::TokenKind::kTFSlash, "/"},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTLessThan, "<"},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTGreaterThan, ">"},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTIf, "if"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTLessThan, "<"},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTReturn, "return"},
            {tinycsharp::TokenKind::kTBLiteral, "true"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTElse, "else"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTReturn, "return"},
            {tinycsharp::TokenKind::kTBLiteral, "false"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTEquality, "=="},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTNeq, "!="},
            {tinycsharp::TokenKind::kTNLiteral, "9"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSLiteral, "foobar"},
            {tinycsharp::TokenKind::kTSLiteral, "foo bar"},
            {tinycsharp::TokenKind::kTLSquare, "["},
            {tinycsharp::TokenKind::kTNLiteral, "1"},
            {tinycsharp::TokenKind::kTComma, ","},
            {tinycsharp::TokenKind::kTNLiteral, "2"},
            {tinycsharp::TokenKind::kTRSquare, "]"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTSLiteral, "foo"},
            {tinycsharp::TokenKind::kTColon, ":"},
            {tinycsharp::TokenKind::kTSLiteral, "bar"},
            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTBLiteral, "true"},
            {tinycsharp::TokenKind::kTLogicalAnd, "&&"},
            {tinycsharp::TokenKind::kTBLiteral, "false"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTBLiteral, "true"},
            {tinycsharp::TokenKind::kTLogicalOr, "||"},
            {tinycsharp::TokenKind::kTBLiteral, "false"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTConst, "const"},
            {tinycsharp::TokenKind::kTIdent, "cantChangeMe"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTSLiteral, "neato"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTNLiteral, "10"},
            {tinycsharp::TokenKind::kTModulo, "%"},
            {tinycsharp::TokenKind::kTNLiteral, "3"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTIdent, "five"},
            {tinycsharp::TokenKind::kTIncrement, "++"},
            {tinycsharp::TokenKind::kTIdent, "five"},
            {tinycsharp::TokenKind::kTDecrement, "--"},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTGreaterOrEqual, ">="},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTLessOrEqual, "<="},
            {tinycsharp::TokenKind::kTNLiteral, "5"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTVar, "var"},
            {tinycsharp::TokenKind::kTIdent, "snake_case_with_question_mark?"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTBLiteral, "true"},
            {tinycsharp::TokenKind::kTSemiColon, ";"}};

        tinycsharp::Lexer lexer(input);

        for (const auto &expected : expected_tokens)
        {
            SCOPED_TRACE("Testing token with expected lexeme: " + expected.lexeme);

            auto actual_token = lexer.Lex();

            EXPECT_EQ(actual_token.kind, expected.kind);
            EXPECT_EQ(actual_token.lexeme, expected.lexeme);
        }

        auto eof_token = lexer.Lex();
        EXPECT_EQ(eof_token.kind, tinycsharp::TokenKind::kTEof);
        EXPECT_EQ(eof_token.lexeme, "");
    }

    TEST_F(LexerTest, ShouldTokenizeEntireCSharpCodeCorrectly)
    {
        struct ExpectedToken
        {
            tinycsharp::TokenKind kind;
            std::string lexeme;
        };

        const std::vector<ExpectedToken> expected_tokens = {
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "JinianNet"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "JNTemplate"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "Newtonsoft"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Json"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Linq"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Collections"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Generic"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Globalization"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "IO"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Linq"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Net"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Runtime"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "CompilerServices"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTUsing, "using"},
            {tinycsharp::TokenKind::kTIdent, "System"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Text"},

            {tinycsharp::TokenKind::kTSemiColon, ";"},

            {tinycsharp::TokenKind::kTNamespace, "namespace"},
            {tinycsharp::TokenKind::kTIdent, "Veal"},
            {tinycsharp::TokenKind::kTLCurly, "{"},

            {tinycsharp::TokenKind::kTDocComment, "/// <summary>"},
            {tinycsharp::TokenKind::kTDocComment, "/// HttpResponder represents are response returned to an HTTP-call received via any of the configured "},
            {tinycsharp::TokenKind::kTDocComment, "/// </summary>"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "class"},
            {tinycsharp::TokenKind::kTIdent, "HttpResponder"},
            {tinycsharp::TokenKind::kTLCurly, "{"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "int"},
            {tinycsharp::TokenKind::kTIdent, "StatusCode"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "bool"},
            {tinycsharp::TokenKind::kTIdent, "SendChunked"},
            {tinycsharp::TokenKind::kTLCurly, "{"},

            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "string"},
            {tinycsharp::TokenKind::kTIdent, "StatusDescription"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "long"},
            {tinycsharp::TokenKind::kTIdent, "ContentLength"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "string"},
            {tinycsharp::TokenKind::kTIdent, "ContentType"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTIdent, "Encoding"},
            {tinycsharp::TokenKind::kTIdent, "Encoding"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTIdent, "Encoding"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "UTF8"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "string"},
            {tinycsharp::TokenKind::kTIdent, "Language"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTSLiteral, "en-US"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "string"},
            {tinycsharp::TokenKind::kTIdent, "ContentDisposition"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTStatic, "static"},
            {tinycsharp::TokenKind::kTIdent, "Dictionary"},
            {tinycsharp::TokenKind::kTLessThan, "<"},
            {tinycsharp::TokenKind::kTType, "string"},
            {tinycsharp::TokenKind::kTComma, ","},
            {tinycsharp::TokenKind::kTType, "object"},
            {tinycsharp::TokenKind::kTGreaterThan, ">"},
            {tinycsharp::TokenKind::kTIdent, "ViewData"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTNew, "new"},
            {tinycsharp::TokenKind::kTIdent, "Dictionary"},
            {tinycsharp::TokenKind::kTLessThan, "<"},
            {tinycsharp::TokenKind::kTType, "string"},
            {tinycsharp::TokenKind::kTComma, ","},
            {tinycsharp::TokenKind::kTType, "object"},
            {tinycsharp::TokenKind::kTGreaterThan, ">"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "object"},
            {tinycsharp::TokenKind::kTIdent, "Value"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTType, "bool"},
            {tinycsharp::TokenKind::kTIdent, "KeepAlive"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTGet, "get"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTSet, "set"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTDocComment, "/// <summary>"},
            {tinycsharp::TokenKind::kTDocComment, "/// Add a view data to the viewData collection. Used with HttpResponder that returns HTML views"},
            {tinycsharp::TokenKind::kTDocComment, "/// </summary>"},
            {tinycsharp::TokenKind::kTDocComment, "/// <param name=\"key\">key of the data</param>"},
            {tinycsharp::TokenKind::kTDocComment, "/// <param name=\"value\">object that represents the value</param>"},
            {tinycsharp::TokenKind::kTDocComment, "/// <returns></returns>"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTIdent, "HttpResponder"},
            {tinycsharp::TokenKind::kTIdent, "With"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTType, "string"},
            {tinycsharp::TokenKind::kTIdent, "key"},
            {tinycsharp::TokenKind::kTComma, ","},
            {tinycsharp::TokenKind::kTType, "object"},
            {tinycsharp::TokenKind::kTIdent, "value"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTLCurly, "{"},
            {tinycsharp::TokenKind::kTIf, "if"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTNot, "!"},
            {tinycsharp::TokenKind::kTIdent, "ViewData"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "ContainsKey"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTIdent, "key"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTIdent, "ViewData"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Add"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTIdent, "key"},
            {tinycsharp::TokenKind::kTComma, ","},
            {tinycsharp::TokenKind::kTIdent, "value"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTReturn, "return"},
            {tinycsharp::TokenKind::kTThis, "this"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTPublic, "public"},
            {tinycsharp::TokenKind::kTIdent, "HttpResponder"},
            {tinycsharp::TokenKind::kTIdent, "DataToList"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTLCurly, "{"},

            {tinycsharp::TokenKind::kTVar, "var"},
            {tinycsharp::TokenKind::kTIdent, "list"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTAwait, "await"},
            {tinycsharp::TokenKind::kTIdent, "_db"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "ToListAsync"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},

            {tinycsharp::TokenKind::kTVar, "var"},
            {tinycsharp::TokenKind::kTIdent, "newList"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTIdent, "list"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Select"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTIdent, "x"},
            {tinycsharp::TokenKind::kTArrow, "=>"},
            {tinycsharp::TokenKind::kTNew, "new"},
            {tinycsharp::TokenKind::kTLCurly, "{"},

            {tinycsharp::TokenKind::kTIdent, "Key"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTIdent, "x"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Key"},
            {tinycsharp::TokenKind::kTComma, ","},

            {tinycsharp::TokenKind::kTIdent, "Value"},
            {tinycsharp::TokenKind::kTAssign, "="},
            {tinycsharp::TokenKind::kTIdent, "x"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "Value"},
            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTDot, "."},
            {tinycsharp::TokenKind::kTIdent, "ToList"},
            {tinycsharp::TokenKind::kTLParen, "("},
            {tinycsharp::TokenKind::kTRParen, ")"},
            {tinycsharp::TokenKind::kTSemiColon, ";"},
            {tinycsharp::TokenKind::kTRCurly, "}"},

            {tinycsharp::TokenKind::kTRCurly, "}"},
            {tinycsharp::TokenKind::kTRCurly, "}"}};

        tinycsharp::Lexer lexer(actual_csharp_code);

        for (const auto &expected : expected_tokens)
        {
            SCOPED_TRACE("Testing token with expected lexeme: " + expected.lexeme);
            auto actual_token = lexer.Lex();

            EXPECT_EQ(actual_token.kind, expected.kind);
            EXPECT_EQ(actual_token.lexeme, expected.lexeme);
        }

        auto eof_token = lexer.Lex();
        EXPECT_EQ(eof_token.kind, tinycsharp::TokenKind::kTEof);
        EXPECT_EQ(eof_token.lexeme, "");
    }

    TEST_F(LexerTest, ShouldThrowInvalidArgumentForEmptyInput)
    {
        EXPECT_THROW(tinycsharp::Lexer lexer{""}, std::invalid_argument);
    }

    TEST_F(LexerTest, ShouldObtainCorrectLineAndColumnInfoForTokens)
    {
        std::string input = "var x = 10;";

        struct ExpectedToken
        {
            tinycsharp::TokenKind kind;
            std::string lexeme;
            int line;
            int column;
        };

        const std::vector<ExpectedToken> expected_tokens = {
            {tinycsharp::TokenKind::kTVar, "var", 1, 1},
            {tinycsharp::TokenKind::kTIdent, "x", 1, 5},
            {tinycsharp::TokenKind::kTAssign, "=", 1, 7},
            {tinycsharp::TokenKind::kTNLiteral, "10", 1, 9},
            {tinycsharp::TokenKind::kTSemiColon, ";", 1, 11}};

        tinycsharp::Lexer lexer{input};

        for (const auto &expected : expected_tokens)
        {
            SCOPED_TRACE("Testing token with expected lexeme: " + expected.lexeme);
            auto actual_token = lexer.Lex();
            EXPECT_EQ(actual_token.kind, expected.kind);
            EXPECT_EQ(actual_token.lexeme, expected.lexeme);
            EXPECT_EQ(actual_token.line, expected.line);
            EXPECT_EQ(actual_token.column, expected.column);
        }
    }

}
