#ifndef PARSE_HPP
# define PARSE_HPP

typedef union
{
    /// Temporary data returned from tokens (lexer) and productions (parser)
    int num;                    /// Stored by lexer (YYINT) and inter-production data transfer
    WCHAR ident[MAXIDENT];      /// Stored by lexer (YYIDENT)
    LPWSTR str;                 /// Tracked pointer with quotes stripped (YYSTRING)

    EnumsList el;               /// Inter-production data transfer
    ParamsList pl;              /// Inter-production data transfer
    StartTag st;                /// Inter-production data transfer
    COLORREF cr;                /// Inter-production data transfer
    HANDLE h;                   /// Inter-production data transfer

    ValueNode* pvn;             /// NT_ValueNode
    PropValPairNode* ppvpn;     /// NT_PropValPairNode
    ElementNode* pen;           /// NT_ElementNode
    AttribNode* pan;            /// NT_AttribNode
    RuleNode* prn;              /// NT_RuleNode
    SheetNode* psn;             /// NT_SheetNode
} YYSTYPE;
# define	YYIDENT	257
# define	YYINT	258
# define	YYSTRING	259
# define	YYSHEET	260
# define	YYSHEETREF	261
# define	YYRECT	262
# define	YYPOINT	263
# define	YYRGB	264
# define	YYARGB	265
# define	YYGRADIENT	266
# define	YYGRAPHIC	267
# define	YYDFC	268
# define	YYDTB	269
# define	YYTRUE	270
# define	YYFALSE	271
# define	YYRESID	272
# define	YYATOM	273
# define	YYRCSTR	274
# define	YYRCBMP	275
# define	YYRCINT	276
# define	YYRCCHAR	277
# define	YYPT	278
# define	YYRP	279
# define	YYSYSMETRIC	280
# define	YYSYSMETRICSTR	281
# define	YYHANDLEMAP	282


extern YYSTYPE yylval;

#endif /* not PARSE_HPP */
