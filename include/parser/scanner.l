%{
#include "parser/token.h"

#define YY_DECL int my_scan(yyscan_t yyscanner, STREAM::token &token)

#include "parser/parser.h"

%}
 
%option reentrant
%option noyywrap
%option nounput
 
%x SINGLE_QUOTED
%x DOUBLE_QUOTED
 
%% 
"create"                {return K_CREATE;}
"insert"                {return K_INSERT;}
"into"	                {return K_INTO;}
"values"		        {return K_VALUES;}
"stream"    	      	{return K_STREAM;}
"view"    		        {return K_VIEW;}
"double" 		        {return K_DOUBLE;}
"real"   		        {return K_DOUBLE;}
"integer"	         	{return K_INTEGER;}
"text"			        {return K_STRING;}
"blob"			        {return K_BLOB;}
"geometry" 		        {return K_GEOMETRY;}
"as"			        {return K_AS;}
"join"                  {return K_JOIN;}
"on"                    {return K_ON;}
"select"		        {return K_SELECT;}
"from"			        {return K_FROM;}
"max"		            {return K_MAX;}
"min"		            {return K_MIN;}
"="		            	{return K_EQUAL;}
">"		            	{return K_GREATER_THAN;}
">="		            {return K_GRATER_THAN_EQUAL;}
"<"		            	{return K_LESSER_THAN;}
"<="		            {return K_LESSER_THAN_EQUAL;}
"!="		            {return K_NOT_EQUAL;}
"and"		            {return K_AND;}
"or"		            {return K_OR;}
"slide"                 {return K_SLIDE;}
"tilt"                  {return K_TILT;}
"way"	         	    {return K_WAY;}
"session"	         	{return K_SESSION;}
"jumping"	         	{return K_JUMPING;}
"area"	         	    {return K_AREA;}
"ms"                    {return K_MS;}
"m"                     {return K_M;}
[a-z_]+[0-9]*		    {token.stringValue = new std::string(yytext); return IDENTIFIER;}
\[                      {return K_OPEN_SQUARE_BRACKET;}
\]                      {return K_CLOSE_SQUARE_BRACKET;}
\(	    		        {return K_OPEN_BRACKET;}
\)	    		        {return K_CLOSE_BRACKET;}
,		                {return K_COMA;}
;			            {return K_SEMICOLON;}
\.                      {return K_POINT;}
[0-9]+"."[0-9]*    	    {token.doubleValue = new double; *(token.doubleValue) = std::stod(yytext); return V_DOUBLE;}
[0-9]+	 		        {token.longValue = new long; *(token.longValue) = std::stol(yytext); return V_LONG;}
\'[a-z_0-9() \.,]*\'	{token.stringValue = new std::string(yytext); return V_STRING;}
\"[a-z_0-9() \.,]*\"	{token.stringValue = new std::string(yytext); return V_STRING;}
[ \t\r\n]               {}
.	                    {}
%%