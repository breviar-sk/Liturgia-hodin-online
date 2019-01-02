/*********************************************************/
/*                                                       */
/* common.h                                              */
/* (c)1999-2019 | Juraj Vidéky | videky@breviar.sk       */
/*                                                       */
/* description | new core basic define's                 */
/*                                                       */
/*********************************************************/

#include "vstudio.h"

#ifndef __COMMON_H_
#define __COMMON_H_

#define Q_UNUSED(arg) (void)arg;

#define CHAR_EMPTY 0

#define SMALL 160
#define VERY_SMALL 16

// navratova hodnota funkcii
#define NO_RESULT 2
#define FAILURE 1
#define SUCCESS 0

// true -- false
#define TRUE  1
#define FALSE 0
#define ANO   1
#define NIE   0
#define CIASTOCNE 2

#undef YES
#undef NO
#define YES 1
#define NO  0

#define MAX_STR           1024 // max string length

#define GLOBAL_OPTION_NULL  -1 // undefined value for global option

// div, mod: delenie pre short int
#define DIV	/
#define MOD	%

// juliansky datum, funkcia juliansky_datum, dane synonymum JD
#define	JD	juliansky_datum

#define	ROK_1968		1968
#define	JUL_DATE_0_JAN_1968	2439856L // juliansky datum pre 0. januar 1968

#define	POCET_DNI_V_ROKU	365

#pragma region Anchors & special characters

// keyword (anchor) begin + end
#define CHAR_KEYWORD_BEGIN   '{'
#define CHAR_KEYWORD_END     '}'
#define CHAR_KEYWORD_DIVIDER ':'

// underscore '_' used as placeholder for non-breaking space (it will be exported as HTML_NONBREAKING_SPACE == "&nbsp;" defined in mydefs.h) 
#define CHAR_NONBREAKING_SPACE '_'

// special characters in prayer texts (some of them to be removed for blind-friendly version)
#define CHAR_SPACE             ' '
#define CHAR_PRAYER_ASTERISK   '*'
#define CHAR_PRAYER_CROSS      L'\x2020' /*†*/ // used as flexa | U+2020 DAGGER
#define CHAR_PRAYER_CROSS_ALT  '+'
#define CHAR_PRAYER_TRIANGLE   L'\x25B3' /*△*/ // 'uppercase delta': Δ (used for doxology) | U+25B3 WHITE UP-POINTING TRIANGLE
#define CHAR_EM_DASH           L'\x2014' /*—*/ // em dash | U+2014
#define CHAR_EN_DASH           L'\x2013' /*–*/ // en dash | U+2013

// include parameters
#define INCLUDE_BEGIN   "BEGIN" // zaciatok
#define INCLUDE_END     "END"   // koniec

#pragma endregion

#pragma region Week days

// week days
#define DEN_NEDELA      0
#define DEN_PONDELOK    1
#define DEN_UTOROK      2
#define DEN_STREDA      3
#define DEN_STVRTOK     4
#define DEN_PIATOK      5
#define DEN_SOBOTA      6
#define DEN_UNKNOWN     7
// number of week  days
#define POCET_DNI		7

// all days
#define VSETKY_DNI   32
#define STR_VSETKY_DNI  "*"

#pragma endregion

#pragma region Months

// months
#define MES_JAN 0
#define MES_FEB 1
#define MES_MAR 2
#define MES_APR 3
#define MES_MAY 4
#define MES_MAJ 4
#define MES_JUN 5
#define MES_JUL 6
#define MES_AUG 7
#define MES_SEP 8
#define MES_OCT 9
#define MES_OKT 9
#define MES_NOV 10
#define MES_DEC 11
#define UNKNOWN_MESIAC	12
// number of months
#define POCET_MESIACOV	12

// all months
#define VSETKY_MESIACE	13
#define STR_VSETKY_MESIACE  "*"

#pragma endregion

#pragma region string constants

#define STR_EN_DASH "–"
#define STR_EN_DASH_WITH_SPACES " – "
#define STR_EM_DASH "—"
#define STR_SPACE " "
#define STR_VERTICAL_BAR "|"
#define STR_VERTICAL_BAR_WITH_SPACES " | "
#define STR_ASTERISK "*"
#define STR_CROSS "†"
#define STR_SLASH "/"
#define STR_UNDERSCORE "_"
#define STR_DOT "."

