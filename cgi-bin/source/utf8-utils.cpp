/**********************************************************/
/*                                                        */
/* utf8-utils.cpp                                         */
/* (c)2014 | Juraj Vidéky, Richard Královič               */
/*                                                        */
/* description | utilities for UTF-8 (Unicode) encoding   */
/*               (string manipulation, etc.)              */
/*                                                        */
/**********************************************************/

#include "utf8-utils.h"

int WcharToUppercase(int w) {
  if (w >= 'a' && w <= 'z') {
    return w - 'a' + 'A';
  }
  switch (w) {
    case L'\x00E0'/*à*/: return L'\x00C0'/*À*/;
    case L'\x00E1'/*á*/: return L'\x00C1'/*Á*/;
    case L'\x00E2'/*â*/: return L'\x00C2'/*Â*/;
    case L'\x00E3'/*ã*/: return L'\x00C3'/*Ã*/;
    case L'\x00E4'/*ä*/: return L'\x00C4'/*Ä*/;
    case L'\x00E5'/*å*/: return L'\x00C5'/*Å*/;
    case L'\x00E6'/*æ*/: return L'\x00C6'/*Æ*/;
    case L'\x00E7'/*ç*/: return L'\x00C7'/*Ç*/;
    case L'\x00E8'/*è*/: return L'\x00C8'/*È*/;
    case L'\x00E9'/*é*/: return L'\x00C9'/*É*/;
    case L'\x00EA'/*ê*/: return L'\x00CA'/*Ê*/;
    case L'\x00EB'/*ë*/: return L'\x00CB'/*Ë*/;
    case L'\x00EC'/*ì*/: return L'\x00CC'/*Ì*/;
    case L'\x00ED'/*í*/: return L'\x00CD'/*Í*/;
    case L'\x00EE'/*î*/: return L'\x00CE'/*Î*/;
    case L'\x00EF'/*ï*/: return L'\x00CF'/*Ï*/;
    case L'\x00F0'/*ð*/: return L'\x00D0'/*Ð*/;
    case L'\x00F1'/*ñ*/: return L'\x00D1'/*Ñ*/;
    case L'\x00F2'/*ò*/: return L'\x00D2'/*Ò*/;
    case L'\x00F3'/*ó*/: return L'\x00D3'/*Ó*/;
    case L'\x00F4'/*ô*/: return L'\x00D4'/*Ô*/;
    case L'\x00F5'/*õ*/: return L'\x00D5'/*Õ*/;
    case L'\x00F6'/*ö*/: return L'\x00D6'/*Ö*/;
    case L'\x00F8'/*ø*/: return L'\x00D8'/*Ø*/;
    case L'\x00F9'/*ù*/: return L'\x00D9'/*Ù*/;
    case L'\x00FA'/*ú*/: return L'\x00DA'/*Ú*/;
    case L'\x00FB'/*û*/: return L'\x00DB'/*Û*/;
    case L'\x00FC'/*ü*/: return L'\x00DC'/*Ü*/;
    case L'\x00FD'/*ý*/: return L'\x00DD'/*Ý*/;
    case L'\x00FE'/*þ*/: return L'\x00DE'/*Þ*/;
    case L'\x00FF'/*ÿ*/: return L'\x0178'/*Ÿ*/;
    case L'\x0101'/*ā*/: return L'\x0100'/*Ā*/;
    case L'\x0103'/*ă*/: return L'\x0102'/*Ă*/;
    case L'\x0105'/*ą*/: return L'\x0104'/*Ą*/;
    case L'\x0107'/*ć*/: return L'\x0106'/*Ć*/;
    case L'\x0109'/*ĉ*/: return L'\x0108'/*Ĉ*/;
    case L'\x010B'/*ċ*/: return L'\x010A'/*Ċ*/;
    case L'\x010D'/*č*/: return L'\x010C'/*Č*/;
    case L'\x010F'/*ď*/: return L'\x010E'/*Ď*/;
    case L'\x0111'/*đ*/: return L'\x0110'/*Đ*/;
    case L'\x0113'/*ē*/: return L'\x0112'/*Ē*/;
    case L'\x0115'/*ĕ*/: return L'\x0114'/*Ĕ*/;
    case L'\x0117'/*ė*/: return L'\x0116'/*Ė*/;
    case L'\x0119'/*ę*/: return L'\x0118'/*Ę*/;
    case L'\x011B'/*ě*/: return L'\x011A'/*Ě*/;
    case L'\x011D'/*ĝ*/: return L'\x011C'/*Ĝ*/;
    case L'\x011F'/*ğ*/: return L'\x011E'/*Ğ*/;
    case L'\x0121'/*ġ*/: return L'\x0120'/*Ġ*/;
    case L'\x0123'/*ģ*/: return L'\x0122'/*Ģ*/;
    case L'\x0125'/*ĥ*/: return L'\x0124'/*Ĥ*/;
    case L'\x0127'/*ħ*/: return L'\x0126'/*Ħ*/;
    case L'\x0129'/*ĩ*/: return L'\x0128'/*Ĩ*/;
    case L'\x012B'/*ī*/: return L'\x012A'/*Ī*/;
    case L'\x012D'/*ĭ*/: return L'\x012C'/*Ĭ*/;
    case L'\x012F'/*į*/: return L'\x012E'/*Į*/;
    case L'\x0131'/*ı*/: return L'\x0049'/*I*/;
    case L'\x0133'/*ĳ*/: return L'\x0132'/*Ĳ*/;
    case L'\x0135'/*ĵ*/: return L'\x0134'/*Ĵ*/;
    case L'\x0137'/*ķ*/: return L'\x0136'/*Ķ*/;
    case L'\x013A'/*ĺ*/: return L'\x0139'/*Ĺ*/;
    case L'\x013C'/*ļ*/: return L'\x013B'/*Ļ*/;
    case L'\x013E'/*ľ*/: return L'\x013D'/*Ľ*/;
    case L'\x0140'/*ŀ*/: return L'\x013F'/*Ŀ*/;
    case L'\x0142'/*ł*/: return L'\x0141'/*Ł*/;
    case L'\x0144'/*ń*/: return L'\x0143'/*Ń*/;
    case L'\x0146'/*ņ*/: return L'\x0145'/*Ņ*/;
    case L'\x0148'/*ň*/: return L'\x0147'/*Ň*/;
    case L'\x014B'/*ŋ*/: return L'\x014A'/*Ŋ*/;
    case L'\x014D'/*ō*/: return L'\x014C'/*Ō*/;
    case L'\x014F'/*ŏ*/: return L'\x014E'/*Ŏ*/;
    case L'\x0151'/*ő*/: return L'\x0150'/*Ő*/;
    case L'\x0153'/*œ*/: return L'\x0152'/*Œ*/;
    case L'\x0155'/*ŕ*/: return L'\x0154'/*Ŕ*/;
    case L'\x0157'/*ŗ*/: return L'\x0156'/*Ŗ*/;
    case L'\x0159'/*ř*/: return L'\x0158'/*Ř*/;
    case L'\x015B'/*ś*/: return L'\x015A'/*Ś*/;
    case L'\x015D'/*ŝ*/: return L'\x015C'/*Ŝ*/;
    case L'\x015F'/*ş*/: return L'\x015E'/*Ş*/;
    case L'\x0161'/*š*/: return L'\x0160'/*Š*/;
    case L'\x0163'/*ţ*/: return L'\x0162'/*Ţ*/;
    case L'\x0165'/*ť*/: return L'\x0164'/*Ť*/;
    case L'\x0167'/*ŧ*/: return L'\x0166'/*Ŧ*/;
    case L'\x0169'/*ũ*/: return L'\x0168'/*Ũ*/;
    case L'\x016B'/*ū*/: return L'\x016A'/*Ū*/;
    case L'\x016D'/*ŭ*/: return L'\x016C'/*Ŭ*/;
    case L'\x016F'/*ů*/: return L'\x016E'/*Ů*/;
    case L'\x0171'/*ű*/: return L'\x0170'/*Ű*/;
    case L'\x0173'/*ų*/: return L'\x0172'/*Ų*/;
    case L'\x0175'/*ŵ*/: return L'\x0174'/*Ŵ*/;
    case L'\x0177'/*ŷ*/: return L'\x0176'/*Ŷ*/;
    case L'\x017A'/*ź*/: return L'\x0179'/*Ź*/;
    case L'\x017C'/*ż*/: return L'\x017B'/*Ż*/;
    case L'\x017E'/*ž*/: return L'\x017D'/*Ž*/;
    case L'\x0183'/*ƃ*/: return L'\x0182'/*Ƃ*/;
    case L'\x0185'/*ƅ*/: return L'\x0184'/*Ƅ*/;
    case L'\x0188'/*ƈ*/: return L'\x0187'/*Ƈ*/;
    case L'\x018C'/*ƌ*/: return L'\x018B'/*Ƌ*/;
    case L'\x0192'/*ƒ*/: return L'\x0191'/*Ƒ*/;
    case L'\x0199'/*ƙ*/: return L'\x0198'/*Ƙ*/;
    case L'\x01A1'/*ơ*/: return L'\x01A0'/*Ơ*/;
    case L'\x01A3'/*ƣ*/: return L'\x01A2'/*Ƣ*/;
    case L'\x01A5'/*ƥ*/: return L'\x01A4'/*Ƥ*/;
    case L'\x01A8'/*ƨ*/: return L'\x01A7'/*Ƨ*/;
    case L'\x01AD'/*ƭ*/: return L'\x01AC'/*Ƭ*/;
    case L'\x01B0'/*ư*/: return L'\x01AF'/*Ư*/;
    case L'\x01B4'/*ƴ*/: return L'\x01B3'/*Ƴ*/;
    case L'\x01B6'/*ƶ*/: return L'\x01B5'/*Ƶ*/;
    case L'\x01B9'/*ƹ*/: return L'\x01B8'/*Ƹ*/;
    case L'\x01BD'/*ƽ*/: return L'\x01BC'/*Ƽ*/;
    case L'\x01C6'/*ǆ*/: return L'\x01C4'/*Ǆ*/;
    case L'\x01C9'/*ǉ*/: return L'\x01C7'/*Ǉ*/;
    case L'\x01CC'/*ǌ*/: return L'\x01CA'/*Ǌ*/;
    case L'\x01CE'/*ǎ*/: return L'\x01CD'/*Ǎ*/;
    case L'\x01D0'/*ǐ*/: return L'\x01CF'/*Ǐ*/;
    case L'\x01D2'/*ǒ*/: return L'\x01D1'/*Ǒ*/;
    case L'\x01D4'/*ǔ*/: return L'\x01D3'/*Ǔ*/;
    case L'\x01D6'/*ǖ*/: return L'\x01D5'/*Ǖ*/;
    case L'\x01D8'/*ǘ*/: return L'\x01D7'/*Ǘ*/;
    case L'\x01DA'/*ǚ*/: return L'\x01D9'/*Ǚ*/;
    case L'\x01DC'/*ǜ*/: return L'\x01DB'/*Ǜ*/;
    case L'\x01DF'/*ǟ*/: return L'\x01DE'/*Ǟ*/;
    case L'\x01E1'/*ǡ*/: return L'\x01E0'/*Ǡ*/;
    case L'\x01E3'/*ǣ*/: return L'\x01E2'/*Ǣ*/;
    case L'\x01E5'/*ǥ*/: return L'\x01E4'/*Ǥ*/;
    case L'\x01E7'/*ǧ*/: return L'\x01E6'/*Ǧ*/;
    case L'\x01E9'/*ǩ*/: return L'\x01E8'/*Ǩ*/;
    case L'\x01EB'/*ǫ*/: return L'\x01EA'/*Ǫ*/;
    case L'\x01ED'/*ǭ*/: return L'\x01EC'/*Ǭ*/;
    case L'\x01EF'/*ǯ*/: return L'\x01EE'/*Ǯ*/;
    case L'\x01F3'/*ǳ*/: return L'\x01F1'/*Ǳ*/;
    case L'\x01F5'/*ǵ*/: return L'\x01F4'/*Ǵ*/;
    case L'\x01FB'/*ǻ*/: return L'\x01FA'/*Ǻ*/;
    case L'\x01FD'/*ǽ*/: return L'\x01FC'/*Ǽ*/;
    case L'\x01FF'/*ǿ*/: return L'\x01FE'/*Ǿ*/;
    case L'\x0201'/*ȁ*/: return L'\x0200'/*Ȁ*/;
    case L'\x0203'/*ȃ*/: return L'\x0202'/*Ȃ*/;
    case L'\x0205'/*ȅ*/: return L'\x0204'/*Ȅ*/;
    case L'\x0207'/*ȇ*/: return L'\x0206'/*Ȇ*/;
    case L'\x0209'/*ȉ*/: return L'\x0208'/*Ȉ*/;
    case L'\x020B'/*ȋ*/: return L'\x020A'/*Ȋ*/;
    case L'\x020D'/*ȍ*/: return L'\x020C'/*Ȍ*/;
    case L'\x020F'/*ȏ*/: return L'\x020E'/*Ȏ*/;
    case L'\x0211'/*ȑ*/: return L'\x0210'/*Ȑ*/;
    case L'\x0213'/*ȓ*/: return L'\x0212'/*Ȓ*/;
    case L'\x0215'/*ȕ*/: return L'\x0214'/*Ȕ*/;
    case L'\x0217'/*ȗ*/: return L'\x0216'/*Ȗ*/;
    case L'\x0253'/*ɓ*/: return L'\x0181'/*Ɓ*/;
    case L'\x0254'/*ɔ*/: return L'\x0186'/*Ɔ*/;
    case L'\x0257'/*ɗ*/: return L'\x018A'/*Ɗ*/;
    case L'\x0258'/*ɘ*/: return L'\x018E'/*Ǝ*/;
    case L'\x0259'/*ə*/: return L'\x018F'/*Ə*/;
    case L'\x025B'/*ɛ*/: return L'\x0190'/*Ɛ*/;
    case L'\x0260'/*ɠ*/: return L'\x0193'/*Ɠ*/;
    case L'\x0263'/*ɣ*/: return L'\x0194'/*Ɣ*/;
    case L'\x0268'/*ɨ*/: return L'\x0197'/*Ɨ*/;
    case L'\x0269'/*ɩ*/: return L'\x0196'/*Ɩ*/;
    case L'\x026F'/*ɯ*/: return L'\x019C'/*Ɯ*/;
    case L'\x0272'/*ɲ*/: return L'\x019D'/*Ɲ*/;
    case L'\x0275'/*ɵ*/: return L'\x019F'/*Ɵ*/;
    case L'\x0283'/*ʃ*/: return L'\x01A9'/*Ʃ*/;
    case L'\x0288'/*ʈ*/: return L'\x01AE'/*Ʈ*/;
    case L'\x028A'/*ʊ*/: return L'\x01B1'/*Ʊ*/;
    case L'\x028B'/*ʋ*/: return L'\x01B2'/*Ʋ*/;
    case L'\x0292'/*ʒ*/: return L'\x01B7'/*Ʒ*/;
    case L'\x03AC'/*ά*/: return L'\x0386'/*Ά*/;
    case L'\x03AD'/*έ*/: return L'\x0388'/*Έ*/;
    case L'\x03AE'/*ή*/: return L'\x0389'/*Ή*/;
    case L'\x03AF'/*ί*/: return L'\x038A'/*Ί*/;
    case L'\x03B1'/*α*/: return L'\x0391'/*Α*/;
    case L'\x03B2'/*β*/: return L'\x0392'/*Β*/;
    case L'\x03B3'/*γ*/: return L'\x0393'/*Γ*/;
    case L'\x03B4'/*δ*/: return L'\x0394'/*Δ*/;
    case L'\x03B5'/*ε*/: return L'\x0395'/*Ε*/;
    case L'\x03B6'/*ζ*/: return L'\x0396'/*Ζ*/;
    case L'\x03B7'/*η*/: return L'\x0397'/*Η*/;
    case L'\x03B8'/*θ*/: return L'\x0398'/*Θ*/;
    case L'\x03B9'/*ι*/: return L'\x0399'/*Ι*/;
    case L'\x03BA'/*κ*/: return L'\x039A'/*Κ*/;
    case L'\x03BB'/*λ*/: return L'\x039B'/*Λ*/;
    case L'\x03BC'/*μ*/: return L'\x039C'/*Μ*/;
    case L'\x03BD'/*ν*/: return L'\x039D'/*Ν*/;
    case L'\x03BE'/*ξ*/: return L'\x039E'/*Ξ*/;
    case L'\x03BF'/*ο*/: return L'\x039F'/*Ο*/;
    case L'\x03C0'/*π*/: return L'\x03A0'/*Π*/;
    case L'\x03C1'/*ρ*/: return L'\x03A1'/*Ρ*/;
    case L'\x03C3'/*σ*/: return L'\x03A3'/*Σ*/;
    case L'\x03C4'/*τ*/: return L'\x03A4'/*Τ*/;
    case L'\x03C5'/*υ*/: return L'\x03A5'/*Υ*/;
    case L'\x03C6'/*φ*/: return L'\x03A6'/*Φ*/;
    case L'\x03C7'/*χ*/: return L'\x03A7'/*Χ*/;
    case L'\x03C8'/*ψ*/: return L'\x03A8'/*Ψ*/;
    case L'\x03C9'/*ω*/: return L'\x03A9'/*Ω*/;
    case L'\x03CA'/*ϊ*/: return L'\x03AA'/*Ϊ*/;
    case L'\x03CB'/*ϋ*/: return L'\x03AB'/*Ϋ*/;
    case L'\x03CC'/*ό*/: return L'\x038C'/*Ό*/;
    case L'\x03CD'/*ύ*/: return L'\x038E'/*Ύ*/;
    case L'\x03CE'/*ώ*/: return L'\x038F'/*Ώ*/;
    case L'\x03E3'/*ϣ*/: return L'\x03E2'/*Ϣ*/;
    case L'\x03E5'/*ϥ*/: return L'\x03E4'/*Ϥ*/;
    case L'\x03E7'/*ϧ*/: return L'\x03E6'/*Ϧ*/;
    case L'\x03E9'/*ϩ*/: return L'\x03E8'/*Ϩ*/;
    case L'\x03EB'/*ϫ*/: return L'\x03EA'/*Ϫ*/;
    case L'\x03ED'/*ϭ*/: return L'\x03EC'/*Ϭ*/;
    case L'\x03EF'/*ϯ*/: return L'\x03EE'/*Ϯ*/;
    case L'\x0430'/*а*/: return L'\x0410'/*А*/;
    case L'\x0431'/*б*/: return L'\x0411'/*Б*/;
    case L'\x0432'/*в*/: return L'\x0412'/*В*/;
    case L'\x0433'/*г*/: return L'\x0413'/*Г*/;
    case L'\x0434'/*д*/: return L'\x0414'/*Д*/;
    case L'\x0435'/*е*/: return L'\x0415'/*Е*/;
    case L'\x0436'/*ж*/: return L'\x0416'/*Ж*/;
    case L'\x0437'/*з*/: return L'\x0417'/*З*/;
    case L'\x0438'/*и*/: return L'\x0418'/*И*/;
    case L'\x0439'/*й*/: return L'\x0419'/*Й*/;
    case L'\x043A'/*к*/: return L'\x041A'/*К*/;
    case L'\x043B'/*л*/: return L'\x041B'/*Л*/;
    case L'\x043C'/*м*/: return L'\x041C'/*М*/;
    case L'\x043D'/*н*/: return L'\x041D'/*Н*/;
    case L'\x043E'/*о*/: return L'\x041E'/*О*/;
    case L'\x043F'/*п*/: return L'\x041F'/*П*/;
    case L'\x0440'/*р*/: return L'\x0420'/*Р*/;
    case L'\x0441'/*с*/: return L'\x0421'/*С*/;
    case L'\x0442'/*т*/: return L'\x0422'/*Т*/;
    case L'\x0443'/*у*/: return L'\x0423'/*У*/;
    case L'\x0444'/*ф*/: return L'\x0424'/*Ф*/;
    case L'\x0445'/*х*/: return L'\x0425'/*Х*/;
    case L'\x0446'/*ц*/: return L'\x0426'/*Ц*/;
    case L'\x0447'/*ч*/: return L'\x0427'/*Ч*/;
    case L'\x0448'/*ш*/: return L'\x0428'/*Ш*/;
    case L'\x0449'/*щ*/: return L'\x0429'/*Щ*/;
    case L'\x044A'/*ъ*/: return L'\x042A'/*Ъ*/;
    case L'\x044B'/*ы*/: return L'\x042B'/*Ы*/;
    case L'\x044C'/*ь*/: return L'\x042C'/*Ь*/;
    case L'\x044D'/*э*/: return L'\x042D'/*Э*/;
    case L'\x044E'/*ю*/: return L'\x042E'/*Ю*/;
    case L'\x044F'/*я*/: return L'\x042F'/*Я*/;
    case L'\x0451'/*ё*/: return L'\x0401'/*Ё*/;
    case L'\x0452'/*ђ*/: return L'\x0402'/*Ђ*/;
    case L'\x0453'/*ѓ*/: return L'\x0403'/*Ѓ*/;
    case L'\x0454'/*є*/: return L'\x0404'/*Є*/;
    case L'\x0455'/*ѕ*/: return L'\x0405'/*Ѕ*/;
    case L'\x0456'/*і*/: return L'\x0406'/*І*/;
    case L'\x0457'/*ї*/: return L'\x0407'/*Ї*/;
    case L'\x0458'/*ј*/: return L'\x0408'/*Ј*/;
    case L'\x0459'/*љ*/: return L'\x0409'/*Љ*/;
    case L'\x045A'/*њ*/: return L'\x040A'/*Њ*/;
    case L'\x045B'/*ћ*/: return L'\x040B'/*Ћ*/;
    case L'\x045C'/*ќ*/: return L'\x040C'/*Ќ*/;
    case L'\x045E'/*ў*/: return L'\x040E'/*Ў*/;
    case L'\x045F'/*џ*/: return L'\x040F'/*Џ*/;
    case L'\x0461'/*ѡ*/: return L'\x0460'/*Ѡ*/;
    case L'\x0463'/*ѣ*/: return L'\x0462'/*Ѣ*/;
    case L'\x0465'/*ѥ*/: return L'\x0464'/*Ѥ*/;
    case L'\x0467'/*ѧ*/: return L'\x0466'/*Ѧ*/;
    case L'\x0469'/*ѩ*/: return L'\x0468'/*Ѩ*/;
    case L'\x046B'/*ѫ*/: return L'\x046A'/*Ѫ*/;
    case L'\x046D'/*ѭ*/: return L'\x046C'/*Ѭ*/;
    case L'\x046F'/*ѯ*/: return L'\x046E'/*Ѯ*/;
    case L'\x0471'/*ѱ*/: return L'\x0470'/*Ѱ*/;
    case L'\x0473'/*ѳ*/: return L'\x0472'/*Ѳ*/;
    case L'\x0475'/*ѵ*/: return L'\x0474'/*Ѵ*/;
    case L'\x0477'/*ѷ*/: return L'\x0476'/*Ѷ*/;
    case L'\x0479'/*ѹ*/: return L'\x0478'/*Ѹ*/;
    case L'\x047B'/*ѻ*/: return L'\x047A'/*Ѻ*/;
    case L'\x047D'/*ѽ*/: return L'\x047C'/*Ѽ*/;
    case L'\x047F'/*ѿ*/: return L'\x047E'/*Ѿ*/;
    case L'\x0481'/*ҁ*/: return L'\x0480'/*Ҁ*/;
    case L'\x0491'/*ґ*/: return L'\x0490'/*Ґ*/;
    case L'\x0493'/*ғ*/: return L'\x0492'/*Ғ*/;
    case L'\x0495'/*ҕ*/: return L'\x0494'/*Ҕ*/;
    case L'\x0497'/*җ*/: return L'\x0496'/*Җ*/;
    case L'\x0499'/*ҙ*/: return L'\x0498'/*Ҙ*/;
    case L'\x049B'/*қ*/: return L'\x049A'/*Қ*/;
    case L'\x049D'/*ҝ*/: return L'\x049C'/*Ҝ*/;
    case L'\x049F'/*ҟ*/: return L'\x049E'/*Ҟ*/;
    case L'\x04A1'/*ҡ*/: return L'\x04A0'/*Ҡ*/;
    case L'\x04A3'/*ң*/: return L'\x04A2'/*Ң*/;
    case L'\x04A5'/*ҥ*/: return L'\x04A4'/*Ҥ*/;
    case L'\x04A7'/*ҧ*/: return L'\x04A6'/*Ҧ*/;
    case L'\x04A9'/*ҩ*/: return L'\x04A8'/*Ҩ*/;
    case L'\x04AB'/*ҫ*/: return L'\x04AA'/*Ҫ*/;
    case L'\x04AD'/*ҭ*/: return L'\x04AC'/*Ҭ*/;
    case L'\x04AF'/*ү*/: return L'\x04AE'/*Ү*/;
    case L'\x04B1'/*ұ*/: return L'\x04B0'/*Ұ*/;
    case L'\x04B3'/*ҳ*/: return L'\x04B2'/*Ҳ*/;
    case L'\x04B5'/*ҵ*/: return L'\x04B4'/*Ҵ*/;
    case L'\x04B7'/*ҷ*/: return L'\x04B6'/*Ҷ*/;
    case L'\x04B9'/*ҹ*/: return L'\x04B8'/*Ҹ*/;
    case L'\x04BB'/*һ*/: return L'\x04BA'/*Һ*/;
    case L'\x04BD'/*ҽ*/: return L'\x04BC'/*Ҽ*/;
    case L'\x04BF'/*ҿ*/: return L'\x04BE'/*Ҿ*/;
    case L'\x04C2'/*ӂ*/: return L'\x04C1'/*Ӂ*/;
    case L'\x04C4'/*ӄ*/: return L'\x04C3'/*Ӄ*/;
    case L'\x04C8'/*ӈ*/: return L'\x04C7'/*Ӈ*/;
    case L'\x04CC'/*ӌ*/: return L'\x04CB'/*Ӌ*/;
    case L'\x04D1'/*ӑ*/: return L'\x04D0'/*Ӑ*/;
    case L'\x04D3'/*ӓ*/: return L'\x04D2'/*Ӓ*/;
    case L'\x04D5'/*ӕ*/: return L'\x04D4'/*Ӕ*/;
    case L'\x04D7'/*ӗ*/: return L'\x04D6'/*Ӗ*/;
    case L'\x04D9'/*ә*/: return L'\x04D8'/*Ә*/;
    case L'\x04DB'/*ӛ*/: return L'\x04DA'/*Ӛ*/;
    case L'\x04DD'/*ӝ*/: return L'\x04DC'/*Ӝ*/;
    case L'\x04DF'/*ӟ*/: return L'\x04DE'/*Ӟ*/;
    case L'\x04E1'/*ӡ*/: return L'\x04E0'/*Ӡ*/;
    case L'\x04E3'/*ӣ*/: return L'\x04E2'/*Ӣ*/;
    case L'\x04E5'/*ӥ*/: return L'\x04E4'/*Ӥ*/;
    case L'\x04E7'/*ӧ*/: return L'\x04E6'/*Ӧ*/;
    case L'\x04E9'/*ө*/: return L'\x04E8'/*Ө*/;
    case L'\x04EB'/*ӫ*/: return L'\x04EA'/*Ӫ*/;
    case L'\x04EF'/*ӯ*/: return L'\x04EE'/*Ӯ*/;
    case L'\x04F1'/*ӱ*/: return L'\x04F0'/*Ӱ*/;
    case L'\x04F3'/*ӳ*/: return L'\x04F2'/*Ӳ*/;
    case L'\x04F5'/*ӵ*/: return L'\x04F4'/*Ӵ*/;
    case L'\x04F9'/*ӹ*/: return L'\x04F8'/*Ӹ*/;
    case L'\x0561'/*ա*/: return L'\x0531'/*Ա*/;
    case L'\x0562'/*բ*/: return L'\x0532'/*Բ*/;
    case L'\x0563'/*գ*/: return L'\x0533'/*Գ*/;
    case L'\x0564'/*դ*/: return L'\x0534'/*Դ*/;
    case L'\x0565'/*ե*/: return L'\x0535'/*Ե*/;
    case L'\x0566'/*զ*/: return L'\x0536'/*Զ*/;
    case L'\x0567'/*է*/: return L'\x0537'/*Է*/;
    case L'\x0568'/*ը*/: return L'\x0538'/*Ը*/;
    case L'\x0569'/*թ*/: return L'\x0539'/*Թ*/;
    case L'\x056A'/*ժ*/: return L'\x053A'/*Ժ*/;
    case L'\x056B'/*ի*/: return L'\x053B'/*Ի*/;
    case L'\x056C'/*լ*/: return L'\x053C'/*Լ*/;
    case L'\x056D'/*խ*/: return L'\x053D'/*Խ*/;
    case L'\x056E'/*ծ*/: return L'\x053E'/*Ծ*/;
    case L'\x056F'/*կ*/: return L'\x053F'/*Կ*/;
    case L'\x0570'/*հ*/: return L'\x0540'/*Հ*/;
    case L'\x0571'/*ձ*/: return L'\x0541'/*Ձ*/;
    case L'\x0572'/*ղ*/: return L'\x0542'/*Ղ*/;
    case L'\x0573'/*ճ*/: return L'\x0543'/*Ճ*/;
    case L'\x0574'/*մ*/: return L'\x0544'/*Մ*/;
    case L'\x0575'/*յ*/: return L'\x0545'/*Յ*/;
    case L'\x0576'/*ն*/: return L'\x0546'/*Ն*/;
    case L'\x0577'/*շ*/: return L'\x0547'/*Շ*/;
    case L'\x0578'/*ո*/: return L'\x0548'/*Ո*/;
    case L'\x0579'/*չ*/: return L'\x0549'/*Չ*/;
    case L'\x057A'/*պ*/: return L'\x054A'/*Պ*/;
    case L'\x057B'/*ջ*/: return L'\x054B'/*Ջ*/;
    case L'\x057C'/*ռ*/: return L'\x054C'/*Ռ*/;
    case L'\x057D'/*ս*/: return L'\x054D'/*Ս*/;
    case L'\x057E'/*վ*/: return L'\x054E'/*Վ*/;
    case L'\x057F'/*տ*/: return L'\x054F'/*Տ*/;
    case L'\x0580'/*ր*/: return L'\x0550'/*Ր*/;
    case L'\x0581'/*ց*/: return L'\x0551'/*Ց*/;
    case L'\x0582'/*ւ*/: return L'\x0552'/*Ւ*/;
    case L'\x0583'/*փ*/: return L'\x0553'/*Փ*/;
    case L'\x0584'/*ք*/: return L'\x0554'/*Ք*/;
    case L'\x0585'/*օ*/: return L'\x0555'/*Օ*/;
    case L'\x0586'/*ֆ*/: return L'\x0556'/*Ֆ*/;
    case L'\x10D0'/*ა*/: return L'\x10A0'/*Ⴀ*/;
    case L'\x10D1'/*ბ*/: return L'\x10A1'/*Ⴁ*/;
    case L'\x10D2'/*გ*/: return L'\x10A2'/*Ⴂ*/;
    case L'\x10D3'/*დ*/: return L'\x10A3'/*Ⴃ*/;
    case L'\x10D4'/*ე*/: return L'\x10A4'/*Ⴄ*/;
    case L'\x10D5'/*ვ*/: return L'\x10A5'/*Ⴅ*/;
    case L'\x10D6'/*ზ*/: return L'\x10A6'/*Ⴆ*/;
    case L'\x10D7'/*თ*/: return L'\x10A7'/*Ⴇ*/;
    case L'\x10D8'/*ი*/: return L'\x10A8'/*Ⴈ*/;
    case L'\x10D9'/*კ*/: return L'\x10A9'/*Ⴉ*/;
    case L'\x10DA'/*ლ*/: return L'\x10AA'/*Ⴊ*/;
    case L'\x10DB'/*მ*/: return L'\x10AB'/*Ⴋ*/;
    case L'\x10DC'/*ნ*/: return L'\x10AC'/*Ⴌ*/;
    case L'\x10DD'/*ო*/: return L'\x10AD'/*Ⴍ*/;
    case L'\x10DE'/*პ*/: return L'\x10AE'/*Ⴎ*/;
    case L'\x10DF'/*ჟ*/: return L'\x10AF'/*Ⴏ*/;
    case L'\x10E0'/*რ*/: return L'\x10B0'/*Ⴐ*/;
    case L'\x10E1'/*ს*/: return L'\x10B1'/*Ⴑ*/;
    case L'\x10E2'/*ტ*/: return L'\x10B2'/*Ⴒ*/;
    case L'\x10E3'/*უ*/: return L'\x10B3'/*Ⴓ*/;
    case L'\x10E4'/*ფ*/: return L'\x10B4'/*Ⴔ*/;
    case L'\x10E5'/*ქ*/: return L'\x10B5'/*Ⴕ*/;
    case L'\x10E6'/*ღ*/: return L'\x10B6'/*Ⴖ*/;
    case L'\x10E7'/*ყ*/: return L'\x10B7'/*Ⴗ*/;
    case L'\x10E8'/*შ*/: return L'\x10B8'/*Ⴘ*/;
    case L'\x10E9'/*ჩ*/: return L'\x10B9'/*Ⴙ*/;
    case L'\x10EA'/*ც*/: return L'\x10BA'/*Ⴚ*/;
    case L'\x10EB'/*ძ*/: return L'\x10BB'/*Ⴛ*/;
    case L'\x10EC'/*წ*/: return L'\x10BC'/*Ⴜ*/;
    case L'\x10ED'/*ჭ*/: return L'\x10BD'/*Ⴝ*/;
    case L'\x10EE'/*ხ*/: return L'\x10BE'/*Ⴞ*/;
    case L'\x10EF'/*ჯ*/: return L'\x10BF'/*Ⴟ*/;
    case L'\x10F0'/*ჰ*/: return L'\x10C0'/*Ⴠ*/;
    case L'\x10F1'/*ჱ*/: return L'\x10C1'/*Ⴡ*/;
    case L'\x10F2'/*ჲ*/: return L'\x10C2'/*Ⴢ*/;
    case L'\x10F3'/*ჳ*/: return L'\x10C3'/*Ⴣ*/;
    case L'\x10F4'/*ჴ*/: return L'\x10C4'/*Ⴤ*/;
    case L'\x10F5'/*ჵ*/: return L'\x10C5'/*Ⴥ*/;
    case L'\x1E01'/*ḁ*/: return L'\x1E00'/*Ḁ*/;
    case L'\x1E03'/*ḃ*/: return L'\x1E02'/*Ḃ*/;
    case L'\x1E05'/*ḅ*/: return L'\x1E04'/*Ḅ*/;
    case L'\x1E07'/*ḇ*/: return L'\x1E06'/*Ḇ*/;
    case L'\x1E09'/*ḉ*/: return L'\x1E08'/*Ḉ*/;
    case L'\x1E0B'/*ḋ*/: return L'\x1E0A'/*Ḋ*/;
    case L'\x1E0D'/*ḍ*/: return L'\x1E0C'/*Ḍ*/;
    case L'\x1E0F'/*ḏ*/: return L'\x1E0E'/*Ḏ*/;
    case L'\x1E11'/*ḑ*/: return L'\x1E10'/*Ḑ*/;
    case L'\x1E13'/*ḓ*/: return L'\x1E12'/*Ḓ*/;
    case L'\x1E15'/*ḕ*/: return L'\x1E14'/*Ḕ*/;
    case L'\x1E17'/*ḗ*/: return L'\x1E16'/*Ḗ*/;
    case L'\x1E19'/*ḙ*/: return L'\x1E18'/*Ḙ*/;
    case L'\x1E1B'/*ḛ*/: return L'\x1E1A'/*Ḛ*/;
    case L'\x1E1D'/*ḝ*/: return L'\x1E1C'/*Ḝ*/;
    case L'\x1E1F'/*ḟ*/: return L'\x1E1E'/*Ḟ*/;
    case L'\x1E21'/*ḡ*/: return L'\x1E20'/*Ḡ*/;
    case L'\x1E23'/*ḣ*/: return L'\x1E22'/*Ḣ*/;
    case L'\x1E25'/*ḥ*/: return L'\x1E24'/*Ḥ*/;
    case L'\x1E27'/*ḧ*/: return L'\x1E26'/*Ḧ*/;
    case L'\x1E29'/*ḩ*/: return L'\x1E28'/*Ḩ*/;
    case L'\x1E2B'/*ḫ*/: return L'\x1E2A'/*Ḫ*/;
    case L'\x1E2D'/*ḭ*/: return L'\x1E2C'/*Ḭ*/;
    case L'\x1E2F'/*ḯ*/: return L'\x1E2E'/*Ḯ*/;
    case L'\x1E31'/*ḱ*/: return L'\x1E30'/*Ḱ*/;
    case L'\x1E33'/*ḳ*/: return L'\x1E32'/*Ḳ*/;
    case L'\x1E35'/*ḵ*/: return L'\x1E34'/*Ḵ*/;
    case L'\x1E37'/*ḷ*/: return L'\x1E36'/*Ḷ*/;
    case L'\x1E39'/*ḹ*/: return L'\x1E38'/*Ḹ*/;
    case L'\x1E3B'/*ḻ*/: return L'\x1E3A'/*Ḻ*/;
    case L'\x1E3D'/*ḽ*/: return L'\x1E3C'/*Ḽ*/;
    case L'\x1E3F'/*ḿ*/: return L'\x1E3E'/*Ḿ*/;
    case L'\x1E41'/*ṁ*/: return L'\x1E40'/*Ṁ*/;
    case L'\x1E43'/*ṃ*/: return L'\x1E42'/*Ṃ*/;
    case L'\x1E45'/*ṅ*/: return L'\x1E44'/*Ṅ*/;
    case L'\x1E47'/*ṇ*/: return L'\x1E46'/*Ṇ*/;
    case L'\x1E49'/*ṉ*/: return L'\x1E48'/*Ṉ*/;
    case L'\x1E4B'/*ṋ*/: return L'\x1E4A'/*Ṋ*/;
    case L'\x1E4D'/*ṍ*/: return L'\x1E4C'/*Ṍ*/;
    case L'\x1E4F'/*ṏ*/: return L'\x1E4E'/*Ṏ*/;
    case L'\x1E51'/*ṑ*/: return L'\x1E50'/*Ṑ*/;
    case L'\x1E53'/*ṓ*/: return L'\x1E52'/*Ṓ*/;
    case L'\x1E55'/*ṕ*/: return L'\x1E54'/*Ṕ*/;
    case L'\x1E57'/*ṗ*/: return L'\x1E56'/*Ṗ*/;
    case L'\x1E59'/*ṙ*/: return L'\x1E58'/*Ṙ*/;
    case L'\x1E5B'/*ṛ*/: return L'\x1E5A'/*Ṛ*/;
    case L'\x1E5D'/*ṝ*/: return L'\x1E5C'/*Ṝ*/;
    case L'\x1E5F'/*ṟ*/: return L'\x1E5E'/*Ṟ*/;
    case L'\x1E61'/*ṡ*/: return L'\x1E60'/*Ṡ*/;
    case L'\x1E63'/*ṣ*/: return L'\x1E62'/*Ṣ*/;
    case L'\x1E65'/*ṥ*/: return L'\x1E64'/*Ṥ*/;
    case L'\x1E67'/*ṧ*/: return L'\x1E66'/*Ṧ*/;
    case L'\x1E69'/*ṩ*/: return L'\x1E68'/*Ṩ*/;
    case L'\x1E6B'/*ṫ*/: return L'\x1E6A'/*Ṫ*/;
    case L'\x1E6D'/*ṭ*/: return L'\x1E6C'/*Ṭ*/;
    case L'\x1E6F'/*ṯ*/: return L'\x1E6E'/*Ṯ*/;
    case L'\x1E71'/*ṱ*/: return L'\x1E70'/*Ṱ*/;
    case L'\x1E73'/*ṳ*/: return L'\x1E72'/*Ṳ*/;
    case L'\x1E75'/*ṵ*/: return L'\x1E74'/*Ṵ*/;
    case L'\x1E77'/*ṷ*/: return L'\x1E76'/*Ṷ*/;
    case L'\x1E79'/*ṹ*/: return L'\x1E78'/*Ṹ*/;
    case L'\x1E7B'/*ṻ*/: return L'\x1E7A'/*Ṻ*/;
    case L'\x1E7D'/*ṽ*/: return L'\x1E7C'/*Ṽ*/;
    case L'\x1E7F'/*ṿ*/: return L'\x1E7E'/*Ṿ*/;
    case L'\x1E81'/*ẁ*/: return L'\x1E80'/*Ẁ*/;
    case L'\x1E83'/*ẃ*/: return L'\x1E82'/*Ẃ*/;
    case L'\x1E85'/*ẅ*/: return L'\x1E84'/*Ẅ*/;
    case L'\x1E87'/*ẇ*/: return L'\x1E86'/*Ẇ*/;
    case L'\x1E89'/*ẉ*/: return L'\x1E88'/*Ẉ*/;
    case L'\x1E8B'/*ẋ*/: return L'\x1E8A'/*Ẋ*/;
    case L'\x1E8D'/*ẍ*/: return L'\x1E8C'/*Ẍ*/;
    case L'\x1E8F'/*ẏ*/: return L'\x1E8E'/*Ẏ*/;
    case L'\x1E91'/*ẑ*/: return L'\x1E90'/*Ẑ*/;
    case L'\x1E93'/*ẓ*/: return L'\x1E92'/*Ẓ*/;
    case L'\x1E95'/*ẕ*/: return L'\x1E94'/*Ẕ*/;
    case L'\x1EA1'/*ạ*/: return L'\x1EA0'/*Ạ*/;
    case L'\x1EA3'/*ả*/: return L'\x1EA2'/*Ả*/;
    case L'\x1EA5'/*ấ*/: return L'\x1EA4'/*Ấ*/;
    case L'\x1EA7'/*ầ*/: return L'\x1EA6'/*Ầ*/;
    case L'\x1EA9'/*ẩ*/: return L'\x1EA8'/*Ẩ*/;
    case L'\x1EAB'/*ẫ*/: return L'\x1EAA'/*Ẫ*/;
    case L'\x1EAD'/*ậ*/: return L'\x1EAC'/*Ậ*/;
    case L'\x1EAF'/*ắ*/: return L'\x1EAE'/*Ắ*/;
    case L'\x1EB1'/*ằ*/: return L'\x1EB0'/*Ằ*/;
    case L'\x1EB3'/*ẳ*/: return L'\x1EB2'/*Ẳ*/;
    case L'\x1EB5'/*ẵ*/: return L'\x1EB4'/*Ẵ*/;
    case L'\x1EB7'/*ặ*/: return L'\x1EB6'/*Ặ*/;
    case L'\x1EB9'/*ẹ*/: return L'\x1EB8'/*Ẹ*/;
    case L'\x1EBB'/*ẻ*/: return L'\x1EBA'/*Ẻ*/;
    case L'\x1EBD'/*ẽ*/: return L'\x1EBC'/*Ẽ*/;
    case L'\x1EBF'/*ế*/: return L'\x1EBE'/*Ế*/;
    case L'\x1EC1'/*ề*/: return L'\x1EC0'/*Ề*/;
    case L'\x1EC3'/*ể*/: return L'\x1EC2'/*Ể*/;
    case L'\x1EC5'/*ễ*/: return L'\x1EC4'/*Ễ*/;
    case L'\x1EC7'/*ệ*/: return L'\x1EC6'/*Ệ*/;
    case L'\x1EC9'/*ỉ*/: return L'\x1EC8'/*Ỉ*/;
    case L'\x1ECB'/*ị*/: return L'\x1ECA'/*Ị*/;
    case L'\x1ECD'/*ọ*/: return L'\x1ECC'/*Ọ*/;
    case L'\x1ECF'/*ỏ*/: return L'\x1ECE'/*Ỏ*/;
    case L'\x1ED1'/*ố*/: return L'\x1ED0'/*Ố*/;
    case L'\x1ED3'/*ồ*/: return L'\x1ED2'/*Ồ*/;
    case L'\x1ED5'/*ổ*/: return L'\x1ED4'/*Ổ*/;
    case L'\x1ED7'/*ỗ*/: return L'\x1ED6'/*Ỗ*/;
    case L'\x1ED9'/*ộ*/: return L'\x1ED8'/*Ộ*/;
    case L'\x1EDB'/*ớ*/: return L'\x1EDA'/*Ớ*/;
    case L'\x1EDD'/*ờ*/: return L'\x1EDC'/*Ờ*/;
    case L'\x1EDF'/*ở*/: return L'\x1EDE'/*Ở*/;
    case L'\x1EE1'/*ỡ*/: return L'\x1EE0'/*Ỡ*/;
    case L'\x1EE3'/*ợ*/: return L'\x1EE2'/*Ợ*/;
    case L'\x1EE5'/*ụ*/: return L'\x1EE4'/*Ụ*/;
    case L'\x1EE7'/*ủ*/: return L'\x1EE6'/*Ủ*/;
    case L'\x1EE9'/*ứ*/: return L'\x1EE8'/*Ứ*/;
    case L'\x1EEB'/*ừ*/: return L'\x1EEA'/*Ừ*/;
    case L'\x1EED'/*ử*/: return L'\x1EEC'/*Ử*/;
    case L'\x1EEF'/*ữ*/: return L'\x1EEE'/*Ữ*/;
    case L'\x1EF1'/*ự*/: return L'\x1EF0'/*Ự*/;
    case L'\x1EF3'/*ỳ*/: return L'\x1EF2'/*Ỳ*/;
    case L'\x1EF5'/*ỵ*/: return L'\x1EF4'/*Ỵ*/;
    case L'\x1EF7'/*ỷ*/: return L'\x1EF6'/*Ỷ*/;
    case L'\x1EF9'/*ỹ*/: return L'\x1EF8'/*Ỹ*/;
    case L'\x1F00'/*ἀ*/: return L'\x1F08'/*Ἀ*/;
    case L'\x1F01'/*ἁ*/: return L'\x1F09'/*Ἁ*/;
    case L'\x1F02'/*ἂ*/: return L'\x1F0A'/*Ἂ*/;
    case L'\x1F03'/*ἃ*/: return L'\x1F0B'/*Ἃ*/;
    case L'\x1F04'/*ἄ*/: return L'\x1F0C'/*Ἄ*/;
    case L'\x1F05'/*ἅ*/: return L'\x1F0D'/*Ἅ*/;
    case L'\x1F06'/*ἆ*/: return L'\x1F0E'/*Ἆ*/;
    case L'\x1F07'/*ἇ*/: return L'\x1F0F'/*Ἇ*/;
    case L'\x1F10'/*ἐ*/: return L'\x1F18'/*Ἐ*/;
    case L'\x1F11'/*ἑ*/: return L'\x1F19'/*Ἑ*/;
    case L'\x1F12'/*ἒ*/: return L'\x1F1A'/*Ἒ*/;
    case L'\x1F13'/*ἓ*/: return L'\x1F1B'/*Ἓ*/;
    case L'\x1F14'/*ἔ*/: return L'\x1F1C'/*Ἔ*/;
    case L'\x1F15'/*ἕ*/: return L'\x1F1D'/*Ἕ*/;
    case L'\x1F20'/*ἠ*/: return L'\x1F28'/*Ἠ*/;
    case L'\x1F21'/*ἡ*/: return L'\x1F29'/*Ἡ*/;
    case L'\x1F22'/*ἢ*/: return L'\x1F2A'/*Ἢ*/;
    case L'\x1F23'/*ἣ*/: return L'\x1F2B'/*Ἣ*/;
    case L'\x1F24'/*ἤ*/: return L'\x1F2C'/*Ἤ*/;
    case L'\x1F25'/*ἥ*/: return L'\x1F2D'/*Ἥ*/;
    case L'\x1F26'/*ἦ*/: return L'\x1F2E'/*Ἦ*/;
    case L'\x1F27'/*ἧ*/: return L'\x1F2F'/*Ἧ*/;
    case L'\x1F30'/*ἰ*/: return L'\x1F38'/*Ἰ*/;
    case L'\x1F31'/*ἱ*/: return L'\x1F39'/*Ἱ*/;
    case L'\x1F32'/*ἲ*/: return L'\x1F3A'/*Ἲ*/;
    case L'\x1F33'/*ἳ*/: return L'\x1F3B'/*Ἳ*/;
    case L'\x1F34'/*ἴ*/: return L'\x1F3C'/*Ἴ*/;
    case L'\x1F35'/*ἵ*/: return L'\x1F3D'/*Ἵ*/;
    case L'\x1F36'/*ἶ*/: return L'\x1F3E'/*Ἶ*/;
    case L'\x1F37'/*ἷ*/: return L'\x1F3F'/*Ἷ*/;
    case L'\x1F40'/*ὀ*/: return L'\x1F48'/*Ὀ*/;
    case L'\x1F41'/*ὁ*/: return L'\x1F49'/*Ὁ*/;
    case L'\x1F42'/*ὂ*/: return L'\x1F4A'/*Ὂ*/;
    case L'\x1F43'/*ὃ*/: return L'\x1F4B'/*Ὃ*/;
    case L'\x1F44'/*ὄ*/: return L'\x1F4C'/*Ὄ*/;
    case L'\x1F45'/*ὅ*/: return L'\x1F4D'/*Ὅ*/;
    case L'\x1F51'/*ὑ*/: return L'\x1F59'/*Ὑ*/;
    case L'\x1F53'/*ὓ*/: return L'\x1F5B'/*Ὓ*/;
    case L'\x1F55'/*ὕ*/: return L'\x1F5D'/*Ὕ*/;
    case L'\x1F57'/*ὗ*/: return L'\x1F5F'/*Ὗ*/;
    case L'\x1F60'/*ὠ*/: return L'\x1F68'/*Ὠ*/;
    case L'\x1F61'/*ὡ*/: return L'\x1F69'/*Ὡ*/;
    case L'\x1F62'/*ὢ*/: return L'\x1F6A'/*Ὢ*/;
    case L'\x1F63'/*ὣ*/: return L'\x1F6B'/*Ὣ*/;
    case L'\x1F64'/*ὤ*/: return L'\x1F6C'/*Ὤ*/;
    case L'\x1F65'/*ὥ*/: return L'\x1F6D'/*Ὥ*/;
    case L'\x1F66'/*ὦ*/: return L'\x1F6E'/*Ὦ*/;
    case L'\x1F67'/*ὧ*/: return L'\x1F6F'/*Ὧ*/;
    case L'\x1F80'/*ᾀ*/: return L'\x1F88'/*ᾈ*/;
    case L'\x1F81'/*ᾁ*/: return L'\x1F89'/*ᾉ*/;
    case L'\x1F82'/*ᾂ*/: return L'\x1F8A'/*ᾊ*/;
    case L'\x1F83'/*ᾃ*/: return L'\x1F8B'/*ᾋ*/;
    case L'\x1F84'/*ᾄ*/: return L'\x1F8C'/*ᾌ*/;
    case L'\x1F85'/*ᾅ*/: return L'\x1F8D'/*ᾍ*/;
    case L'\x1F86'/*ᾆ*/: return L'\x1F8E'/*ᾎ*/;
    case L'\x1F87'/*ᾇ*/: return L'\x1F8F'/*ᾏ*/;
    case L'\x1F90'/*ᾐ*/: return L'\x1F98'/*ᾘ*/;
    case L'\x1F91'/*ᾑ*/: return L'\x1F99'/*ᾙ*/;
    case L'\x1F92'/*ᾒ*/: return L'\x1F9A'/*ᾚ*/;
    case L'\x1F93'/*ᾓ*/: return L'\x1F9B'/*ᾛ*/;
    case L'\x1F94'/*ᾔ*/: return L'\x1F9C'/*ᾜ*/;
    case L'\x1F95'/*ᾕ*/: return L'\x1F9D'/*ᾝ*/;
    case L'\x1F96'/*ᾖ*/: return L'\x1F9E'/*ᾞ*/;
    case L'\x1F97'/*ᾗ*/: return L'\x1F9F'/*ᾟ*/;
    case L'\x1FA0'/*ᾠ*/: return L'\x1FA8'/*ᾨ*/;
    case L'\x1FA1'/*ᾡ*/: return L'\x1FA9'/*ᾩ*/;
    case L'\x1FA2'/*ᾢ*/: return L'\x1FAA'/*ᾪ*/;
    case L'\x1FA3'/*ᾣ*/: return L'\x1FAB'/*ᾫ*/;
    case L'\x1FA4'/*ᾤ*/: return L'\x1FAC'/*ᾬ*/;
    case L'\x1FA5'/*ᾥ*/: return L'\x1FAD'/*ᾭ*/;
    case L'\x1FA6'/*ᾦ*/: return L'\x1FAE'/*ᾮ*/;
    case L'\x1FA7'/*ᾧ*/: return L'\x1FAF'/*ᾯ*/;
    case L'\x1FB0'/*ᾰ*/: return L'\x1FB8'/*Ᾰ*/;
    case L'\x1FB1'/*ᾱ*/: return L'\x1FB9'/*Ᾱ*/;
    case L'\x1FD0'/*ῐ*/: return L'\x1FD8'/*Ῐ*/;
    case L'\x1FD1'/*ῑ*/: return L'\x1FD9'/*Ῑ*/;
    case L'\x1FE0'/*ῠ*/: return L'\x1FE8'/*Ῠ*/;
    case L'\x1FE1'/*ῡ*/: return L'\x1FE9'/*Ῡ*/;
    case L'\x24D0'/*ⓐ*/: return L'\x24B6'/*Ⓐ*/;
    case L'\x24D1'/*ⓑ*/: return L'\x24B7'/*Ⓑ*/;
    case L'\x24D2'/*ⓒ*/: return L'\x24B8'/*Ⓒ*/;
    case L'\x24D3'/*ⓓ*/: return L'\x24B9'/*Ⓓ*/;
    case L'\x24D4'/*ⓔ*/: return L'\x24BA'/*Ⓔ*/;
    case L'\x24D5'/*ⓕ*/: return L'\x24BB'/*Ⓕ*/;
    case L'\x24D6'/*ⓖ*/: return L'\x24BC'/*Ⓖ*/;
    case L'\x24D7'/*ⓗ*/: return L'\x24BD'/*Ⓗ*/;
    case L'\x24D8'/*ⓘ*/: return L'\x24BE'/*Ⓘ*/;
    case L'\x24D9'/*ⓙ*/: return L'\x24BF'/*Ⓙ*/;
    case L'\x24DA'/*ⓚ*/: return L'\x24C0'/*Ⓚ*/;
    case L'\x24DB'/*ⓛ*/: return L'\x24C1'/*Ⓛ*/;
    case L'\x24DC'/*ⓜ*/: return L'\x24C2'/*Ⓜ*/;
    case L'\x24DD'/*ⓝ*/: return L'\x24C3'/*Ⓝ*/;
    case L'\x24DE'/*ⓞ*/: return L'\x24C4'/*Ⓞ*/;
    case L'\x24DF'/*ⓟ*/: return L'\x24C5'/*Ⓟ*/;
    case L'\x24E0'/*ⓠ*/: return L'\x24C6'/*Ⓠ*/;
    case L'\x24E1'/*ⓡ*/: return L'\x24C7'/*Ⓡ*/;
    case L'\x24E2'/*ⓢ*/: return L'\x24C8'/*Ⓢ*/;
    case L'\x24E3'/*ⓣ*/: return L'\x24C9'/*Ⓣ*/;
    case L'\x24E4'/*ⓤ*/: return L'\x24CA'/*Ⓤ*/;
    case L'\x24E5'/*ⓥ*/: return L'\x24CB'/*Ⓥ*/;
    case L'\x24E6'/*ⓦ*/: return L'\x24CC'/*Ⓦ*/;
    case L'\x24E7'/*ⓧ*/: return L'\x24CD'/*Ⓧ*/;
    case L'\x24E8'/*ⓨ*/: return L'\x24CE'/*Ⓨ*/;
    case L'\x24E9'/*ⓩ*/: return L'\x24CF'/*Ⓩ*/;
    case L'\xFF41'/*ａ*/: return L'\xFF21'/*Ａ*/;
    case L'\xFF42'/*ｂ*/: return L'\xFF22'/*Ｂ*/;
    case L'\xFF43'/*ｃ*/: return L'\xFF23'/*Ｃ*/;
    case L'\xFF44'/*ｄ*/: return L'\xFF24'/*Ｄ*/;
    case L'\xFF45'/*ｅ*/: return L'\xFF25'/*Ｅ*/;
    case L'\xFF46'/*ｆ*/: return L'\xFF26'/*Ｆ*/;
    case L'\xFF47'/*ｇ*/: return L'\xFF27'/*Ｇ*/;
    case L'\xFF48'/*ｈ*/: return L'\xFF28'/*Ｈ*/;
    case L'\xFF49'/*ｉ*/: return L'\xFF29'/*Ｉ*/;
    case L'\xFF4A'/*ｊ*/: return L'\xFF2A'/*Ｊ*/;
    case L'\xFF4B'/*ｋ*/: return L'\xFF2B'/*Ｋ*/;
    case L'\xFF4C'/*ｌ*/: return L'\xFF2C'/*Ｌ*/;
    case L'\xFF4D'/*ｍ*/: return L'\xFF2D'/*Ｍ*/;
    case L'\xFF4E'/*ｎ*/: return L'\xFF2E'/*Ｎ*/;
    case L'\xFF4F'/*ｏ*/: return L'\xFF2F'/*Ｏ*/;
    case L'\xFF50'/*ｐ*/: return L'\xFF30'/*Ｐ*/;
    case L'\xFF51'/*ｑ*/: return L'\xFF31'/*Ｑ*/;
    case L'\xFF52'/*ｒ*/: return L'\xFF32'/*Ｒ*/;
    case L'\xFF53'/*ｓ*/: return L'\xFF33'/*Ｓ*/;
    case L'\xFF54'/*ｔ*/: return L'\xFF34'/*Ｔ*/;
    case L'\xFF55'/*ｕ*/: return L'\xFF35'/*Ｕ*/;
    case L'\xFF56'/*ｖ*/: return L'\xFF36'/*Ｖ*/;
    case L'\xFF57'/*ｗ*/: return L'\xFF37'/*Ｗ*/;
    case L'\xFF58'/*ｘ*/: return L'\xFF38'/*Ｘ*/;
    case L'\xFF59'/*ｙ*/: return L'\xFF39'/*Ｙ*/;
    case L'\xFF5A'/*ｚ*/: return L'\xFF3A'/*Ｚ*/;
  }
  return w;
}