#pragma endregion

#pragma region HTML string constants

#define HTML_FORM_INPUT_SUBMIT   HTML_FORM_INPUT_DIV_BEGIN "<input type=\"submit\" class=\"button\""
#define HTML_FORM_INPUT_SUBMIT_PRAYER   HTML_FORM_INPUT_DIV_BEGIN "<input type=\"submit\" class=\"button-prayer\""
#define HTML_FORM_INPUT_RESET    HTML_FORM_INPUT_DIV_BEGIN "<input type=\"reset\" class=\"reset\""
#define HTML_FORM_INPUT_RADIO    HTML_FORM_INPUT_DIV_BEGIN "<input type=\"radio\" class=\"radio\""
#define HTML_FORM_INPUT_TEXT     HTML_FORM_INPUT_DIV_BEGIN "<input type=\"text\" class=\"text\""
#define HTML_FORM_INPUT_TEXT_ROK HTML_FORM_INPUT_DIV_BEGIN "<input type=\"text\" class=\"text\" size=\"4\" maxlength=\"4\" style=\"font-family:monospace\""
#define HTML_FORM_INPUT_CHECKBOX HTML_FORM_INPUT_DIV_BEGIN "<input type=\"checkbox\" class=\"checkbox\""

// buttons (0. level: pre predošlý/nasledovný; 1. level: button "dnes"; 2. level: použité pre menej dôležité buttony)
#define HTML_FORM_INPUT_SUBMIT0  HTML_FORM_INPUT_DIV_BEGIN "<input type=\"submit\" class=\"button0\""
#define HTML_FORM_INPUT_RESET0   HTML_FORM_INPUT_DIV_BEGIN "<input type=\"reset\" class=\"reset0\""
#define HTML_FORM_INPUT_SUBMIT1  HTML_FORM_INPUT_DIV_BEGIN "<input type=\"submit\" class=\"button1\""
#define HTML_FORM_INPUT_RESET1   HTML_FORM_INPUT_DIV_BEGIN "<input type=\"reset\" class=\"reset1\""
#define HTML_FORM_INPUT_SUBMIT2  HTML_FORM_INPUT_DIV_BEGIN "<input type=\"submit\" class=\"button2\""
#define HTML_FORM_INPUT_RESET2   HTML_FORM_INPUT_DIV_BEGIN "<input type=\"reset\" class=\"reset2\""
#define HTML_FORM_INPUT_HIDDEN   HTML_FORM_INPUT_DIV_BEGIN "<input type=\"hidden\""

#define HTML_FORM_INPUT_END      HTML_EMPTY_TAG_END "" HTML_FORM_INPUT_DIV_END

// wrapping <input ... /> into <div>...</div>
#define HTML_FORM_INPUT_DIV_BEGIN HTML_DIV_INLINE
#define HTML_FORM_INPUT_DIV_END   HTML_DIV_END

#define HTML_FORM_SELECT "<select "

#define HTML_HR            "<hr/>"

#define HTML_EMPTY_TAG_END " />"

#define HTML_FORM_METHOD_GET     "<form action=\"%s\" method=\"get\">\n"
#define HTML_FORM_METHOD_POST    "<form action=\"%s\" method=\"post\">\n"

#define HTML_LINK_RED    "a class=\"red\""
#define HTML_LINK_NORMAL "a"
#define HTML_LINK_CLASS_B "a class=\""
#define HTML_LINK_CLASS_E "\""

#define HTML_TARGET_BLANK " target=\"_blank\" "
#define HTML_TARGET_TOP " target=\"_top\" "

#define HTML_NONBREAKING_SPACE "&nbsp;"
#define HTML_NONBREAKING_SPACE_LONG "&nbsp;&nbsp;&nbsp;"
#define HTML_LINE_BREAK "<br/>\n" // always followed by real line-break
#define HTML_CRLF_LINE_BREAK "\n<br/>"
#define HTML_NONBREAKING_SPACE_LOOONG "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
#define HTML_SLASH_SPACE_LOONG_LINE_BREAK (HTML_NONBREAKING_SPACE "" STR_SLASH "" HTML_NONBREAKING_SPACE "" HTML_LINE_BREAK "" HTML_NONBREAKING_SPACE_LOOONG)
#define HTML_SLASH_SPACE_LOONG (HTML_NONBREAKING_SPACE "" STR_SLASH "" HTML_NONBREAKING_SPACE)

#define HTML_P_BEGIN                "<p>"
#define HTML_P_END                  "</p>"

#define HTML_P_RUBRIC               "<p " HTML_CLASS_RUBRIC ">"

#define HTML_P_CENTER               "<p " HTML_CLASS_CENTER ">"
#define HTML_P_CENTER_SMALL         "<p " HTML_CLASS_SMALL_CENTER ">"
#define HTML_P_INLINE               "<p " HTML_CLASS_INLINE ">"

#define HTML_P_VERSE_START          "<p class=\"verse start\">"
#define HTML_P_VERSE_CONT           "<p class=\"verse cont\">"

#define HTML_A_HREF_BEGIN           "<a href="
#define HTML_A_NAME_BEGIN           "<a name="
#define HTML_A_END                  "</a>"

#define HTML_DIV_BEGIN              "<div>"
#define HTML_DIV_END                "</div>"

#define HTML_DIV_CENTER             "<div " HTML_CLASS_CENTER ">"
#define HTML_DIV_INLINE             "<div " HTML_CLASS_INLINE ">"
#define HTML_DIV_RUBRIC             "<div " HTML_CLASS_RUBRIC ">"

#define HTML_DIV_SMALL_INLINE       "div class=\"small inline\""
#define HTML_DIV_SMALL              "div class=\"small\""
#define HTML_DIV_RED_SMALL          "div class=\"redsmall\""
#define HTML_DIV_RED_SUBTITLE       "div class=\"redsubtitle\""

#define HTML_DIV_PSALM              "div class=\"psalm\""
#define HTML_DIV_PSALM_INDENT       "div class=\"psalm-indent\""

// TTS navigation
#define HTML_DIV_TTS_HEADING        "div class=\"tts_heading\""
#define HTML_DIV_TTS_SECTION        "div class=\"tts_section\""

// TTS special - pause (for special characters)
#define HTML_SPAN_TTS_PAUSE_RED     "span class=\"tts_pause red\""
#define HTML_SPAN_TTS_PAUSE         "span class=\"tts_pause\""
#define HTML_SPAN_TTS_PAUSE_SHORT   "span class=\"tts_pause_short\""

// HTML tables defined using DIVs
#define HTML_TABLE			        "div class=\"table\"" // "table"
#define HTML_TABLE_LEFT             "div class=\"table-left\"" // "table" left-aligned
#define HTML_TABLE_CAPTION	        "div class=\"table-caption\"" // "th"
#define HTML_TABLE_ROW		        "div class=\"table-row\"" // "tr"
#define HTML_TABLE_CELL		        "div class=\"table-cell\"" // "td"
#define HTML_TABLE_CELL_CENTER      "div class=\"table-cell center\""
#define HTML_TABLE_CELL_BORDER      "div class=\"table-cell-bordered\"" // "td" with borders
#define HTML_TABLE_CELL_3_COLUMNS   "div class=\"table-cell-3-columns\"" // "td" for tables with 3 columns
#define HTML_TABLE_CELL_VALIGN_TOP  "div class=\"table-cell-valign-top\""

#define HTML_TABLE_CELL_PRAYER      (isGlobalOption(OPT_2_HTML_EXPORT, BIT_OPT_2_BUTTONY_USPORNE) ? HTML_TABLE_CELL_3_COLUMNS : HTML_TABLE_CELL)

#define HTML_TABLE_END		        HTML_DIV_END "" HTML_COMMENT_BEGIN "table" HTML_COMMENT_END // "</table>"
#define HTML_TABLE_CAPTION_END	    HTML_DIV_END "" HTML_COMMENT_BEGIN "caption" HTML_COMMENT_END // "</th>"
#define HTML_TABLE_ROW_END	        HTML_DIV_END "" HTML_COMMENT_BEGIN "row" HTML_COMMENT_END // "</tr>"
#define HTML_TABLE_CELL_END	        HTML_DIV_END "" HTML_COMMENT_BEGIN "cell" HTML_COMMENT_END // "</td>"