int RemoveDiacriticsFromWchar(int w) {
  switch (w) {
    case L'\x00AA'/*ª*/: return 'a';    // FEMININE ORDINAL INDICATOR
    case L'\x00BA'/*º*/: return 'o';	// MASCULINE ORDINAL INDICATOR
    case L'\x00C0'/*À*/: return 'A';	// LATIN CAPITAL LETTER A WITH GRAVE
    case L'\x00C1'/*Á*/: return 'A';	// LATIN CAPITAL LETTER A WITH ACUTE
    case L'\x00C2'/*Â*/: return 'A';	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX
    case L'\x00C3'/*Ã*/: return 'A';	// LATIN CAPITAL LETTER A WITH TILDE
    case L'\x00C4'/*Ä*/: return 'A';	// LATIN CAPITAL LETTER A WITH DIAERESIS
    case L'\x00C5'/*Å*/: return 'A';	// LATIN CAPITAL LETTER A WITH RING ABOVE
    // case L'\x00C6'/*Æ*/: return 'AE';	// LATIN CAPITAL LETTER AE -- no decomposition
    case L'\x00C7'/*Ç*/: return 'C';	// LATIN CAPITAL LETTER C WITH CEDILLA
    case L'\x00C8'/*È*/: return 'E';	// LATIN CAPITAL LETTER E WITH GRAVE
    case L'\x00C9'/*É*/: return 'E';	// LATIN CAPITAL LETTER E WITH ACUTE
    case L'\x00CA'/*Ê*/: return 'E';	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX
    case L'\x00CB'/*Ë*/: return 'E';	// LATIN CAPITAL LETTER E WITH DIAERESIS
    case L'\x00CC'/*Ì*/: return 'I';	// LATIN CAPITAL LETTER I WITH GRAVE
    case L'\x00CD'/*Í*/: return 'I';	// LATIN CAPITAL LETTER I WITH ACUTE
    case L'\x00CE'/*Î*/: return 'I';	// LATIN CAPITAL LETTER I WITH CIRCUMFLEX
    case L'\x00CF'/*Ï*/: return 'I';	// LATIN CAPITAL LETTER I WITH DIAERESIS
    case L'\x00D0'/*Ð*/: return 'D';	// LATIN CAPITAL LETTER ETH -- no decomposition  	// Eth [D for Vietnamese]
    case L'\x00D1'/*Ñ*/: return 'N';	// LATIN CAPITAL LETTER N WITH TILDE
    case L'\x00D2'/*Ò*/: return 'O';	// LATIN CAPITAL LETTER O WITH GRAVE
    case L'\x00D3'/*Ó*/: return 'O';	// LATIN CAPITAL LETTER O WITH ACUTE
    case L'\x00D4'/*Ô*/: return 'O';	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX
    case L'\x00D5'/*Õ*/: return 'O';	// LATIN CAPITAL LETTER O WITH TILDE
    case L'\x00D6'/*Ö*/: return 'O';	// LATIN CAPITAL LETTER O WITH DIAERESIS
    case L'\x00D8'/*Ø*/: return 'O';	// LATIN CAPITAL LETTER O WITH STROKE -- no decom
    case L'\x00D9'/*Ù*/: return 'U';	// LATIN CAPITAL LETTER U WITH GRAVE
    case L'\x00DA'/*Ú*/: return 'U';	// LATIN CAPITAL LETTER U WITH ACUTE
    case L'\x00DB'/*Û*/: return 'U';	// LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    case L'\x00DC'/*Ü*/: return 'U';	// LATIN CAPITAL LETTER U WITH DIAERESIS
    case L'\x00DD'/*Ý*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH ACUTE
    // case L'\x00DE'/*Þ*/: return 'Th';	// LATIN CAPITAL LETTER THORN -- no decomposition; // Thorn - Could be nothing other than thorn
    case L'\x00DF'/*ß*/: return 's';	// LATIN SMALL LETTER SHARP S -- no decomposition
    case L'\x00E0'/*à*/: return 'a';	// LATIN SMALL LETTER A WITH GRAVE
    case L'\x00E1'/*á*/: return 'a';	// LATIN SMALL LETTER A WITH ACUTE
    case L'\x00E2'/*â*/: return 'a';	// LATIN SMALL LETTER A WITH CIRCUMFLEX
    case L'\x00E3'/*ã*/: return 'a';	// LATIN SMALL LETTER A WITH TILDE
    case L'\x00E4'/*ä*/: return 'a';	// LATIN SMALL LETTER A WITH DIAERESIS
    case L'\x00E5'/*å*/: return 'a';	// LATIN SMALL LETTER A WITH RING ABOVE
    // case L'\x00E6'/*æ*/: return 'ae';	// LATIN SMALL LETTER AE -- no decomposition     ;
    case L'\x00E7'/*ç*/: return 'c';	// LATIN SMALL LETTER C WITH CEDILLA
    case L'\x00E8'/*è*/: return 'e';	// LATIN SMALL LETTER E WITH GRAVE
    case L'\x00E9'/*é*/: return 'e';	// LATIN SMALL LETTER E WITH ACUTE
    case L'\x00EA'/*ê*/: return 'e';	// LATIN SMALL LETTER E WITH CIRCUMFLEX
    case L'\x00EB'/*ë*/: return 'e';	// LATIN SMALL LETTER E WITH DIAERESIS
    case L'\x00EC'/*ì*/: return 'i';	// LATIN SMALL LETTER I WITH GRAVE
    case L'\x00ED'/*í*/: return 'i';	// LATIN SMALL LETTER I WITH ACUTE
    case L'\x00EE'/*î*/: return 'i';	// LATIN SMALL LETTER I WITH CIRCUMFLEX
    case L'\x00EF'/*ï*/: return 'i';	// LATIN SMALL LETTER I WITH DIAERESIS
    case L'\x00F0'/*ð*/: return 'd';	// LATIN SMALL LETTER ETH -- no decomposition         // small eth, "d" for benefit of Vietnamese
    case L'\x00F1'/*ñ*/: return 'n';	// LATIN SMALL LETTER N WITH TILDE
    case L'\x00F2'/*ò*/: return 'o';	// LATIN SMALL LETTER O WITH GRAVE
    case L'\x00F3'/*ó*/: return 'o';	// LATIN SMALL LETTER O WITH ACUTE
    case L'\x00F4'/*ô*/: return 'o';	// LATIN SMALL LETTER O WITH CIRCUMFLEX
    case L'\x00F5'/*õ*/: return 'o';	// LATIN SMALL LETTER O WITH TILDE
    case L'\x00F6'/*ö*/: return 'o';	// LATIN SMALL LETTER O WITH DIAERESIS
    case L'\x00F8'/*ø*/: return 'o';	// LATIN SMALL LETTER O WITH STROKE -- no decompo
    case L'\x00F9'/*ù*/: return 'u';	// LATIN SMALL LETTER U WITH GRAVE
    case L'\x00FA'/*ú*/: return 'u';	// LATIN SMALL LETTER U WITH ACUTE
    case L'\x00FB'/*û*/: return 'u';	// LATIN SMALL LETTER U WITH CIRCUMFLEX
    case L'\x00FC'/*ü*/: return 'u';	// LATIN SMALL LETTER U WITH DIAERESIS
    case L'\x00FD'/*ý*/: return 'y';	// LATIN SMALL LETTER Y WITH ACUTE
    // case L'\x00FE'/*þ*/: return 'th';	// LATIN SMALL LETTER THORN -- no decomposition  ;   // Small thorn
    case L'\x00FF'/*ÿ*/: return 'y';	// LATIN SMALL LETTER Y WITH DIAERESIS
    case L'\x0100'/*Ā*/: return 'A';	// LATIN CAPITAL LETTER A WITH MACRON
    case L'\x0101'/*ā*/: return 'a';	// LATIN SMALL LETTER A WITH MACRON
    case L'\x0102'/*Ă*/: return 'A';	// LATIN CAPITAL LETTER A WITH BREVE
    case L'\x0103'/*ă*/: return 'a';	// LATIN SMALL LETTER A WITH BREVE
    case L'\x0104'/*Ą*/: return 'A';	// LATIN CAPITAL LETTER A WITH OGONEK
    case L'\x0105'/*ą*/: return 'a';	// LATIN SMALL LETTER A WITH OGONEK
    case L'\x0106'/*Ć*/: return 'C';	// LATIN CAPITAL LETTER C WITH ACUTE
    case L'\x0107'/*ć*/: return 'c';	// LATIN SMALL LETTER C WITH ACUTE
    case L'\x0108'/*Ĉ*/: return 'C';	// LATIN CAPITAL LETTER C WITH CIRCUMFLEX
    case L'\x0109'/*ĉ*/: return 'c';	// LATIN SMALL LETTER C WITH CIRCUMFLEX
    case L'\x010A'/*Ċ*/: return 'C';	// LATIN CAPITAL LETTER C WITH DOT ABOVE
    case L'\x010B'/*ċ*/: return 'c';	// LATIN SMALL LETTER C WITH DOT ABOVE
    case L'\x010C'/*Č*/: return 'C';	// LATIN CAPITAL LETTER C WITH CARON
    case L'\x010D'/*č*/: return 'c';	// LATIN SMALL LETTER C WITH CARON
    case L'\x010E'/*Ď*/: return 'D';	// LATIN CAPITAL LETTER D WITH CARON
    case L'\x010F'/*ď*/: return 'd';	// LATIN SMALL LETTER D WITH CARON
    case L'\x0110'/*Đ*/: return 'D';	// LATIN CAPITAL LETTER D WITH STROKE -- no decomposition                     // Capital D with stroke
    case L'\x0111'/*đ*/: return 'd';	// LATIN SMALL LETTER D WITH STROKE -- no decomposition                       // small D with stroke
    case L'\x0112'/*Ē*/: return 'E';	// LATIN CAPITAL LETTER E WITH MACRON
    case L'\x0113'/*ē*/: return 'e';	// LATIN SMALL LETTER E WITH MACRON
    case L'\x0114'/*Ĕ*/: return 'E';	// LATIN CAPITAL LETTER E WITH BREVE
    case L'\x0115'/*ĕ*/: return 'e';	// LATIN SMALL LETTER E WITH BREVE
    case L'\x0116'/*Ė*/: return 'E';	// LATIN CAPITAL LETTER E WITH DOT ABOVE
    case L'\x0117'/*ė*/: return 'e';	// LATIN SMALL LETTER E WITH DOT ABOVE
    case L'\x0118'/*Ę*/: return 'E';	// LATIN CAPITAL LETTER E WITH OGONEK
    case L'\x0119'/*ę*/: return 'e';	// LATIN SMALL LETTER E WITH OGONEK
    case L'\x011A'/*Ě*/: return 'E';	// LATIN CAPITAL LETTER E WITH CARON
    case L'\x011B'/*ě*/: return 'e';	// LATIN SMALL LETTER E WITH CARON
    case L'\x011C'/*Ĝ*/: return 'G';	// LATIN CAPITAL LETTER G WITH CIRCUMFLEX
    case L'\x011D'/*ĝ*/: return 'g';	// LATIN SMALL LETTER G WITH CIRCUMFLEX
    case L'\x011E'/*Ğ*/: return 'G';	// LATIN CAPITAL LETTER G WITH BREVE
    case L'\x011F'/*ğ*/: return 'g';	// LATIN SMALL LETTER G WITH BREVE
    case L'\x0120'/*Ġ*/: return 'G';	// LATIN CAPITAL LETTER G WITH DOT ABOVE
    case L'\x0121'/*ġ*/: return 'g';	// LATIN SMALL LETTER G WITH DOT ABOVE
    case L'\x0122'/*Ģ*/: return 'G';	// LATIN CAPITAL LETTER G WITH CEDILLA
    case L'\x0123'/*ģ*/: return 'g';	// LATIN SMALL LETTER G WITH CEDILLA
    case L'\x0124'/*Ĥ*/: return 'H';	// LATIN CAPITAL LETTER H WITH CIRCUMFLEX
    case L'\x0125'/*ĥ*/: return 'h';	// LATIN SMALL LETTER H WITH CIRCUMFLEX
    case L'\x0126'/*Ħ*/: return 'H';	// LATIN CAPITAL LETTER H WITH STROKE -- no decomposition
    case L'\x0127'/*ħ*/: return 'h';	// LATIN SMALL LETTER H WITH STROKE -- no decomposition
    case L'\x0128'/*Ĩ*/: return 'I';	// LATIN CAPITAL LETTER I WITH TILDE
    case L'\x0129'/*ĩ*/: return 'i';	// LATIN SMALL LETTER I WITH TILDE
    case L'\x012A'/*Ī*/: return 'I';	// LATIN CAPITAL LETTER I WITH MACRON
    case L'\x012B'/*ī*/: return 'i';	// LATIN SMALL LETTER I WITH MACRON
    case L'\x012C'/*Ĭ*/: return 'I';	// LATIN CAPITAL LETTER I WITH BREVE
    case L'\x012D'/*ĭ*/: return 'i';	// LATIN SMALL LETTER I WITH BREVE
    case L'\x012E'/*Į*/: return 'I';	// LATIN CAPITAL LETTER I WITH OGONEK
    case L'\x012F'/*į*/: return 'i';	// LATIN SMALL LETTER I WITH OGONEK
    case L'\x0130'/*İ*/: return 'I';	// LATIN CAPITAL LETTER I WITH DOT ABOVE
    case L'\x0131'/*ı*/: return 'i';	// LATIN SMALL LETTER DOTLESS I -- no decomposition
    case L'\x0132'/*Ĳ*/: return 'I';	// LATIN CAPITAL LIGATURE IJ
    case L'\x0133'/*ĳ*/: return 'i';	// LATIN SMALL LIGATURE IJ
    case L'\x0134'/*Ĵ*/: return 'J';	// LATIN CAPITAL LETTER J WITH CIRCUMFLEX
    case L'\x0135'/*ĵ*/: return 'j';	// LATIN SMALL LETTER J WITH CIRCUMFLEX
    case L'\x0136'/*Ķ*/: return 'K';	// LATIN CAPITAL LETTER K WITH CEDILLA
    case L'\x0137'/*ķ*/: return 'k';	// LATIN SMALL LETTER K WITH CEDILLA
    case L'\x0138'/*ĸ*/: return 'k';	// LATIN SMALL LETTER KRA -- no decomposition
    case L'\x0139'/*Ĺ*/: return 'L';	// LATIN CAPITAL LETTER L WITH ACUTE
    case L'\x013A'/*ĺ*/: return 'l';	// LATIN SMALL LETTER L WITH ACUTE
    case L'\x013B'/*Ļ*/: return 'L';	// LATIN CAPITAL LETTER L WITH CEDILLA
    case L'\x013C'/*ļ*/: return 'l';	// LATIN SMALL LETTER L WITH CEDILLA
    case L'\x013D'/*Ľ*/: return 'L';	// LATIN CAPITAL LETTER L WITH CARON
    case L'\x013E'/*ľ*/: return 'l';	// LATIN SMALL LETTER L WITH CARON
    case L'\x013F'/*Ŀ*/: return 'L';	// LATIN CAPITAL LETTER L WITH MIDDLE DOT
    case L'\x0140'/*ŀ*/: return 'l';	// LATIN SMALL LETTER L WITH MIDDLE DOT
    case L'\x0141'/*Ł*/: return 'L';	// LATIN CAPITAL LETTER L WITH STROKE -- no decomposition
    case L'\x0142'/*ł*/: return 'l';	// LATIN SMALL LETTER L WITH STROKE -- no decomposition
    case L'\x0143'/*Ń*/: return 'N';	// LATIN CAPITAL LETTER N WITH ACUTE
    case L'\x0144'/*ń*/: return 'n';	// LATIN SMALL LETTER N WITH ACUTE
    case L'\x0145'/*Ņ*/: return 'N';	// LATIN CAPITAL LETTER N WITH CEDILLA
    case L'\x0146'/*ņ*/: return 'n';	// LATIN SMALL LETTER N WITH CEDILLA
    case L'\x0147'/*Ň*/: return 'N';	// LATIN CAPITAL LETTER N WITH CARON
    case L'\x0148'/*ň*/: return 'n';	// LATIN SMALL LETTER N WITH CARON
    // case L'\x0149'/*ŉ*/: return ''n';	// LATIN SMALL LETTER N PRECEDED BY APOSTROPHE                              ;
    // case L'\x014A'/*Ŋ*/: return 'NG';	// LATIN CAPITAL LETTER ENG -- no decomposition                             ;
    // case L'\x014B'/*ŋ*/: return 'ng';	// LATIN SMALL LETTER ENG -- no decomposition                               ;
    case L'\x014C'/*Ō*/: return 'O';	// LATIN CAPITAL LETTER O WITH MACRON
    case L'\x014D'/*ō*/: return 'o';	// LATIN SMALL LETTER O WITH MACRON
    case L'\x014E'/*Ŏ*/: return 'O';	// LATIN CAPITAL LETTER O WITH BREVE
    case L'\x014F'/*ŏ*/: return 'o';	// LATIN SMALL LETTER O WITH BREVE
    case L'\x0150'/*Ő*/: return 'O';	// LATIN CAPITAL LETTER O WITH DOUBLE ACUTE
    case L'\x0151'/*ő*/: return 'o';	// LATIN SMALL LETTER O WITH DOUBLE ACUTE
    // case L'\x0152'/*Œ*/: return 'OE';	// LATIN CAPITAL LIGATURE OE -- no decomposition
    // case L'\x0153'/*œ*/: return 'oe';	// LATIN SMALL LIGATURE OE -- no decomposition
    case L'\x0154'/*Ŕ*/: return 'R';	// LATIN CAPITAL LETTER R WITH ACUTE
    case L'\x0155'/*ŕ*/: return 'r';	// LATIN SMALL LETTER R WITH ACUTE
    case L'\x0156'/*Ŗ*/: return 'R';	// LATIN CAPITAL LETTER R WITH CEDILLA
    case L'\x0157'/*ŗ*/: return 'r';	// LATIN SMALL LETTER R WITH CEDILLA
    case L'\x0158'/*Ř*/: return 'R';	// LATIN CAPITAL LETTER R WITH CARON
    case L'\x0159'/*ř*/: return 'r';	// LATIN SMALL LETTER R WITH CARON
    case L'\x015A'/*Ś*/: return 'S';	// LATIN CAPITAL LETTER S WITH ACUTE
    case L'\x015B'/*ś*/: return 's';	// LATIN SMALL LETTER S WITH ACUTE
    case L'\x015C'/*Ŝ*/: return 'S';	// LATIN CAPITAL LETTER S WITH CIRCUMFLEX
    case L'\x015D'/*ŝ*/: return 's';	// LATIN SMALL LETTER S WITH CIRCUMFLEX
    case L'\x015E'/*Ş*/: return 'S';	// LATIN CAPITAL LETTER S WITH CEDILLA
    case L'\x015F'/*ş*/: return 's';	// LATIN SMALL LETTER S WITH CEDILLA
    case L'\x0160'/*Š*/: return 'S';	// LATIN CAPITAL LETTER S WITH CARON
    case L'\x0161'/*š*/: return 's';	// LATIN SMALL LETTER S WITH CARON
    case L'\x0162'/*Ţ*/: return 'T';	// LATIN CAPITAL LETTER T WITH CEDILLA
    case L'\x0163'/*ţ*/: return 't';	// LATIN SMALL LETTER T WITH CEDILLA
    case L'\x0164'/*Ť*/: return 'T';	// LATIN CAPITAL LETTER T WITH CARON
    case L'\x0165'/*ť*/: return 't';	// LATIN SMALL LETTER T WITH CARON
    case L'\x0166'/*Ŧ*/: return 'T';	// LATIN CAPITAL LETTER T WITH STROKE -- no decomposition
    case L'\x0167'/*ŧ*/: return 't';	// LATIN SMALL LETTER T WITH STROKE -- no decomposition
    case L'\x0168'/*Ũ*/: return 'U';	// LATIN CAPITAL LETTER U WITH TILDE
    case L'\x0169'/*ũ*/: return 'u';	// LATIN SMALL LETTER U WITH TILDE
    case L'\x016A'/*Ū*/: return 'U';	// LATIN CAPITAL LETTER U WITH MACRON
    case L'\x016B'/*ū*/: return 'u';	// LATIN SMALL LETTER U WITH MACRON
    case L'\x016C'/*Ŭ*/: return 'U';	// LATIN CAPITAL LETTER U WITH BREVE
    case L'\x016D'/*ŭ*/: return 'u';	// LATIN SMALL LETTER U WITH BREVE
    case L'\x016E'/*Ů*/: return 'U';	// LATIN CAPITAL LETTER U WITH RING ABOVE
    case L'\x016F'/*ů*/: return 'u';	// LATIN SMALL LETTER U WITH RING ABOVE
    case L'\x0170'/*Ű*/: return 'U';	// LATIN CAPITAL LETTER U WITH DOUBLE ACUTE
    case L'\x0171'/*ű*/: return 'u';	// LATIN SMALL LETTER U WITH DOUBLE ACUTE
    case L'\x0172'/*Ų*/: return 'U';	// LATIN CAPITAL LETTER U WITH OGONEK
    case L'\x0173'/*ų*/: return 'u';	// LATIN SMALL LETTER U WITH OGONEK
    case L'\x0174'/*Ŵ*/: return 'W';	// LATIN CAPITAL LETTER W WITH CIRCUMFLEX
    case L'\x0175'/*ŵ*/: return 'w';	// LATIN SMALL LETTER W WITH CIRCUMFLEX
    case L'\x0176'/*Ŷ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH CIRCUMFLEX
    case L'\x0177'/*ŷ*/: return 'y';	// LATIN SMALL LETTER Y WITH CIRCUMFLEX
    case L'\x0178'/*Ÿ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH DIAERESIS
    case L'\x0179'/*Ź*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH ACUTE
    case L'\x017A'/*ź*/: return 'z';	// LATIN SMALL LETTER Z WITH ACUTE
    case L'\x017B'/*Ż*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH DOT ABOVE
    case L'\x017C'/*ż*/: return 'z';	// LATIN SMALL LETTER Z WITH DOT ABOVE
    case L'\x017D'/*Ž*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH CARON
    case L'\x017E'/*ž*/: return 'z';	// LATIN SMALL LETTER Z WITH CARON
    case L'\x017F'/*ſ*/: return 's';	// LATIN SMALL LETTER LONG S
    case L'\x0180'/*ƀ*/: return 'b';	// LATIN SMALL LETTER B WITH STROKE -- no decomposition
    case L'\x0181'/*Ɓ*/: return 'B';	// LATIN CAPITAL LETTER B WITH HOOK -- no decomposition
    case L'\x0182'/*Ƃ*/: return 'B';	// LATIN CAPITAL LETTER B WITH TOPBAR -- no decomposition
    case L'\x0183'/*ƃ*/: return 'b';	// LATIN SMALL LETTER B WITH TOPBAR -- no decomposition
    case L'\x0184'/*Ƅ*/: return '6';	// LATIN CAPITAL LETTER TONE SIX -- no decomposition
    case L'\x0185'/*ƅ*/: return '6';	// LATIN SMALL LETTER TONE SIX -- no decomposition
    case L'\x0186'/*Ɔ*/: return 'O';	// LATIN CAPITAL LETTER OPEN O -- no decomposition
    case L'\x0187'/*Ƈ*/: return 'C';	// LATIN CAPITAL LETTER C WITH HOOK -- no decomposition
    case L'\x0188'/*ƈ*/: return 'c';	// LATIN SMALL LETTER C WITH HOOK -- no decomposition
    case L'\x0189'/*Ɖ*/: return 'D';	// LATIN CAPITAL LETTER AFRICAN D -- no decomposition
    case L'\x018A'/*Ɗ*/: return 'D';	// LATIN CAPITAL LETTER D WITH HOOK -- no decomposition
    case L'\x018B'/*Ƌ*/: return 'D';	// LATIN CAPITAL LETTER D WITH TOPBAR -- no decomposition
    case L'\x018C'/*ƌ*/: return 'd';	// LATIN SMALL LETTER D WITH TOPBAR -- no decomposition
    case L'\x018D'/*ƍ*/: return 'd';	// LATIN SMALL LETTER TURNED DELTA -- no decomposition
    case L'\x018E'/*Ǝ*/: return 'E';	// LATIN CAPITAL LETTER REVERSED E -- no decomposition
    case L'\x018F'/*Ə*/: return 'E';	// LATIN CAPITAL LETTER SCHWA -- no decomposition
    case L'\x0190'/*Ɛ*/: return 'E';	// LATIN CAPITAL LETTER OPEN E -- no decomposition
    case L'\x0191'/*Ƒ*/: return 'F';	// LATIN CAPITAL LETTER F WITH HOOK -- no decomposition
    case L'\x0192'/*ƒ*/: return 'f';	// LATIN SMALL LETTER F WITH HOOK -- no decomposition
    case L'\x0193'/*Ɠ*/: return 'G';	// LATIN CAPITAL LETTER G WITH HOOK -- no decomposition
    case L'\x0194'/*Ɣ*/: return 'G';	// LATIN CAPITAL LETTER GAMMA -- no decomposition
    // case L'\x0195'/*ƕ*/: return 'hv';	// LATIN SMALL LETTER HV -- no decomposition
    case L'\x0196'/*Ɩ*/: return 'I';	// LATIN CAPITAL LETTER IOTA -- no decomposition
    case L'\x0197'/*Ɨ*/: return 'I';	// LATIN CAPITAL LETTER I WITH STROKE -- no decomposition
    case L'\x0198'/*Ƙ*/: return 'K';	// LATIN CAPITAL LETTER K WITH HOOK -- no decomposition
    case L'\x0199'/*ƙ*/: return 'k';	// LATIN SMALL LETTER K WITH HOOK -- no decomposition
    case L'\x019A'/*ƚ*/: return 'l';	// LATIN SMALL LETTER L WITH BAR -- no decomposition
    case L'\x019B'/*ƛ*/: return 'l';	// LATIN SMALL LETTER LAMBDA WITH STROKE -- no decomposition
    case L'\x019C'/*Ɯ*/: return 'M';	// LATIN CAPITAL LETTER TURNED M -- no decomposition
    case L'\x019D'/*Ɲ*/: return 'N';	// LATIN CAPITAL LETTER N WITH LEFT HOOK -- no decomposition
    case L'\x019E'/*ƞ*/: return 'n';	// LATIN SMALL LETTER N WITH LONG RIGHT LEG -- no decomposition
    case L'\x019F'/*Ɵ*/: return 'O';	// LATIN CAPITAL LETTER O WITH MIDDLE TILDE -- no decomposition
    case L'\x01A0'/*Ơ*/: return 'O';	// LATIN CAPITAL LETTER O WITH HORN
    case L'\x01A1'/*ơ*/: return 'o';	// LATIN SMALL LETTER O WITH HORN
    // case L'\x01A2'/*Ƣ*/: return 'OI';	// LATIN CAPITAL LETTER OI -- no decomposition
    // case L'\x01A3'/*ƣ*/: return 'oi';	// LATIN SMALL LETTER OI -- no decomposition
    case L'\x01A4'/*Ƥ*/: return 'P';	// LATIN CAPITAL LETTER P WITH HOOK -- no decomposition
    case L'\x01A5'/*ƥ*/: return 'p';	// LATIN SMALL LETTER P WITH HOOK -- no decomposition
    // case L'\x01A6'/*Ʀ*/: return 'YR';	// LATIN LETTER YR -- no decomposition
    case L'\x01A7'/*Ƨ*/: return '2';	// LATIN CAPITAL LETTER TONE TWO -- no decomposition
    case L'\x01A8'/*ƨ*/: return '2';	// LATIN SMALL LETTER TONE TWO -- no decomposition
    case L'\x01A9'/*Ʃ*/: return 'S';	// LATIN CAPITAL LETTER ESH -- no decomposition
    case L'\x01AA'/*ƪ*/: return 's';	// LATIN LETTER REVERSED ESH LOOP -- no decomposition
    case L'\x01AB'/*ƫ*/: return 't';	// LATIN SMALL LETTER T WITH PALATAL HOOK -- no decomposition
    case L'\x01AC'/*Ƭ*/: return 'T';	// LATIN CAPITAL LETTER T WITH HOOK -- no decomposition
    case L'\x01AD'/*ƭ*/: return 't';	// LATIN SMALL LETTER T WITH HOOK -- no decomposition
    case L'\x01AE'/*Ʈ*/: return 'T';	// LATIN CAPITAL LETTER T WITH RETROFLEX HOOK -- no decomposition
    case L'\x01AF'/*Ư*/: return 'U';	// LATIN CAPITAL LETTER U WITH HORN
    case L'\x01B0'/*ư*/: return 'u';	// LATIN SMALL LETTER U WITH HORN
    case L'\x01B1'/*Ʊ*/: return 'u';	// LATIN CAPITAL LETTER UPSILON -- no decomposition
    case L'\x01B2'/*Ʋ*/: return 'V';	// LATIN CAPITAL LETTER V WITH HOOK -- no decomposition
    case L'\x01B3'/*Ƴ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH HOOK -- no decomposition
    case L'\x01B4'/*ƴ*/: return 'y';	// LATIN SMALL LETTER Y WITH HOOK -- no decomposition
    case L'\x01B5'/*Ƶ*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH STROKE -- no decomposition
    case L'\x01B6'/*ƶ*/: return 'z';	// LATIN SMALL LETTER Z WITH STROKE -- no decomposition
    case L'\x01B7'/*Ʒ*/: return 'Z';	// LATIN CAPITAL LETTER EZH -- no decomposition
    case L'\x01B8'/*Ƹ*/: return 'Z';	// LATIN CAPITAL LETTER EZH REVERSED -- no decomposition
    case L'\x01B9'/*ƹ*/: return 'Z';	// LATIN SMALL LETTER EZH REVERSED -- no decomposition
    case L'\x01BA'/*ƺ*/: return 'z';	// LATIN SMALL LETTER EZH WITH TAIL -- no decomposition
    case L'\x01BB'/*ƻ*/: return '2';	// LATIN LETTER TWO WITH STROKE -- no decomposition
    case L'\x01BC'/*Ƽ*/: return '5';	// LATIN CAPITAL LETTER TONE FIVE -- no decomposition
    case L'\x01BD'/*ƽ*/: return '5';	// LATIN SMALL LETTER TONE FIVE -- no decomposition
    case L'\x01BE'/*ƾ*/: return '\'';	// LATIN LETTER INVERTED GLOTTAL STOP WITH STROKE -- no decomposition
    case L'\x01BF'/*ƿ*/: return 'w';	// LATIN LETTER WYNN -- no decomposition
    case L'\x01C0'/*ǀ*/: return '!';	// LATIN LETTER DENTAL CLICK -- no decomposition
    case L'\x01C1'/*ǁ*/: return '!';	// LATIN LETTER LATERAL CLICK -- no decomposition
    case L'\x01C2'/*ǂ*/: return '!';	// LATIN LETTER ALVEOLAR CLICK -- no decomposition
    case L'\x01C3'/*ǃ*/: return '!';	// LATIN LETTER RETROFLEX CLICK -- no decomposition
    // case L'\x01C4'/*Ǆ*/: return 'DZ';	// LATIN CAPITAL LETTER DZ WITH CARON
    // case L'\x01C5'/*ǅ*/: return 'DZ';	// LATIN CAPITAL LETTER D WITH SMALL LETTER Z WITH CARON
    case L'\x01C6'/*ǆ*/: return 'd';	// LATIN SMALL LETTER DZ WITH CARON
    // case L'\x01C7'/*Ǉ*/: return 'Lj';	// LATIN CAPITAL LETTER LJ
    // case L'\x01C8'/*ǈ*/: return 'Lj';	// LATIN CAPITAL LETTER L WITH SMALL LETTER J
    // case L'\x01C9'/*ǉ*/: return 'lj';	// LATIN SMALL LETTER LJ
    // case L'\x01CA'/*Ǌ*/: return 'NJ';	// LATIN CAPITAL LETTER NJ
    // case L'\x01CB'/*ǋ*/: return 'NJ';	// LATIN CAPITAL LETTER N WITH SMALL LETTER J
    // case L'\x01CC'/*ǌ*/: return 'nj';	// LATIN SMALL LETTER NJ
    case L'\x01CD'/*Ǎ*/: return 'A';	// LATIN CAPITAL LETTER A WITH CARON
    case L'\x01CE'/*ǎ*/: return 'a';	// LATIN SMALL LETTER A WITH CARON
    case L'\x01CF'/*Ǐ*/: return 'I';	// LATIN CAPITAL LETTER I WITH CARON
    case L'\x01D0'/*ǐ*/: return 'i';	// LATIN SMALL LETTER I WITH CARON
    case L'\x01D1'/*Ǒ*/: return 'O';	// LATIN CAPITAL LETTER O WITH CARON
    case L'\x01D2'/*ǒ*/: return 'o';	// LATIN SMALL LETTER O WITH CARON
    case L'\x01D3'/*Ǔ*/: return 'U';	// LATIN CAPITAL LETTER U WITH CARON
    case L'\x01D4'/*ǔ*/: return 'u';	// LATIN SMALL LETTER U WITH CARON
    case L'\x01D5'/*Ǖ*/: return 'U';	// LATIN CAPITAL LETTER U WITH DIAERESIS AND MACRON
    case L'\x01D6'/*ǖ*/: return 'u';	// LATIN SMALL LETTER U WITH DIAERESIS AND MACRON
    case L'\x01D7'/*Ǘ*/: return 'U';	// LATIN CAPITAL LETTER U WITH DIAERESIS AND ACUTE
    case L'\x01D8'/*ǘ*/: return 'u';	// LATIN SMALL LETTER U WITH DIAERESIS AND ACUTE
    case L'\x01D9'/*Ǚ*/: return 'U';	// LATIN CAPITAL LETTER U WITH DIAERESIS AND CARON
    case L'\x01DA'/*ǚ*/: return 'u';	// LATIN SMALL LETTER U WITH DIAERESIS AND CARON
    case L'\x01DB'/*Ǜ*/: return 'U';	// LATIN CAPITAL LETTER U WITH DIAERESIS AND GRAVE
    case L'\x01DC'/*ǜ*/: return 'u';	// LATIN SMALL LETTER U WITH DIAERESIS AND GRAVE
    case L'\x01DD'/*ǝ*/: return 'e';	// LATIN SMALL LETTER TURNED E -- no decomposition
    case L'\x01DE'/*Ǟ*/: return 'A';	// LATIN CAPITAL LETTER A WITH DIAERESIS AND MACRON
    case L'\x01DF'/*ǟ*/: return 'a';	// LATIN SMALL LETTER A WITH DIAERESIS AND MACRON
    case L'\x01E0'/*Ǡ*/: return 'A';	// LATIN CAPITAL LETTER A WITH DOT ABOVE AND MACRON
    case L'\x01E1'/*ǡ*/: return 'a';	// LATIN SMALL LETTER A WITH DOT ABOVE AND MACRON
    // case L'\x01E2'/*Ǣ*/: return 'AE';	// LATIN CAPITAL LETTER AE WITH MACRON
    // case L'\x01E3'/*ǣ*/: return 'ae';	// LATIN SMALL LETTER AE WITH MACRON
    case L'\x01E4'/*Ǥ*/: return 'G';	// LATIN CAPITAL LETTER G WITH STROKE -- no decomposition
    case L'\x01E5'/*ǥ*/: return 'g';	// LATIN SMALL LETTER G WITH STROKE -- no decomposition
    case L'\x01E6'/*Ǧ*/: return 'G';	// LATIN CAPITAL LETTER G WITH CARON
    case L'\x01E7'/*ǧ*/: return 'g';	// LATIN SMALL LETTER G WITH CARON
    case L'\x01E8'/*Ǩ*/: return 'K';	// LATIN CAPITAL LETTER K WITH CARON
    case L'\x01E9'/*ǩ*/: return 'k';	// LATIN SMALL LETTER K WITH CARON
    case L'\x01EA'/*Ǫ*/: return 'O';	// LATIN CAPITAL LETTER O WITH OGONEK
    case L'\x01EB'/*ǫ*/: return 'o';	// LATIN SMALL LETTER O WITH OGONEK
    case L'\x01EC'/*Ǭ*/: return 'O';	// LATIN CAPITAL LETTER O WITH OGONEK AND MACRON
    case L'\x01ED'/*ǭ*/: return 'o';	// LATIN SMALL LETTER O WITH OGONEK AND MACRON
    case L'\x01EE'/*Ǯ*/: return 'Z';	// LATIN CAPITAL LETTER EZH WITH CARON
    case L'\x01EF'/*ǯ*/: return 'Z';	// LATIN SMALL LETTER EZH WITH CARON
    case L'\x01F0'/*ǰ*/: return 'j';	// LATIN SMALL LETTER J WITH CARON
    // case L'\x01F1'/*Ǳ*/: return 'DZ';	// LATIN CAPITAL LETTER DZ
    // case L'\x01F2'/*ǲ*/: return 'DZ';	// LATIN CAPITAL LETTER D WITH SMALL LETTER Z
    // case L'\x01F3'/*ǳ*/: return 'dz';	// LATIN SMALL LETTER DZ
    case L'\x01F4'/*Ǵ*/: return 'G';	// LATIN CAPITAL LETTER G WITH ACUTE
    case L'\x01F5'/*ǵ*/: return 'g';	// LATIN SMALL LETTER G WITH ACUTE
    // case L'\x01F6'/*Ƕ*/: return 'hv';	// LATIN CAPITAL LETTER HWAIR -- no decomposition
    case L'\x01F7'/*Ƿ*/: return 'w';	// LATIN CAPITAL LETTER WYNN -- no decomposition
    case L'\x01F8'/*Ǹ*/: return 'N';	// LATIN CAPITAL LETTER N WITH GRAVE
    case L'\x01F9'/*ǹ*/: return 'n';	// LATIN SMALL LETTER N WITH GRAVE
    case L'\x01FA'/*Ǻ*/: return 'A';	// LATIN CAPITAL LETTER A WITH RING ABOVE AND ACUTE
    case L'\x01FB'/*ǻ*/: return 'a';	// LATIN SMALL LETTER A WITH RING ABOVE AND ACUTE
    // case L'\x01FC'/*Ǽ*/: return 'AE';	// LATIN CAPITAL LETTER AE WITH ACUTE
    // case L'\x01FD'/*ǽ*/: return 'ae';	// LATIN SMALL LETTER AE WITH ACUTE
    case L'\x01FE'/*Ǿ*/: return 'O';	// LATIN CAPITAL LETTER O WITH STROKE AND ACUTE
    case L'\x01FF'/*ǿ*/: return 'o';	// LATIN SMALL LETTER O WITH STROKE AND ACUTE
    case L'\x0200'/*Ȁ*/: return 'A';	// LATIN CAPITAL LETTER A WITH DOUBLE GRAVE
    case L'\x0201'/*ȁ*/: return 'a';	// LATIN SMALL LETTER A WITH DOUBLE GRAVE
    case L'\x0202'/*Ȃ*/: return 'A';	// LATIN CAPITAL LETTER A WITH INVERTED BREVE
    case L'\x0203'/*ȃ*/: return 'a';	// LATIN SMALL LETTER A WITH INVERTED BREVE
    case L'\x0204'/*Ȅ*/: return 'E';	// LATIN CAPITAL LETTER E WITH DOUBLE GRAVE
    case L'\x0205'/*ȅ*/: return 'e';	// LATIN SMALL LETTER E WITH DOUBLE GRAVE
    case L'\x0206'/*Ȇ*/: return 'E';	// LATIN CAPITAL LETTER E WITH INVERTED BREVE
    case L'\x0207'/*ȇ*/: return 'e';	// LATIN SMALL LETTER E WITH INVERTED BREVE
    case L'\x0208'/*Ȉ*/: return 'I';	// LATIN CAPITAL LETTER I WITH DOUBLE GRAVE
    case L'\x0209'/*ȉ*/: return 'i';	// LATIN SMALL LETTER I WITH DOUBLE GRAVE
    case L'\x020A'/*Ȋ*/: return 'I';	// LATIN CAPITAL LETTER I WITH INVERTED BREVE
    case L'\x020B'/*ȋ*/: return 'i';	// LATIN SMALL LETTER I WITH INVERTED BREVE
    case L'\x020C'/*Ȍ*/: return 'O';	// LATIN CAPITAL LETTER O WITH DOUBLE GRAVE
    case L'\x020D'/*ȍ*/: return 'o';	// LATIN SMALL LETTER O WITH DOUBLE GRAVE
    case L'\x020E'/*Ȏ*/: return 'O';	// LATIN CAPITAL LETTER O WITH INVERTED BREVE
    case L'\x020F'/*ȏ*/: return 'o';	// LATIN SMALL LETTER O WITH INVERTED BREVE
    case L'\x0210'/*Ȑ*/: return 'R';	// LATIN CAPITAL LETTER R WITH DOUBLE GRAVE
    case L'\x0211'/*ȑ*/: return 'r';	// LATIN SMALL LETTER R WITH DOUBLE GRAVE
    case L'\x0212'/*Ȓ*/: return 'R';	// LATIN CAPITAL LETTER R WITH INVERTED BREVE
    case L'\x0213'/*ȓ*/: return 'r';	// LATIN SMALL LETTER R WITH INVERTED BREVE
    case L'\x0214'/*Ȕ*/: return 'U';	// LATIN CAPITAL LETTER U WITH DOUBLE GRAVE
    case L'\x0215'/*ȕ*/: return 'u';	// LATIN SMALL LETTER U WITH DOUBLE GRAVE
    case L'\x0216'/*Ȗ*/: return 'U';	// LATIN CAPITAL LETTER U WITH INVERTED BREVE
    case L'\x0217'/*ȗ*/: return 'u';	// LATIN SMALL LETTER U WITH INVERTED BREVE
    case L'\x0218'/*Ș*/: return 'S';	// LATIN CAPITAL LETTER S WITH COMMA BELOW
    case L'\x0219'/*ș*/: return 's';	// LATIN SMALL LETTER S WITH COMMA BELOW
    case L'\x021A'/*Ț*/: return 'T';	// LATIN CAPITAL LETTER T WITH COMMA BELOW
    case L'\x021B'/*ț*/: return 't';	// LATIN SMALL LETTER T WITH COMMA BELOW
    case L'\x021C'/*Ȝ*/: return 'Z';	// LATIN CAPITAL LETTER YOGH -- no decomposition
    case L'\x021D'/*ȝ*/: return 'z';	// LATIN SMALL LETTER YOGH -- no decomposition
    case L'\x021E'/*Ȟ*/: return 'H';	// LATIN CAPITAL LETTER H WITH CARON
    case L'\x021F'/*ȟ*/: return 'h';	// LATIN SMALL LETTER H WITH CARON
    case L'\x0220'/*Ƞ*/: return 'N';	// LATIN CAPITAL LETTER N WITH LONG RIGHT LEG -- no decomposition
    case L'\x0221'/*ȡ*/: return 'd';	// LATIN SMALL LETTER D WITH CURL -- no decomposition
    // case L'\x0222'/*Ȣ*/: return 'OU';	// LATIN CAPITAL LETTER OU -- no decomposition
    // case L'\x0223'/*ȣ*/: return 'ou';	// LATIN SMALL LETTER OU -- no decomposition
    case L'\x0224'/*Ȥ*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH HOOK -- no decomposition
    case L'\x0225'/*ȥ*/: return 'z';	// LATIN SMALL LETTER Z WITH HOOK -- no decomposition
    case L'\x0226'/*Ȧ*/: return 'A';	// LATIN CAPITAL LETTER A WITH DOT ABOVE
    case L'\x0227'/*ȧ*/: return 'a';	// LATIN SMALL LETTER A WITH DOT ABOVE
    case L'\x0228'/*Ȩ*/: return 'E';	// LATIN CAPITAL LETTER E WITH CEDILLA
    case L'\x0229'/*ȩ*/: return 'e';	// LATIN SMALL LETTER E WITH CEDILLA
    case L'\x022A'/*Ȫ*/: return 'O';	// LATIN CAPITAL LETTER O WITH DIAERESIS AND MACRON
    case L'\x022B'/*ȫ*/: return 'o';	// LATIN SMALL LETTER O WITH DIAERESIS AND MACRON
    case L'\x022C'/*Ȭ*/: return 'O';	// LATIN CAPITAL LETTER O WITH TILDE AND MACRON
    case L'\x022D'/*ȭ*/: return 'o';	// LATIN SMALL LETTER O WITH TILDE AND MACRON
    case L'\x022E'/*Ȯ*/: return 'O';	// LATIN CAPITAL LETTER O WITH DOT ABOVE
    case L'\x022F'/*ȯ*/: return 'o';	// LATIN SMALL LETTER O WITH DOT ABOVE
    case L'\x0230'/*Ȱ*/: return 'O';	// LATIN CAPITAL LETTER O WITH DOT ABOVE AND MACRON
    case L'\x0231'/*ȱ*/: return 'o';	// LATIN SMALL LETTER O WITH DOT ABOVE AND MACRON
    case L'\x0232'/*Ȳ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH MACRON
    case L'\x0233'/*ȳ*/: return 'y';	// LATIN SMALL LETTER Y WITH MACRON
    case L'\x0234'/*ȴ*/: return 'l';	// LATIN SMALL LETTER L WITH CURL -- no decomposition
    case L'\x0235'/*ȵ*/: return 'n';	// LATIN SMALL LETTER N WITH CURL -- no decomposition
    case L'\x0236'/*ȶ*/: return 't';	// LATIN SMALL LETTER T WITH CURL -- no decomposition
    case L'\x0250'/*ɐ*/: return 'a';	// LATIN SMALL LETTER TURNED A -- no decomposition
    case L'\x0251'/*ɑ*/: return 'a';	// LATIN SMALL LETTER ALPHA -- no decomposition
    case L'\x0252'/*ɒ*/: return 'a';	// LATIN SMALL LETTER TURNED ALPHA -- no decomposition
    case L'\x0253'/*ɓ*/: return 'b';	// LATIN SMALL LETTER B WITH HOOK -- no decomposition
    case L'\x0254'/*ɔ*/: return 'o';	// LATIN SMALL LETTER OPEN O -- no decomposition
    case L'\x0255'/*ɕ*/: return 'c';	// LATIN SMALL LETTER C WITH CURL -- no decomposition
    case L'\x0256'/*ɖ*/: return 'd';	// LATIN SMALL LETTER D WITH TAIL -- no decomposition
    case L'\x0257'/*ɗ*/: return 'd';	// LATIN SMALL LETTER D WITH HOOK -- no decomposition
    case L'\x0258'/*ɘ*/: return 'e';	// LATIN SMALL LETTER REVERSED E -- no decomposition
    case L'\x0259'/*ə*/: return 'e';	// LATIN SMALL LETTER SCHWA -- no decomposition
    case L'\x025A'/*ɚ*/: return 'e';	// LATIN SMALL LETTER SCHWA WITH HOOK -- no decomposition
    case L'\x025B'/*ɛ*/: return 'e';	// LATIN SMALL LETTER OPEN E -- no decomposition
    case L'\x025C'/*ɜ*/: return 'e';	// LATIN SMALL LETTER REVERSED OPEN E -- no decomposition
    case L'\x025D'/*ɝ*/: return 'e';	// LATIN SMALL LETTER REVERSED OPEN E WITH HOOK -- no decomposition
    case L'\x025E'/*ɞ*/: return 'e';	// LATIN SMALL LETTER CLOSED REVERSED OPEN E -- no decomposition
    case L'\x025F'/*ɟ*/: return 'j';	// LATIN SMALL LETTER DOTLESS J WITH STROKE -- no decomposition
    case L'\x0260'/*ɠ*/: return 'g';	// LATIN SMALL LETTER G WITH HOOK -- no decomposition
    case L'\x0261'/*ɡ*/: return 'g';	// LATIN SMALL LETTER SCRIPT G -- no decomposition
    case L'\x0262'/*ɢ*/: return 'G';	// LATIN LETTER SMALL CAPITAL G -- no decomposition
    case L'\x0263'/*ɣ*/: return 'g';	// LATIN SMALL LETTER GAMMA -- no decomposition
    case L'\x0264'/*ɤ*/: return 'y';	// LATIN SMALL LETTER RAMS HORN -- no decomposition
    case L'\x0265'/*ɥ*/: return 'h';	// LATIN SMALL LETTER TURNED H -- no decomposition
    case L'\x0266'/*ɦ*/: return 'h';	// LATIN SMALL LETTER H WITH HOOK -- no decomposition
    case L'\x0267'/*ɧ*/: return 'h';	// LATIN SMALL LETTER HENG WITH HOOK -- no decomposition
    case L'\x0268'/*ɨ*/: return 'i';	// LATIN SMALL LETTER I WITH STROKE -- no decomposition
    case L'\x0269'/*ɩ*/: return 'i';	// LATIN SMALL LETTER IOTA -- no decomposition
    case L'\x026A'/*ɪ*/: return 'I';	// LATIN LETTER SMALL CAPITAL I -- no decomposition
    case L'\x026B'/*ɫ*/: return 'l';	// LATIN SMALL LETTER L WITH MIDDLE TILDE -- no decomposition
    case L'\x026C'/*ɬ*/: return 'l';	// LATIN SMALL LETTER L WITH BELT -- no decomposition
    case L'\x026D'/*ɭ*/: return 'l';	// LATIN SMALL LETTER L WITH RETROFLEX HOOK -- no decomposition
    // case L'\x026E'/*ɮ*/: return 'lz';	// LATIN SMALL LETTER LEZH -- no decomposition
    case L'\x026F'/*ɯ*/: return 'm';	// LATIN SMALL LETTER TURNED M -- no decomposition
    case L'\x0270'/*ɰ*/: return 'm';	// LATIN SMALL LETTER TURNED M WITH LONG LEG -- no decomposition
    case L'\x0271'/*ɱ*/: return 'm';	// LATIN SMALL LETTER M WITH HOOK -- no decomposition
    case L'\x0272'/*ɲ*/: return 'n';	// LATIN SMALL LETTER N WITH LEFT HOOK -- no decomposition
    case L'\x0273'/*ɳ*/: return 'n';	// LATIN SMALL LETTER N WITH RETROFLEX HOOK -- no decomposition
    case L'\x0274'/*ɴ*/: return 'N';	// LATIN LETTER SMALL CAPITAL N -- no decomposition
    case L'\x0275'/*ɵ*/: return 'o';	// LATIN SMALL LETTER BARRED O -- no decomposition
    // case L'\x0276'/*ɶ*/: return 'OE';	// LATIN LETTER SMALL CAPITAL OE -- no decomposition
    case L'\x0277'/*ɷ*/: return 'o';	// LATIN SMALL LETTER CLOSED OMEGA -- no decomposition
    // case L'\x0278'/*ɸ*/: return 'ph';	// LATIN SMALL LETTER PHI -- no decomposition
    case L'\x0279'/*ɹ*/: return 'r';	// LATIN SMALL LETTER TURNED R -- no decomposition
    case L'\x027A'/*ɺ*/: return 'r';	// LATIN SMALL LETTER TURNED R WITH LONG LEG -- no decomposition
    case L'\x027B'/*ɻ*/: return 'r';	// LATIN SMALL LETTER TURNED R WITH HOOK -- no decomposition
    case L'\x027C'/*ɼ*/: return 'r';	// LATIN SMALL LETTER R WITH LONG LEG -- no decomposition
    case L'\x027D'/*ɽ*/: return 'r';	// LATIN SMALL LETTER R WITH TAIL -- no decomposition
    case L'\x027E'/*ɾ*/: return 'r';	// LATIN SMALL LETTER R WITH FISHHOOK -- no decomposition
    case L'\x027F'/*ɿ*/: return 'r';	// LATIN SMALL LETTER REVERSED R WITH FISHHOOK -- no decomposition
    case L'\x0280'/*ʀ*/: return 'R';	// LATIN LETTER SMALL CAPITAL R -- no decomposition
    case L'\x0281'/*ʁ*/: return 'r';	// LATIN LETTER SMALL CAPITAL INVERTED R -- no decomposition
    case L'\x0282'/*ʂ*/: return 's';	// LATIN SMALL LETTER S WITH HOOK -- no decomposition
    case L'\x0283'/*ʃ*/: return 's';	// LATIN SMALL LETTER ESH -- no decomposition
    case L'\x0284'/*ʄ*/: return 'j';	// LATIN SMALL LETTER DOTLESS J WITH STROKE AND HOOK -- no decomposition
    case L'\x0285'/*ʅ*/: return 's';	// LATIN SMALL LETTER SQUAT REVERSED ESH -- no decomposition
    case L'\x0286'/*ʆ*/: return 's';	// LATIN SMALL LETTER ESH WITH CURL -- no decomposition
    case L'\x0287'/*ʇ*/: return 'y';	// LATIN SMALL LETTER TURNED T -- no decomposition
    case L'\x0288'/*ʈ*/: return 't';	// LATIN SMALL LETTER T WITH RETROFLEX HOOK -- no decomposition
    case L'\x0289'/*ʉ*/: return 'u';	// LATIN SMALL LETTER U BAR -- no decomposition
    case L'\x028A'/*ʊ*/: return 'u';	// LATIN SMALL LETTER UPSILON -- no decomposition
    case L'\x028B'/*ʋ*/: return 'u';	// LATIN SMALL LETTER V WITH HOOK -- no decomposition
    case L'\x028C'/*ʌ*/: return 'v';	// LATIN SMALL LETTER TURNED V -- no decomposition
    case L'\x028D'/*ʍ*/: return 'w';	// LATIN SMALL LETTER TURNED W -- no decomposition
    case L'\x028E'/*ʎ*/: return 'y';	// LATIN SMALL LETTER TURNED Y -- no decomposition
    case L'\x028F'/*ʏ*/: return 'Y';	// LATIN LETTER SMALL CAPITAL Y -- no decomposition
    case L'\x0290'/*ʐ*/: return 'z';	// LATIN SMALL LETTER Z WITH RETROFLEX HOOK -- no decomposition
    case L'\x0291'/*ʑ*/: return 'z';	// LATIN SMALL LETTER Z WITH CURL -- no decomposition
    case L'\x0292'/*ʒ*/: return 'z';	// LATIN SMALL LETTER EZH -- no decomposition
    case L'\x0293'/*ʓ*/: return 'z';	// LATIN SMALL LETTER EZH WITH CURL -- no decomposition
    // case L'\x0294'/*ʔ*/: return ''';	// LATIN LETTER GLOTTAL STOP -- no decomposition
    // case L'\x0295'/*ʕ*/: return ''';	// LATIN LETTER PHARYNGEAL VOICED FRICATIVE -- no decomposition
    // case L'\x0296'/*ʖ*/: return ''';	// LATIN LETTER INVERTED GLOTTAL STOP -- no decomposition
    case L'\x0297'/*ʗ*/: return 'C';	// LATIN LETTER STRETCHED C -- no decomposition
    //case L'\x0298'/*ʘ*/: return 'O';	// LATIN LETTER BILABIAL CLICK -- no decomposition
    case L'\x0299'/*ʙ*/: return 'B';	// LATIN LETTER SMALL CAPITAL B -- no decomposition
    case L'\x029A'/*ʚ*/: return 'e';	// LATIN SMALL LETTER CLOSED OPEN E -- no decomposition
    case L'\x029B'/*ʛ*/: return 'G';	// LATIN LETTER SMALL CAPITAL G WITH HOOK -- no decomposition
    case L'\x029C'/*ʜ*/: return 'H';	// LATIN LETTER SMALL CAPITAL H -- no decomposition
    case L'\x029D'/*ʝ*/: return 'j';	// LATIN SMALL LETTER J WITH CROSSED-TAIL -- no decomposition
    case L'\x029E'/*ʞ*/: return 'k';	// LATIN SMALL LETTER TURNED K -- no decomposition
    case L'\x029F'/*ʟ*/: return 'L';	// LATIN LETTER SMALL CAPITAL L -- no decomposition
    case L'\x02A0'/*ʠ*/: return 'q';	// LATIN SMALL LETTER Q WITH HOOK -- no decomposition
    // case L'\x02A1'/*ʡ*/: return ''';	// LATIN LETTER GLOTTAL STOP WITH STROKE -- no decomposition
    // case L'\x02A2'/*ʢ*/: return ''';	// LATIN LETTER REVERSED GLOTTAL STOP WITH STROKE -- no decomposition
    // case L'\x02A3'/*ʣ*/: return 'dz';	// LATIN SMALL LETTER DZ DIGRAPH -- no decomposition
    // case L'\x02A4'/*ʤ*/: return 'dz';	// LATIN SMALL LETTER DEZH DIGRAPH -- no decomposition
    // case L'\x02A5'/*ʥ*/: return 'dz';	// LATIN SMALL LETTER DZ DIGRAPH WITH CURL -- no decomposition
    // case L'\x02A6'/*ʦ*/: return 'ts';	// LATIN SMALL LETTER TS DIGRAPH -- no decomposition
    // case L'\x02A7'/*ʧ*/: return 'ts';	// LATIN SMALL LETTER TESH DIGRAPH -- no decomposition
    // case L'\x02A8'/*ʨ*/: return ''; // LATIN SMALL LETTER TC DIGRAPH WITH CURL -- no decomposition
    // case L'\x02A9'/*ʩ*/: return 'fn';	// LATIN SMALL LETTER FENG DIGRAPH -- no decomposition
    // case L'\x02AA'/*ʪ*/: return 'ls';	// LATIN SMALL LETTER LS DIGRAPH -- no decomposition
    // case L'\x02AB'/*ʫ*/: return 'lz';	// LATIN SMALL LETTER LZ DIGRAPH -- no decomposition
    case L'\x02AC'/*ʬ*/: return 'w';	// LATIN LETTER BILABIAL PERCUSSIVE -- no decomposition
    case L'\x02AD'/*ʭ*/: return 't';	// LATIN LETTER BIDENTAL PERCUSSIVE -- no decomposition
    case L'\x02AE'/*ʮ*/: return 'h';	// LATIN SMALL LETTER TURNED H WITH FISHHOOK -- no decomposition
    case L'\x02AF'/*ʯ*/: return 'h';	// LATIN SMALL LETTER TURNED H WITH FISHHOOK AND TAIL -- no decomposition
    case L'\x02B0'/*ʰ*/: return 'h';	// MODIFIER LETTER SMALL H
    case L'\x02B1'/*ʱ*/: return 'h';	// MODIFIER LETTER SMALL H WITH HOOK
    case L'\x02B2'/*ʲ*/: return 'j';	// MODIFIER LETTER SMALL J
    case L'\x02B3'/*ʳ*/: return 'r';	// MODIFIER LETTER SMALL R
    case L'\x02B4'/*ʴ*/: return 'r';	// MODIFIER LETTER SMALL TURNED R
    case L'\x02B5'/*ʵ*/: return 'r';	// MODIFIER LETTER SMALL TURNED R WITH HOOK
    case L'\x02B6'/*ʶ*/: return 'R';	// MODIFIER LETTER SMALL CAPITAL INVERTED R
    case L'\x02B7'/*ʷ*/: return 'w';	// MODIFIER LETTER SMALL W
    case L'\x02B8'/*ʸ*/: return 'y';	// MODIFIER LETTER SMALL Y
    case L'\x02E1'/*ˡ*/: return 'l';	// MODIFIER LETTER SMALL L
    case L'\x02E2'/*ˢ*/: return 's';	// MODIFIER LETTER SMALL S
    case L'\x02E3'/*ˣ*/: return 'x';	// MODIFIER LETTER SMALL X
    // case L'\x02E4'/*ˤ*/: return ''';	// MODIFIER LETTER SMALL REVERSED GLOTTAL STOP
    case L'\x1D00'/*ᴀ*/: return 'A';	// LATIN LETTER SMALL CAPITAL A -- no decomposition
    // case L'\x1D01'/*ᴁ*/: return 'AE';	// LATIN LETTER SMALL CAPITAL AE -- no decomposition
    // case L'\x1D02'/*ᴂ*/: return 'ae';	// LATIN SMALL LETTER TURNED AE -- no decomposition
    case L'\x1D03'/*ᴃ*/: return 'B';	// LATIN LETTER SMALL CAPITAL BARRED B -- no decomposition
    case L'\x1D04'/*ᴄ*/: return 'C';	// LATIN LETTER SMALL CAPITAL C -- no decomposition
    case L'\x1D05'/*ᴅ*/: return 'D';	// LATIN LETTER SMALL CAPITAL D -- no decomposition
    // case L'\x1D06'/*ᴆ*/: return 'TH';	// LATIN LETTER SMALL CAPITAL ETH -- no decomposition
    case L'\x1D07'/*ᴇ*/: return 'E';	// LATIN LETTER SMALL CAPITAL E -- no decomposition
    case L'\x1D08'/*ᴈ*/: return 'e';	// LATIN SMALL LETTER TURNED OPEN E -- no decomposition
    case L'\x1D09'/*ᴉ*/: return 'i';	// LATIN SMALL LETTER TURNED I -- no decomposition
    case L'\x1D0A'/*ᴊ*/: return 'J';	// LATIN LETTER SMALL CAPITAL J -- no decomposition
    case L'\x1D0B'/*ᴋ*/: return 'K';	// LATIN LETTER SMALL CAPITAL K -- no decomposition
    case L'\x1D0C'/*ᴌ*/: return 'L';	// LATIN LETTER SMALL CAPITAL L WITH STROKE -- no decomposition
    case L'\x1D0D'/*ᴍ*/: return 'M';	// LATIN LETTER SMALL CAPITAL M -- no decomposition
    case L'\x1D0E'/*ᴎ*/: return 'N';	// LATIN LETTER SMALL CAPITAL REVERSED N -- no decomposition
    case L'\x1D0F'/*ᴏ*/: return 'O';	// LATIN LETTER SMALL CAPITAL O -- no decomposition
    case L'\x1D10'/*ᴐ*/: return 'O';	// LATIN LETTER SMALL CAPITAL OPEN O -- no decomposition
    case L'\x1D11'/*ᴑ*/: return 'o';	// LATIN SMALL LETTER SIDEWAYS O -- no decomposition
    case L'\x1D12'/*ᴒ*/: return 'o';	// LATIN SMALL LETTER SIDEWAYS OPEN O -- no decomposition
    case L'\x1D13'/*ᴓ*/: return 'o';	// LATIN SMALL LETTER SIDEWAYS O WITH STROKE -- no decomposition
    // case L'\x1D14'/*ᴔ*/: return 'oe';	// LATIN SMALL LETTER TURNED OE -- no decomposition
    // case L'\x1D15'/*ᴕ*/: return 'ou';	// LATIN LETTER SMALL CAPITAL OU -- no decomposition
    case L'\x1D16'/*ᴖ*/: return 'o';	// LATIN SMALL LETTER TOP HALF O -- no decomposition
    case L'\x1D17'/*ᴗ*/: return 'o';	// LATIN SMALL LETTER BOTTOM HALF O -- no decomposition
    case L'\x1D18'/*ᴘ*/: return 'P';	// LATIN LETTER SMALL CAPITAL P -- no decomposition
    case L'\x1D19'/*ᴙ*/: return 'R';	// LATIN LETTER SMALL CAPITAL REVERSED R -- no decomposition
    case L'\x1D1A'/*ᴚ*/: return 'R';	// LATIN LETTER SMALL CAPITAL TURNED R -- no decomposition
    case L'\x1D1B'/*ᴛ*/: return 'T';	// LATIN LETTER SMALL CAPITAL T -- no decomposition
    case L'\x1D1C'/*ᴜ*/: return 'U';	// LATIN LETTER SMALL CAPITAL U -- no decomposition
    case L'\x1D1D'/*ᴝ*/: return 'u';	// LATIN SMALL LETTER SIDEWAYS U -- no decomposition
    case L'\x1D1E'/*ᴞ*/: return 'u';	// LATIN SMALL LETTER SIDEWAYS DIAERESIZED U -- no decomposition
    case L'\x1D1F'/*ᴟ*/: return 'm';	// LATIN SMALL LETTER SIDEWAYS TURNED M -- no decomposition
    case L'\x1D20'/*ᴠ*/: return 'V';	// LATIN LETTER SMALL CAPITAL V -- no decomposition
    case L'\x1D21'/*ᴡ*/: return 'W';	// LATIN LETTER SMALL CAPITAL W -- no decomposition
    case L'\x1D22'/*ᴢ*/: return 'Z';	// LATIN LETTER SMALL CAPITAL Z -- no decomposition
    // case L'\x1D23'/*ᴣ*/: return 'EZH';	// LATIN LETTER SMALL CAPITAL EZH -- no decomposition
    // case L'\x1D24'/*ᴤ*/: return ''';	// LATIN LETTER VOICED LARYNGEAL SPIRANT -- no decomposition
    case L'\x1D25'/*ᴥ*/: return 'L';	// LATIN LETTER AIN -- no decomposition
    case L'\x1D2C'/*ᴬ*/: return 'A';	// MODIFIER LETTER CAPITAL A
    // case L'\x1D2D'/*ᴭ*/: return 'AE';	// MODIFIER LETTER CAPITAL AE
    case L'\x1D2E'/*ᴮ*/: return 'B';	// MODIFIER LETTER CAPITAL B
    case L'\x1D2F'/*ᴯ*/: return 'B';	// MODIFIER LETTER CAPITAL BARRED B -- no decomposition
    case L'\x1D30'/*ᴰ*/: return 'D';	// MODIFIER LETTER CAPITAL D
    case L'\x1D31'/*ᴱ*/: return 'E';	// MODIFIER LETTER CAPITAL E
    case L'\x1D32'/*ᴲ*/: return 'E';	// MODIFIER LETTER CAPITAL REVERSED E
    case L'\x1D33'/*ᴳ*/: return 'G';	// MODIFIER LETTER CAPITAL G
    case L'\x1D34'/*ᴴ*/: return 'H';	// MODIFIER LETTER CAPITAL H
    case L'\x1D35'/*ᴵ*/: return 'I';	// MODIFIER LETTER CAPITAL I
    case L'\x1D36'/*ᴶ*/: return 'J';	// MODIFIER LETTER CAPITAL J
    case L'\x1D37'/*ᴷ*/: return 'K';	// MODIFIER LETTER CAPITAL K
    case L'\x1D38'/*ᴸ*/: return 'L';	// MODIFIER LETTER CAPITAL L
    case L'\x1D39'/*ᴹ*/: return 'M';	// MODIFIER LETTER CAPITAL M
    case L'\x1D3A'/*ᴺ*/: return 'N';	// MODIFIER LETTER CAPITAL N
    case L'\x1D3B'/*ᴻ*/: return 'N';	// MODIFIER LETTER CAPITAL REVERSED N -- no decomposition
    case L'\x1D3C'/*ᴼ*/: return 'O';	// MODIFIER LETTER CAPITAL O
    // case L'\x1D3D'/*ᴽ*/: return 'OU';	// MODIFIER LETTER CAPITAL OU
    case L'\x1D3E'/*ᴾ*/: return 'P';	// MODIFIER LETTER CAPITAL P
    case L'\x1D3F'/*ᴿ*/: return 'R';	// MODIFIER LETTER CAPITAL R
    case L'\x1D40'/*ᵀ*/: return 'T';	// MODIFIER LETTER CAPITAL T
    case L'\x1D41'/*ᵁ*/: return 'U';	// MODIFIER LETTER CAPITAL U
    case L'\x1D42'/*ᵂ*/: return 'W';	// MODIFIER LETTER CAPITAL W
    case L'\x1D43'/*ᵃ*/: return 'a';	// MODIFIER LETTER SMALL A
    case L'\x1D44'/*ᵄ*/: return 'a';	// MODIFIER LETTER SMALL TURNED A
    // case L'\x1D46'/*ᵆ*/: return 'ae';	// MODIFIER LETTER SMALL TURNED AE
    case L'\x1D47'/*ᵇ*/: return 'b';    // MODIFIER LETTER SMALL B
    case L'\x1D48'/*ᵈ*/: return 'd';    // MODIFIER LETTER SMALL D
    case L'\x1D49'/*ᵉ*/: return 'e';    // MODIFIER LETTER SMALL E
    case L'\x1D4A'/*ᵊ*/: return 'e';    // MODIFIER LETTER SMALL SCHWA
    case L'\x1D4B'/*ᵋ*/: return 'e';    // MODIFIER LETTER SMALL OPEN E
    case L'\x1D4C'/*ᵌ*/: return 'e';    // MODIFIER LETTER SMALL TURNED OPEN E
    case L'\x1D4D'/*ᵍ*/: return 'g';    // MODIFIER LETTER SMALL G
    case L'\x1D4E'/*ᵎ*/: return 'i';    // MODIFIER LETTER SMALL TURNED I -- no decomposition
    case L'\x1D4F'/*ᵏ*/: return 'k';    // MODIFIER LETTER SMALL K
    case L'\x1D50'/*ᵐ*/: return 'm';	// MODIFIER LETTER SMALL M
    case L'\x1D51'/*ᵑ*/: return 'g';	// MODIFIER LETTER SMALL ENG
    case L'\x1D52'/*ᵒ*/: return 'o';	// MODIFIER LETTER SMALL O
    case L'\x1D53'/*ᵓ*/: return 'o';	// MODIFIER LETTER SMALL OPEN O
    case L'\x1D54'/*ᵔ*/: return 'o';	// MODIFIER LETTER SMALL TOP HALF O
    case L'\x1D55'/*ᵕ*/: return 'o';	// MODIFIER LETTER SMALL BOTTOM HALF O
    case L'\x1D56'/*ᵖ*/: return 'p';	// MODIFIER LETTER SMALL P
    case L'\x1D57'/*ᵗ*/: return 't';	// MODIFIER LETTER SMALL T
    case L'\x1D58'/*ᵘ*/: return 'u';	// MODIFIER LETTER SMALL U
    case L'\x1D59'/*ᵙ*/: return 'u';	// MODIFIER LETTER SMALL SIDEWAYS U
    case L'\x1D5A'/*ᵚ*/: return 'm';	// MODIFIER LETTER SMALL TURNED M
    case L'\x1D5B'/*ᵛ*/: return 'v';	// MODIFIER LETTER SMALL V
    case L'\x1D62'/*ᵢ*/: return 'i';	// LATIN SUBSCRIPT SMALL LETTER I
    case L'\x1D63'/*ᵣ*/: return 'r';	// LATIN SUBSCRIPT SMALL LETTER R
    case L'\x1D64'/*ᵤ*/: return 'u';	// LATIN SUBSCRIPT SMALL LETTER U
    case L'\x1D65'/*ᵥ*/: return 'v';	// LATIN SUBSCRIPT SMALL LETTER V
    // case L'\x1D6B'/*ᵫ*/: return 'ue';	// LATIN SMALL LETTER UE -- no decomposition
    case L'\x1E00'/*Ḁ*/: return 'A';	// LATIN CAPITAL LETTER A WITH RING BELOW
    case L'\x1E01'/*ḁ*/: return 'a';	// LATIN SMALL LETTER A WITH RING BELOW
    case L'\x1E02'/*Ḃ*/: return 'B';	// LATIN CAPITAL LETTER B WITH DOT ABOVE
    case L'\x1E03'/*ḃ*/: return 'b';	// LATIN SMALL LETTER B WITH DOT ABOVE
    case L'\x1E04'/*Ḅ*/: return 'B';	// LATIN CAPITAL LETTER B WITH DOT BELOW
    case L'\x1E05'/*ḅ*/: return 'b';	// LATIN SMALL LETTER B WITH DOT BELOW
    case L'\x1E06'/*Ḇ*/: return 'B';	// LATIN CAPITAL LETTER B WITH LINE BELOW
    case L'\x1E07'/*ḇ*/: return 'b';	// LATIN SMALL LETTER B WITH LINE BELOW
    case L'\x1E08'/*Ḉ*/: return 'C';	// LATIN CAPITAL LETTER C WITH CEDILLA AND ACUTE
    case L'\x1E09'/*ḉ*/: return 'c';	// LATIN SMALL LETTER C WITH CEDILLA AND ACUTE
    case L'\x1E0A'/*Ḋ*/: return 'D';	// LATIN CAPITAL LETTER D WITH DOT ABOVE
    case L'\x1E0B'/*ḋ*/: return 'd';	// LATIN SMALL LETTER D WITH DOT ABOVE
    case L'\x1E0C'/*Ḍ*/: return 'D';	// LATIN CAPITAL LETTER D WITH DOT BELOW
    case L'\x1E0D'/*ḍ*/: return 'd';	// LATIN SMALL LETTER D WITH DOT BELOW
    case L'\x1E0E'/*Ḏ*/: return 'D';	// LATIN CAPITAL LETTER D WITH LINE BELOW
    case L'\x1E0F'/*ḏ*/: return 'd';	// LATIN SMALL LETTER D WITH LINE BELOW
    case L'\x1E10'/*Ḑ*/: return 'D';	// LATIN CAPITAL LETTER D WITH CEDILLA
    case L'\x1E11'/*ḑ*/: return 'd';	// LATIN SMALL LETTER D WITH CEDILLA
    case L'\x1E12'/*Ḓ*/: return 'D';	// LATIN CAPITAL LETTER D WITH CIRCUMFLEX BELOW
    case L'\x1E13'/*ḓ*/: return 'd';	// LATIN SMALL LETTER D WITH CIRCUMFLEX BELOW
    case L'\x1E14'/*Ḕ*/: return 'E';	// LATIN CAPITAL LETTER E WITH MACRON AND GRAVE
    case L'\x1E15'/*ḕ*/: return 'e';	// LATIN SMALL LETTER E WITH MACRON AND GRAVE
    case L'\x1E16'/*Ḗ*/: return 'E';	// LATIN CAPITAL LETTER E WITH MACRON AND ACUTE
    case L'\x1E17'/*ḗ*/: return 'e';	// LATIN SMALL LETTER E WITH MACRON AND ACUTE
    case L'\x1E18'/*Ḙ*/: return 'E';	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX BELOW
    case L'\x1E19'/*ḙ*/: return 'e';	// LATIN SMALL LETTER E WITH CIRCUMFLEX BELOW
    case L'\x1E1A'/*Ḛ*/: return 'E';	// LATIN CAPITAL LETTER E WITH TILDE BELOW
    case L'\x1E1B'/*ḛ*/: return 'e';	// LATIN SMALL LETTER E WITH TILDE BELOW
    case L'\x1E1C'/*Ḝ*/: return 'E';	// LATIN CAPITAL LETTER E WITH CEDILLA AND BREVE
    case L'\x1E1D'/*ḝ*/: return 'e';	// LATIN SMALL LETTER E WITH CEDILLA AND BREVE
    case L'\x1E1E'/*Ḟ*/: return 'F';	// LATIN CAPITAL LETTER F WITH DOT ABOVE
    case L'\x1E1F'/*ḟ*/: return 'f';	// LATIN SMALL LETTER F WITH DOT ABOVE
    case L'\x1E20'/*Ḡ*/: return 'G';	// LATIN CAPITAL LETTER G WITH MACRON
    case L'\x1E21'/*ḡ*/: return 'g';	// LATIN SMALL LETTER G WITH MACRON
    case L'\x1E22'/*Ḣ*/: return 'H';	// LATIN CAPITAL LETTER H WITH DOT ABOVE
    case L'\x1E23'/*ḣ*/: return 'h';	// LATIN SMALL LETTER H WITH DOT ABOVE
    case L'\x1E24'/*Ḥ*/: return 'H';	// LATIN CAPITAL LETTER H WITH DOT BELOW
    case L'\x1E25'/*ḥ*/: return 'h';	// LATIN SMALL LETTER H WITH DOT BELOW
    case L'\x1E26'/*Ḧ*/: return 'H';	// LATIN CAPITAL LETTER H WITH DIAERESIS
    case L'\x1E27'/*ḧ*/: return 'h';	// LATIN SMALL LETTER H WITH DIAERESIS
    case L'\x1E28'/*Ḩ*/: return 'H';	// LATIN CAPITAL LETTER H WITH CEDILLA
    case L'\x1E29'/*ḩ*/: return 'h';	// LATIN SMALL LETTER H WITH CEDILLA
    case L'\x1E2A'/*Ḫ*/: return 'H';	// LATIN CAPITAL LETTER H WITH BREVE BELOW
    case L'\x1E2B'/*ḫ*/: return 'h';	// LATIN SMALL LETTER H WITH BREVE BELOW
    case L'\x1E2C'/*Ḭ*/: return 'I';	// LATIN CAPITAL LETTER I WITH TILDE BELOW
    case L'\x1E2D'/*ḭ*/: return 'i';	// LATIN SMALL LETTER I WITH TILDE BELOW
    case L'\x1E2E'/*Ḯ*/: return 'I';	// LATIN CAPITAL LETTER I WITH DIAERESIS AND ACUTE
    case L'\x1E2F'/*ḯ*/: return 'i';	// LATIN SMALL LETTER I WITH DIAERESIS AND ACUTE
    case L'\x1E30'/*Ḱ*/: return 'K';	// LATIN CAPITAL LETTER K WITH ACUTE
    case L'\x1E31'/*ḱ*/: return 'k';	// LATIN SMALL LETTER K WITH ACUTE
    case L'\x1E32'/*Ḳ*/: return 'K';	// LATIN CAPITAL LETTER K WITH DOT BELOW
    case L'\x1E33'/*ḳ*/: return 'k';	// LATIN SMALL LETTER K WITH DOT BELOW
    case L'\x1E34'/*Ḵ*/: return 'K';	// LATIN CAPITAL LETTER K WITH LINE BELOW
    case L'\x1E35'/*ḵ*/: return 'k';	// LATIN SMALL LETTER K WITH LINE BELOW
    case L'\x1E36'/*Ḷ*/: return 'L';	// LATIN CAPITAL LETTER L WITH DOT BELOW
    case L'\x1E37'/*ḷ*/: return 'l';	// LATIN SMALL LETTER L WITH DOT BELOW
    case L'\x1E38'/*Ḹ*/: return 'L';	// LATIN CAPITAL LETTER L WITH DOT BELOW AND MACRON
    case L'\x1E39'/*ḹ*/: return 'l';	// LATIN SMALL LETTER L WITH DOT BELOW AND MACRON
    case L'\x1E3A'/*Ḻ*/: return 'L';	// LATIN CAPITAL LETTER L WITH LINE BELOW
    case L'\x1E3B'/*ḻ*/: return 'l';	// LATIN SMALL LETTER L WITH LINE BELOW
    case L'\x1E3C'/*Ḽ*/: return 'L';	// LATIN CAPITAL LETTER L WITH CIRCUMFLEX BELOW
    case L'\x1E3D'/*ḽ*/: return 'l';	// LATIN SMALL LETTER L WITH CIRCUMFLEX BELOW
    case L'\x1E3E'/*Ḿ*/: return 'M';	// LATIN CAPITAL LETTER M WITH ACUTE
    case L'\x1E3F'/*ḿ*/: return 'm';	// LATIN SMALL LETTER M WITH ACUTE
    case L'\x1E40'/*Ṁ*/: return 'M';	// LATIN CAPITAL LETTER M WITH DOT ABOVE
    case L'\x1E41'/*ṁ*/: return 'm';	// LATIN SMALL LETTER M WITH DOT ABOVE
    case L'\x1E42'/*Ṃ*/: return 'M';	// LATIN CAPITAL LETTER M WITH DOT BELOW
    case L'\x1E43'/*ṃ*/: return 'm';	// LATIN SMALL LETTER M WITH DOT BELOW
    case L'\x1E44'/*Ṅ*/: return 'N';	// LATIN CAPITAL LETTER N WITH DOT ABOVE
    case L'\x1E45'/*ṅ*/: return 'n';	// LATIN SMALL LETTER N WITH DOT ABOVE
    case L'\x1E46'/*Ṇ*/: return 'N';	// LATIN CAPITAL LETTER N WITH DOT BELOW
    case L'\x1E47'/*ṇ*/: return 'n';	// LATIN SMALL LETTER N WITH DOT BELOW
    case L'\x1E48'/*Ṉ*/: return 'N';	// LATIN CAPITAL LETTER N WITH LINE BELOW
    case L'\x1E49'/*ṉ*/: return 'n';	// LATIN SMALL LETTER N WITH LINE BELOW
    case L'\x1E4A'/*Ṋ*/: return 'N';	// LATIN CAPITAL LETTER N WITH CIRCUMFLEX BELOW
    case L'\x1E4B'/*ṋ*/: return 'n';	// LATIN SMALL LETTER N WITH CIRCUMFLEX BELOW
    case L'\x1E4C'/*Ṍ*/: return 'O';	// LATIN CAPITAL LETTER O WITH TILDE AND ACUTE
    case L'\x1E4D'/*ṍ*/: return 'o';	// LATIN SMALL LETTER O WITH TILDE AND ACUTE
    case L'\x1E4E'/*Ṏ*/: return 'O';	// LATIN CAPITAL LETTER O WITH TILDE AND DIAERESIS
    case L'\x1E4F'/*ṏ*/: return 'o';	// LATIN SMALL LETTER O WITH TILDE AND DIAERESIS
    case L'\x1E50'/*Ṑ*/: return 'O';	// LATIN CAPITAL LETTER O WITH MACRON AND GRAVE
    case L'\x1E51'/*ṑ*/: return 'o';	// LATIN SMALL LETTER O WITH MACRON AND GRAVE
    case L'\x1E52'/*Ṓ*/: return 'O';	// LATIN CAPITAL LETTER O WITH MACRON AND ACUTE
    case L'\x1E53'/*ṓ*/: return 'o';	// LATIN SMALL LETTER O WITH MACRON AND ACUTE
    case L'\x1E54'/*Ṕ*/: return 'P';	// LATIN CAPITAL LETTER P WITH ACUTE
    case L'\x1E55'/*ṕ*/: return 'p';	// LATIN SMALL LETTER P WITH ACUTE
    case L'\x1E56'/*Ṗ*/: return 'P';	// LATIN CAPITAL LETTER P WITH DOT ABOVE
    case L'\x1E57'/*ṗ*/: return 'p';	// LATIN SMALL LETTER P WITH DOT ABOVE
    case L'\x1E58'/*Ṙ*/: return 'R';	// LATIN CAPITAL LETTER R WITH DOT ABOVE
    case L'\x1E59'/*ṙ*/: return 'r';	// LATIN SMALL LETTER R WITH DOT ABOVE
    case L'\x1E5A'/*Ṛ*/: return 'R';	// LATIN CAPITAL LETTER R WITH DOT BELOW
    case L'\x1E5B'/*ṛ*/: return 'r';	// LATIN SMALL LETTER R WITH DOT BELOW
    case L'\x1E5C'/*Ṝ*/: return 'R';	// LATIN CAPITAL LETTER R WITH DOT BELOW AND MACRON
    case L'\x1E5D'/*ṝ*/: return 'r';	// LATIN SMALL LETTER R WITH DOT BELOW AND MACRON
    case L'\x1E5E'/*Ṟ*/: return 'R';	// LATIN CAPITAL LETTER R WITH LINE BELOW
    case L'\x1E5F'/*ṟ*/: return 'r';	// LATIN SMALL LETTER R WITH LINE BELOW
    case L'\x1E60'/*Ṡ*/: return 'S';	// LATIN CAPITAL LETTER S WITH DOT ABOVE
    case L'\x1E61'/*ṡ*/: return 's';	// LATIN SMALL LETTER S WITH DOT ABOVE
    case L'\x1E62'/*Ṣ*/: return 'S';	// LATIN CAPITAL LETTER S WITH DOT BELOW
    case L'\x1E63'/*ṣ*/: return 's';	// LATIN SMALL LETTER S WITH DOT BELOW
    case L'\x1E64'/*Ṥ*/: return 'S';	// LATIN CAPITAL LETTER S WITH ACUTE AND DOT ABOVE
    case L'\x1E65'/*ṥ*/: return 's';	// LATIN SMALL LETTER S WITH ACUTE AND DOT ABOVE
    case L'\x1E66'/*Ṧ*/: return 'S';	// LATIN CAPITAL LETTER S WITH CARON AND DOT ABOVE
    case L'\x1E67'/*ṧ*/: return 's';	// LATIN SMALL LETTER S WITH CARON AND DOT ABOVE
    case L'\x1E68'/*Ṩ*/: return 'S';	// LATIN CAPITAL LETTER S WITH DOT BELOW AND DOT ABOVE
    case L'\x1E69'/*ṩ*/: return 's';	// LATIN SMALL LETTER S WITH DOT BELOW AND DOT ABOVE
    case L'\x1E6A'/*Ṫ*/: return 'T';	// LATIN CAPITAL LETTER T WITH DOT ABOVE
    case L'\x1E6B'/*ṫ*/: return 't';	// LATIN SMALL LETTER T WITH DOT ABOVE
    case L'\x1E6C'/*Ṭ*/: return 'T';	// LATIN CAPITAL LETTER T WITH DOT BELOW
    case L'\x1E6D'/*ṭ*/: return 't';	// LATIN SMALL LETTER T WITH DOT BELOW
    case L'\x1E6E'/*Ṯ*/: return 'T';	// LATIN CAPITAL LETTER T WITH LINE BELOW
    case L'\x1E6F'/*ṯ*/: return 't';	// LATIN SMALL LETTER T WITH LINE BELOW
    case L'\x1E70'/*Ṱ*/: return 'T';	// LATIN CAPITAL LETTER T WITH CIRCUMFLEX BELOW
    case L'\x1E71'/*ṱ*/: return 't';	// LATIN SMALL LETTER T WITH CIRCUMFLEX BELOW
    case L'\x1E72'/*Ṳ*/: return 'U';	// LATIN CAPITAL LETTER U WITH DIAERESIS BELOW
    case L'\x1E73'/*ṳ*/: return 'u';	// LATIN SMALL LETTER U WITH DIAERESIS BELOW
    case L'\x1E74'/*Ṵ*/: return 'U';	// LATIN CAPITAL LETTER U WITH TILDE BELOW
    case L'\x1E75'/*ṵ*/: return 'u';	// LATIN SMALL LETTER U WITH TILDE BELOW
    case L'\x1E76'/*Ṷ*/: return 'U';	// LATIN CAPITAL LETTER U WITH CIRCUMFLEX BELOW
    case L'\x1E77'/*ṷ*/: return 'u';	// LATIN SMALL LETTER U WITH CIRCUMFLEX BELOW
    case L'\x1E78'/*Ṹ*/: return 'U';	// LATIN CAPITAL LETTER U WITH TILDE AND ACUTE
    case L'\x1E79'/*ṹ*/: return 'u';	// LATIN SMALL LETTER U WITH TILDE AND ACUTE
    case L'\x1E7A'/*Ṻ*/: return 'U';	// LATIN CAPITAL LETTER U WITH MACRON AND DIAERESIS
    case L'\x1E7B'/*ṻ*/: return 'u';	// LATIN SMALL LETTER U WITH MACRON AND DIAERESIS
    case L'\x1E7C'/*Ṽ*/: return 'V';	// LATIN CAPITAL LETTER V WITH TILDE
    case L'\x1E7D'/*ṽ*/: return 'v';	// LATIN SMALL LETTER V WITH TILDE
    case L'\x1E7E'/*Ṿ*/: return 'V';	// LATIN CAPITAL LETTER V WITH DOT BELOW
    case L'\x1E7F'/*ṿ*/: return 'v';	// LATIN SMALL LETTER V WITH DOT BELOW
    case L'\x1E80'/*Ẁ*/: return 'W';	// LATIN CAPITAL LETTER W WITH GRAVE
    case L'\x1E81'/*ẁ*/: return 'w';	// LATIN SMALL LETTER W WITH GRAVE
    case L'\x1E82'/*Ẃ*/: return 'W';	// LATIN CAPITAL LETTER W WITH ACUTE
    case L'\x1E83'/*ẃ*/: return 'w';	// LATIN SMALL LETTER W WITH ACUTE
    case L'\x1E84'/*Ẅ*/: return 'W';	// LATIN CAPITAL LETTER W WITH DIAERESIS
    case L'\x1E85'/*ẅ*/: return 'w';	// LATIN SMALL LETTER W WITH DIAERESIS
    case L'\x1E86'/*Ẇ*/: return 'W';	// LATIN CAPITAL LETTER W WITH DOT ABOVE
    case L'\x1E87'/*ẇ*/: return 'w';	// LATIN SMALL LETTER W WITH DOT ABOVE
    case L'\x1E88'/*Ẉ*/: return 'W';	// LATIN CAPITAL LETTER W WITH DOT BELOW
    case L'\x1E89'/*ẉ*/: return 'w';	// LATIN SMALL LETTER W WITH DOT BELOW
    case L'\x1E8A'/*Ẋ*/: return 'X';	// LATIN CAPITAL LETTER X WITH DOT ABOVE
    case L'\x1E8B'/*ẋ*/: return 'x';	// LATIN SMALL LETTER X WITH DOT ABOVE
    case L'\x1E8C'/*Ẍ*/: return 'X';	// LATIN CAPITAL LETTER X WITH DIAERESIS
    case L'\x1E8D'/*ẍ*/: return 'x';	// LATIN SMALL LETTER X WITH DIAERESIS
    case L'\x1E8E'/*Ẏ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH DOT ABOVE
    case L'\x1E8F'/*ẏ*/: return 'y';	// LATIN SMALL LETTER Y WITH DOT ABOVE
    case L'\x1E90'/*Ẑ*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH CIRCUMFLEX
    case L'\x1E91'/*ẑ*/: return 'z';	// LATIN SMALL LETTER Z WITH CIRCUMFLEX
    case L'\x1E92'/*Ẓ*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH DOT BELOW
    case L'\x1E93'/*ẓ*/: return 'z';	// LATIN SMALL LETTER Z WITH DOT BELOW
    case L'\x1E94'/*Ẕ*/: return 'Z';	// LATIN CAPITAL LETTER Z WITH LINE BELOW
    case L'\x1E95'/*ẕ*/: return 'z';	// LATIN SMALL LETTER Z WITH LINE BELOW
    case L'\x1E96'/*ẖ*/: return 'h';	// LATIN SMALL LETTER H WITH LINE BELOW
    case L'\x1E97'/*ẗ*/: return 't';	// LATIN SMALL LETTER T WITH DIAERESIS
    case L'\x1E98'/*ẘ*/: return 'w';	// LATIN SMALL LETTER W WITH RING ABOVE
    case L'\x1E99'/*ẙ*/: return 'y';	// LATIN SMALL LETTER Y WITH RING ABOVE
    case L'\x1E9A'/*ẚ*/: return 'a';	// LATIN SMALL LETTER A WITH RIGHT HALF RING
    case L'\x1E9B'/*ẛ*/: return 's';	// LATIN SMALL LETTER LONG S WITH DOT ABOVE
    case L'\x1EA0'/*Ạ*/: return 'A';	// LATIN CAPITAL LETTER A WITH DOT BELOW
    case L'\x1EA1'/*ạ*/: return 'a';	// LATIN SMALL LETTER A WITH DOT BELOW
    case L'\x1EA2'/*Ả*/: return 'A';	// LATIN CAPITAL LETTER A WITH HOOK ABOVE
    case L'\x1EA3'/*ả*/: return 'a';	// LATIN SMALL LETTER A WITH HOOK ABOVE
    case L'\x1EA4'/*Ấ*/: return 'A';	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND ACUTE
    case L'\x1EA5'/*ấ*/: return 'a';	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND ACUTE
    case L'\x1EA6'/*Ầ*/: return 'A';	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND GRAVE
    case L'\x1EA7'/*ầ*/: return 'a';	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND GRAVE
    case L'\x1EA8'/*Ẩ*/: return 'A';	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
    case L'\x1EA9'/*ẩ*/: return 'a';	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND HOOK ABOVE
    case L'\x1EAA'/*Ẫ*/: return 'A';	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND TILDE
    case L'\x1EAB'/*ẫ*/: return 'a';	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND TILDE
    case L'\x1EAC'/*Ậ*/: return 'A';	// LATIN CAPITAL LETTER A WITH CIRCUMFLEX AND DOT BELOW
    case L'\x1EAD'/*ậ*/: return 'a';	// LATIN SMALL LETTER A WITH CIRCUMFLEX AND DOT BELOW
    case L'\x1EAE'/*Ắ*/: return 'A';	// LATIN CAPITAL LETTER A WITH BREVE AND ACUTE
    case L'\x1EAF'/*ắ*/: return 'a';	// LATIN SMALL LETTER A WITH BREVE AND ACUTE
    case L'\x1EB0'/*Ằ*/: return 'A';	// LATIN CAPITAL LETTER A WITH BREVE AND GRAVE
    case L'\x1EB1'/*ằ*/: return 'a';	// LATIN SMALL LETTER A WITH BREVE AND GRAVE
    case L'\x1EB2'/*Ẳ*/: return 'A';	// LATIN CAPITAL LETTER A WITH BREVE AND HOOK ABOVE
    case L'\x1EB3'/*ẳ*/: return 'a';	// LATIN SMALL LETTER A WITH BREVE AND HOOK ABOVE
    case L'\x1EB4'/*Ẵ*/: return 'A';	// LATIN CAPITAL LETTER A WITH BREVE AND TILDE
    case L'\x1EB5'/*ẵ*/: return 'a';	// LATIN SMALL LETTER A WITH BREVE AND TILDE
    case L'\x1EB6'/*Ặ*/: return 'A';	// LATIN CAPITAL LETTER A WITH BREVE AND DOT BELOW
    case L'\x1EB7'/*ặ*/: return 'a';	// LATIN SMALL LETTER A WITH BREVE AND DOT BELOW
    case L'\x1EB8'/*Ẹ*/: return 'E';	// LATIN CAPITAL LETTER E WITH DOT BELOW
    case L'\x1EB9'/*ẹ*/: return 'e';	// LATIN SMALL LETTER E WITH DOT BELOW
    case L'\x1EBA'/*Ẻ*/: return 'E';	// LATIN CAPITAL LETTER E WITH HOOK ABOVE
    case L'\x1EBB'/*ẻ*/: return 'e';	// LATIN SMALL LETTER E WITH HOOK ABOVE
    case L'\x1EBC'/*Ẽ*/: return 'E';	// LATIN CAPITAL LETTER E WITH TILDE
    case L'\x1EBD'/*ẽ*/: return 'e';	// LATIN SMALL LETTER E WITH TILDE
    case L'\x1EBE'/*Ế*/: return 'E';	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND ACUTE
    case L'\x1EBF'/*ế*/: return 'e';	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND ACUTE
    case L'\x1EC0'/*Ề*/: return 'E';	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND GRAVE
    case L'\x1EC1'/*ề*/: return 'e';	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND GRAVE
    case L'\x1EC2'/*Ể*/: return 'E';	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
    case L'\x1EC3'/*ể*/: return 'e';	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND HOOK ABOVE
    case L'\x1EC4'/*Ễ*/: return 'E';	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND TILDE
    case L'\x1EC5'/*ễ*/: return 'e';	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND TILDE
    case L'\x1EC6'/*Ệ*/: return 'E';	// LATIN CAPITAL LETTER E WITH CIRCUMFLEX AND DOT BELOW
    case L'\x1EC7'/*ệ*/: return 'e';	// LATIN SMALL LETTER E WITH CIRCUMFLEX AND DOT BELOW
    case L'\x1EC8'/*Ỉ*/: return 'I';	// LATIN CAPITAL LETTER I WITH HOOK ABOVE
    case L'\x1EC9'/*ỉ*/: return 'i';	// LATIN SMALL LETTER I WITH HOOK ABOVE
    case L'\x1ECA'/*Ị*/: return 'I';	// LATIN CAPITAL LETTER I WITH DOT BELOW
    case L'\x1ECB'/*ị*/: return 'i';	// LATIN SMALL LETTER I WITH DOT BELOW
    case L'\x1ECC'/*Ọ*/: return 'O';	// LATIN CAPITAL LETTER O WITH DOT BELOW
    case L'\x1ECD'/*ọ*/: return 'o';	// LATIN SMALL LETTER O WITH DOT BELOW
    case L'\x1ECE'/*Ỏ*/: return 'O';	// LATIN CAPITAL LETTER O WITH HOOK ABOVE
    case L'\x1ECF'/*ỏ*/: return 'o';	// LATIN SMALL LETTER O WITH HOOK ABOVE
    case L'\x1ED0'/*Ố*/: return 'O';	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND ACUTE
    case L'\x1ED1'/*ố*/: return 'o';	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND ACUTE
    case L'\x1ED2'/*Ồ*/: return 'O';	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND GRAVE
    case L'\x1ED3'/*ồ*/: return 'o';	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND GRAVE
    case L'\x1ED4'/*Ổ*/: return 'O';	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
    case L'\x1ED5'/*ổ*/: return 'o';	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND HOOK ABOVE
    case L'\x1ED6'/*Ỗ*/: return 'O';	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND TILDE
    case L'\x1ED7'/*ỗ*/: return 'o';	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND TILDE
    case L'\x1ED8'/*Ộ*/: return 'O';	// LATIN CAPITAL LETTER O WITH CIRCUMFLEX AND DOT BELOW
    case L'\x1ED9'/*ộ*/: return 'o';	// LATIN SMALL LETTER O WITH CIRCUMFLEX AND DOT BELOW
    case L'\x1EDA'/*Ớ*/: return 'O';	// LATIN CAPITAL LETTER O WITH HORN AND ACUTE
    case L'\x1EDB'/*ớ*/: return 'o';	// LATIN SMALL LETTER O WITH HORN AND ACUTE
    case L'\x1EDC'/*Ờ*/: return 'O';	// LATIN CAPITAL LETTER O WITH HORN AND GRAVE
    case L'\x1EDD'/*ờ*/: return 'o';	// LATIN SMALL LETTER O WITH HORN AND GRAVE
    case L'\x1EDE'/*Ở*/: return 'O';	// LATIN CAPITAL LETTER O WITH HORN AND HOOK ABOVE
    case L'\x1EDF'/*ở*/: return 'o';	// LATIN SMALL LETTER O WITH HORN AND HOOK ABOVE
    case L'\x1EE0'/*Ỡ*/: return 'O';	// LATIN CAPITAL LETTER O WITH HORN AND TILDE
    case L'\x1EE1'/*ỡ*/: return 'o';	// LATIN SMALL LETTER O WITH HORN AND TILDE
    case L'\x1EE2'/*Ợ*/: return 'O';	// LATIN CAPITAL LETTER O WITH HORN AND DOT BELOW
    case L'\x1EE3'/*ợ*/: return 'o';	// LATIN SMALL LETTER O WITH HORN AND DOT BELOW
    case L'\x1EE4'/*Ụ*/: return 'U';	// LATIN CAPITAL LETTER U WITH DOT BELOW
    case L'\x1EE5'/*ụ*/: return 'u';	// LATIN SMALL LETTER U WITH DOT BELOW
    case L'\x1EE6'/*Ủ*/: return 'U';	// LATIN CAPITAL LETTER U WITH HOOK ABOVE
    case L'\x1EE7'/*ủ*/: return 'u';	// LATIN SMALL LETTER U WITH HOOK ABOVE
    case L'\x1EE8'/*Ứ*/: return 'U';	// LATIN CAPITAL LETTER U WITH HORN AND ACUTE
    case L'\x1EE9'/*ứ*/: return 'u';	// LATIN SMALL LETTER U WITH HORN AND ACUTE
    case L'\x1EEA'/*Ừ*/: return 'U';	// LATIN CAPITAL LETTER U WITH HORN AND GRAVE
    case L'\x1EEB'/*ừ*/: return 'u';	// LATIN SMALL LETTER U WITH HORN AND GRAVE
    case L'\x1EEC'/*Ử*/: return 'U';	// LATIN CAPITAL LETTER U WITH HORN AND HOOK ABOVE
    case L'\x1EED'/*ử*/: return 'u';	// LATIN SMALL LETTER U WITH HORN AND HOOK ABOVE
    case L'\x1EEE'/*Ữ*/: return 'U';	// LATIN CAPITAL LETTER U WITH HORN AND TILDE
    case L'\x1EEF'/*ữ*/: return 'u';	// LATIN SMALL LETTER U WITH HORN AND TILDE
    case L'\x1EF0'/*Ự*/: return 'U';	// LATIN CAPITAL LETTER U WITH HORN AND DOT BELOW
    case L'\x1EF1'/*ự*/: return 'u';	// LATIN SMALL LETTER U WITH HORN AND DOT BELOW
    case L'\x1EF2'/*Ỳ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH GRAVE
    case L'\x1EF3'/*ỳ*/: return 'y';	// LATIN SMALL LETTER Y WITH GRAVE
    case L'\x1EF4'/*Ỵ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH DOT BELOW
    case L'\x1EF5'/*ỵ*/: return 'y';	// LATIN SMALL LETTER Y WITH DOT BELOW
    case L'\x1EF6'/*Ỷ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH HOOK ABOVE
    case L'\x1EF7'/*ỷ*/: return 'y';	// LATIN SMALL LETTER Y WITH HOOK ABOVE
    case L'\x1EF8'/*Ỹ*/: return 'Y';	// LATIN CAPITAL LETTER Y WITH TILDE
    case L'\x1EF9'/*ỹ*/: return 'y';	// LATIN SMALL LETTER Y WITH TILDE
    case L'\x2071'/*ⁱ*/: return 'i';	// SUPERSCRIPT LATIN SMALL LETTER I
    case L'\x207F'/*ⁿ*/: return 'n';	// SUPERSCRIPT LATIN SMALL LETTER N
    case L'\x212A'/*K*/: return 'K';	// KELVIN SIGN
    case L'\x212B'/*Å*/: return 'A';	// ANGSTROM SIGN
    case L'\x212C'/*ℬ*/: return 'B';	// SCRIPT CAPITAL B
    case L'\x212D'/*ℭ*/: return 'C';	// BLACK-LETTER CAPITAL C
    case L'\x212F'/*ℯ*/: return 'e';	// SCRIPT SMALL E
    case L'\x2130'/*ℰ*/: return 'E';	// SCRIPT CAPITAL E
    case L'\x2131'/*ℱ*/: return 'F';	// SCRIPT CAPITAL F
    case L'\x2132'/*Ⅎ*/: return 'F';	// TURNED CAPITAL F -- no decomposition
    case L'\x2133'/*ℳ*/: return 'M';	// SCRIPT CAPITAL M
    case L'\x2134'/*ℴ*/: return '0';	// SCRIPT SMALL O
    case L'\x213A'/*℺*/: return '0';	// ROTATED CAPITAL Q -- no decomposition
    case L'\x2141'/*⅁*/: return 'G';	// TURNED SANS-SERIF CAPITAL G -- no decomposition
    case L'\x2142'/*⅂*/: return 'L';	// TURNED SANS-SERIF CAPITAL L -- no decomposition
    case L'\x2143'/*⅃*/: return 'L';	// REVERSED SANS-SERIF CAPITAL L -- no decomposition
    case L'\x2144'/*⅄*/: return 'Y';	// TURNED SANS-SERIF CAPITAL Y -- no decomposition
    case L'\x2145'/*ⅅ*/: return 'D';	// DOUBLE-STRUCK ITALIC CAPITAL D
    case L'\x2146'/*ⅆ*/: return 'd';	// DOUBLE-STRUCK ITALIC SMALL D
    case L'\x2147'/*ⅇ*/: return 'e';	// DOUBLE-STRUCK ITALIC SMALL E
    case L'\x2148'/*ⅈ*/: return 'i';	// DOUBLE-STRUCK ITALIC SMALL I
    case L'\x2149'/*ⅉ*/: return 'j';	// DOUBLE-STRUCK ITALIC SMALL J
    // case L'\xFB00'/*ﬀ*/: return 'ff';	// LATIN SMALL LIGATURE FF
    // case L'\xFB01'/*ﬁ*/: return 'fi';	// LATIN SMALL LIGATURE FI
    // case L'\xFB02'/*ﬂ*/: return 'fl';	// LATIN SMALL LIGATURE FL
    // case L'\xFB03'/*ﬃ*/: return 'ffi';	// LATIN SMALL LIGATURE FFI
    // case L'\xFB04'/*ﬄ*/: return 'ffl';	// LATIN SMALL LIGATURE FFL
    // case L'\xFB05'/*ﬅ*/: return 'st';	// LATIN SMALL LIGATURE LONG S T
    // case L'\xFB06'/*ﬆ*/: return 'st';	// LATIN SMALL LIGATURE ST
    case L'\xFF21'/*Ａ*/: return 'A';	// FULLWIDTH LATIN CAPITAL LETTER B
    case L'\xFF22'/*Ｂ*/: return 'B';	// FULLWIDTH LATIN CAPITAL LETTER B
    case L'\xFF23'/*Ｃ*/: return 'C';	// FULLWIDTH LATIN CAPITAL LETTER C
    case L'\xFF24'/*Ｄ*/: return 'D';	// FULLWIDTH LATIN CAPITAL LETTER D
    case L'\xFF25'/*Ｅ*/: return 'E';	// FULLWIDTH LATIN CAPITAL LETTER E
    case L'\xFF26'/*Ｆ*/: return 'F';	// FULLWIDTH LATIN CAPITAL LETTER F
    case L'\xFF27'/*Ｇ*/: return 'G';	// FULLWIDTH LATIN CAPITAL LETTER G
    case L'\xFF28'/*Ｈ*/: return 'H';	// FULLWIDTH LATIN CAPITAL LETTER H
    case L'\xFF29'/*Ｉ*/: return 'I';	// FULLWIDTH LATIN CAPITAL LETTER I
    case L'\xFF2A'/*Ｊ*/: return 'J';	// FULLWIDTH LATIN CAPITAL LETTER J
    case L'\xFF2B'/*Ｋ*/: return 'K';	// FULLWIDTH LATIN CAPITAL LETTER K
    case L'\xFF2C'/*Ｌ*/: return 'L';	// FULLWIDTH LATIN CAPITAL LETTER L
    case L'\xFF2D'/*Ｍ*/: return 'M';	// FULLWIDTH LATIN CAPITAL LETTER M
    case L'\xFF2E'/*Ｎ*/: return 'N';	// FULLWIDTH LATIN CAPITAL LETTER N
    case L'\xFF2F'/*Ｏ*/: return 'O';	// FULLWIDTH LATIN CAPITAL LETTER O
    case L'\xFF30'/*Ｐ*/: return 'P';	// FULLWIDTH LATIN CAPITAL LETTER P
    case L'\xFF31'/*Ｑ*/: return 'Q';	// FULLWIDTH LATIN CAPITAL LETTER Q
    case L'\xFF32'/*Ｒ*/: return 'R';	// FULLWIDTH LATIN CAPITAL LETTER R
    case L'\xFF33'/*Ｓ*/: return 'S';	// FULLWIDTH LATIN CAPITAL LETTER S
    case L'\xFF34'/*Ｔ*/: return 'T';	// FULLWIDTH LATIN CAPITAL LETTER T
    case L'\xFF35'/*Ｕ*/: return 'U';	// FULLWIDTH LATIN CAPITAL LETTER U
    case L'\xFF36'/*Ｖ*/: return 'V';	// FULLWIDTH LATIN CAPITAL LETTER V
    case L'\xFF37'/*Ｗ*/: return 'W';	// FULLWIDTH LATIN CAPITAL LETTER W
    case L'\xFF38'/*Ｘ*/: return 'X';	// FULLWIDTH LATIN CAPITAL LETTER X
    case L'\xFF39'/*Ｙ*/: return 'Y';	// FULLWIDTH LATIN CAPITAL LETTER Y
    case L'\xFF3A'/*Ｚ*/: return 'Z';	// FULLWIDTH LATIN CAPITAL LETTER Z
    case L'\xFF41'/*ａ*/: return 'a';	// FULLWIDTH LATIN SMALL LETTER A
    case L'\xFF42'/*ｂ*/: return 'b';	// FULLWIDTH LATIN SMALL LETTER B
    case L'\xFF43'/*ｃ*/: return 'c';	// FULLWIDTH LATIN SMALL LETTER C
    case L'\xFF44'/*ｄ*/: return 'd';	// FULLWIDTH LATIN SMALL LETTER D
    case L'\xFF45'/*ｅ*/: return 'e';	// FULLWIDTH LATIN SMALL LETTER E
    case L'\xFF46'/*ｆ*/: return 'f';	// FULLWIDTH LATIN SMALL LETTER F
    case L'\xFF47'/*ｇ*/: return 'g';	// FULLWIDTH LATIN SMALL LETTER G
    case L'\xFF48'/*ｈ*/: return 'h';	// FULLWIDTH LATIN SMALL LETTER H
    case L'\xFF49'/*ｉ*/: return 'i';	// FULLWIDTH LATIN SMALL LETTER I
    case L'\xFF4A'/*ｊ*/: return 'j';	// FULLWIDTH LATIN SMALL LETTER J
    case L'\xFF4B'/*ｋ*/: return 'k';	// FULLWIDTH LATIN SMALL LETTER K
    case L'\xFF4C'/*ｌ*/: return 'l';	// FULLWIDTH LATIN SMALL LETTER L
    case L'\xFF4D'/*ｍ*/: return 'm';	// FULLWIDTH LATIN SMALL LETTER M
    case L'\xFF4E'/*ｎ*/: return 'n';	// FULLWIDTH LATIN SMALL LETTER N
    case L'\xFF4F'/*ｏ*/: return 'o';	// FULLWIDTH LATIN SMALL LETTER O
    case L'\xFF50'/*ｐ*/: return 'p';	// FULLWIDTH LATIN SMALL LETTER P
    case L'\xFF51'/*ｑ*/: return 'q';	// FULLWIDTH LATIN SMALL LETTER Q
    case L'\xFF52'/*ｒ*/: return 'r';	// FULLWIDTH LATIN SMALL LETTER R
    case L'\xFF53'/*ｓ*/: return 's';	// FULLWIDTH LATIN SMALL LETTER S
    case L'\xFF54'/*ｔ*/: return 't';	// FULLWIDTH LATIN SMALL LETTER T
    case L'\xFF55'/*ｕ*/: return 'u';	// FULLWIDTH LATIN SMALL LETTER U
    case L'\xFF56'/*ｖ*/: return 'v';	// FULLWIDTH LATIN SMALL LETTER V
    case L'\xFF57'/*ｗ*/: return 'w';	// FULLWIDTH LATIN SMALL LETTER W
    case L'\xFF58'/*ｘ*/: return 'x';	// FULLWIDTH LATIN SMALL LETTER X
    case L'\xFF59'/*ｙ*/: return 'y';	// FULLWIDTH LATIN SMALL LETTER Y
    case L'\xFF5A'/*ｚ*/: return 'z';	// FULLWIDTH LATIN SMALL LETTER Z
  }
  return w;
}