#define HTML_TABLE_CELL_BORDER_END	HTML_TABLE_CELL_END

#define HTML_CLASS                  "class"

#define HTML_SPAN                   "span"

#define HTML_SPAN_CLASS             HTML_SPAN " " HTML_CLASS "=" // without quote

#define HTML_SPAN_END               "</" HTML_SPAN ">"

#define HTML_CLASS_NAME_NORMAL        "normal"
#define HTML_CLASS_NAME_ITALIC        "it"
#define HTML_CLASS_NAME_BOLD          "bold"
#define HTML_CLASS_NAME_BOLD_IT       "boldit"
#define HTML_CLASS_NAME_RED_TITLE     "redtitle"
#define HTML_CLASS_NAME_RED           "red"
#define HTML_CLASS_NAME_RED_BOLD      "redbold"
#define HTML_CLASS_NAME_BLUE          "blue"
#define HTML_CLASS_NAME_BLUE_BOLD     "bluebold"
#define HTML_CLASS_NAME_RED_SMALL     "redsmall"
#define HTML_CLASS_NAME_RED_SUBTITLE  "redsubtitle"
#define HTML_CLASS_NAME_SMALL         "small"
#define HTML_CLASS_NAME_SMALLCAPS     "smallcaps"
#define HTML_CLASS_NAME_EXPLAIN       "explain"
#define HTML_CLASS_NAME_PARAMETER     "parameter"
#define HTML_CLASS_NAME_VALUE         "value"
#define HTML_CLASS_NAME_XS_CAPS       "xsmallcaps"
#define HTML_CLASS_NAME_HIDDEN        "hidden"
#define HTML_CLASS_NAME_UPPERCASE     "uppercase"
#define HTML_CLASS_NAME_TEXTNOTE      "textnote"

#define HTML_SPAN_NORMAL          HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_NORMAL "\""
#define HTML_SPAN_ITALIC          HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_ITALIC "\""
#define HTML_SPAN_BOLD            HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_BOLD "\""
#define HTML_SPAN_BOLD_IT         HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_BOLD_IT "\""
#define HTML_SPAN_RED_TITLE       HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_RED_TITLE "\""
#define HTML_SPAN_RED             HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_RED "\""
#define HTML_SPAN_RED_BOLD        HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_RED_BOLD "\""
#define HTML_SPAN_BLUE            HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_BLUE "\""
#define HTML_SPAN_BLUE_BOLD       HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_BLUE_BOLD "\""
#define HTML_SPAN_RED_SMALL       HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_RED_SMALL "\""
#define HTML_SPAN_RED_SUBTITLE    HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_RED_SUBTITLE "\""
#define HTML_SPAN_SMALL           HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_SMALL "\""
#define HTML_SPAN_SMALLCAPS       HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_SMALLCAPS "\""
#define HTML_SPAN_EXPLAIN         HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_EXPLAIN "\""
#define HTML_SPAN_PARAMETER       HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_PARAMETER "\""
#define HTML_SPAN_VALUE           HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_VALUE "\""
#define HTML_SPAN_XS_CAPS         HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_XS_CAPS "\""
#define HTML_SPAN_HIDDEN          HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_HIDDEN "\""
#define HTML_SPAN_UPPERCASE       HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_UPPERCASE "\""
#define HTML_SPAN_TEXTNOTE        HTML_SPAN_CLASS "\"" HTML_CLASS_NAME_TEXTNOTE "\""

#define HTML_CLASS_CALENDAR       "class=\"calendar\""
#define HTML_CLASS_SMALL          "class=\"small\""

#define HTML_CALENDAR_HEADING       "span class=\"calendar heading\""
#define HTML_CALENDAR_DAYS          "span class=\"calendar day_name\""
#define HTML_CALENDAR_TODAY_SUNDAY  "span class=\"calendar today bold\""
#define HTML_CALENDAR_TODAY         "span class=\"calendar today\""

#define HTML_CLASS_NAME_CALENDAR_TODAY_SUNDAY "calendar today bold"
#define HTML_CLASS_NAME_CALENDAR_TODAY        "calendar today"
#define HTML_CLASS_NAME_CALENDAR_SUNDAY       "calendar day bold"
#define HTML_CLASS_NAME_CALENDAR_DAY          "calendar day"

#define HTML_SPAN_TOOLTIP           HTML_SPAN " " "title=\"%s\"" // obsahuje %s
#define HTML_SPAN_BOLD_TOOLTIP      HTML_SPAN " " "class=\"bold\" title=\"%s\"" // obsahuje %s
#define HTML_SPAN_NORMAL_TOOLTIP    HTML_SPAN " " "class=\"normal\" title=\"%s\"" // obsahuje %s

#define HTML_SUP_RED                "sup class=\"red\""

#define HTML_CLASS_QUIET            "class=\"quiet\"" // for <a>

#define HTML_CLASS_WITHOUT_BORDER   "class=\"without-border\""

#define HTML_CLASS_BLUE             "class=\"blue\""
#define HTML_CLASS_BOLD_IT          "class=\"boldit\""
#define HTML_CLASS_LEVEL1           "class=\"level1\""
#define HTML_CLASS_TT               "class=\"tt\""
#define HTML_CLASS_BUTTON           "class=\"button\""
#define HTML_CLASS_BUTTON_PRAYER    "class=\"button-prayer\""
#define HTML_CLASS_SMALL            "class=\"small\""
#define HTML_CLASS_SMALL_CENTER     "class=\"small center\""
#define HTML_CLASS_INLINE           "class=\"inline\""
#define HTML_CLASS_CENTER           "class=\"center\""

#define HTML_CLASS_RUBRIC           "class=\"rubric\""

#define HTML_VALIGN_MIDDLE          "valign=\"middle\""
#define HTML_VALIGN_TOP             "valign=\"top\""
#define HTML_VALIGN_BASE            "valign=\"baseline\""

#define HTML_BUTTON_BEGIN	        "<button type=\"button\" " HTML_CLASS_BUTTON ">" // wrapping <a> element to look like button
#define HTML_BUTTON_PRAYER_BEGIN	"<button type=\"button\" " HTML_CLASS_BUTTON_PRAYER ">" // wrapping <a> element to look like button
#define HTML_BUTTON_END		        "</button>"

#define HTML_AMPERSAND              "&amp;"

#define HTML_COMMENT_BEGIN		    "<!--"
#define HTML_COMMENT_END		    "-->"
#define HTML_FONT_SIZE_FARBA	    "80%%"

#define HTML_LEFT_ARROW_CLASSIC		"&larr;"
#define HTML_RIGHT_ARROW_CLASSIC	"&rarr;"
#define HTML_UP_ARROW_CLASSIC		"&uarr;"
#define HTML_DOWN_ARROW_CLASSIC		"&darr;"

#define HTML_LEFT_ARROW			    "&laquo;"
#define HTML_RIGHT_ARROW		    "&raquo;"

#define HTML_LEFT_ARROW_WIDE	    "&nbsp;&laquo;&nbsp;"
#define HTML_RIGHT_ARROW_WIDE	    "&nbsp;&raquo;&nbsp;"

#define HTML_LINK_CALL1             "%s?%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s"
#define HTML_LINK_CALL2             "%s?%s=%s" HTML_AMPERSAND "%s=%s" HTML_AMPERSAND "%s=%d" HTML_AMPERSAND "%s=%d%s"
#define HTML_LINK_CALL3             "%s?%s=%s" HTML_AMPERSAND "%s=%s%s"
#define HTML_LINK_CALL_PARAM        HTML_AMPERSAND "%s=%s"

#define HTML_LEFT_ARROW_SINGLE	    "&lsaquo;"
#define HTML_RIGHT_ARROW_SINGLE	    "&rsaquo;"

#define HTML_LEFT_ARROW_HUGE	    "&lsaquo;&laquo;"
#define HTML_RIGHT_ARROW_HUGE	    "&raquo;&rsaquo;"

#pragma endregion

#endif // __COMMON_H_

