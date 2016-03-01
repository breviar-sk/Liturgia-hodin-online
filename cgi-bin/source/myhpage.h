/************************************************************************/
/*                                                                      */
/* myhpage.h                                                            */
/* (c)1999-2016 | Juraj Vidéky | videky@breviar.sk                      */
/*                                                                      */
/* description | HTML document dynamically generated header and footer  */
/*                                                                      */
/************************************************************************/

#include "vstudio.h"
#include "myexpt.h"

#ifndef __MYHPAGE_H_
#define __MYHPAGE_H_

#define HTML_TOP "p-top"
#define HTML_ANAME_TOP "<div id=\"contentRoot\"><a name=\""HTML_TOP"\"></a>"

#define HTML_TRANSPARENT_NAV_ARROW \
"iVBORw0KGgoAAAANSUhEUgAAADIAAAAyCAYAAAAeP4ixAAAABHNCSVQICAgIfAhkiAAAAAlwSFlz" \
"AAAAbwAAAG8B8aLcQwAAABl0RVh0U29mdHdhcmUAd3d3Lmlua3NjYXBlLm9yZ5vuPBoAABGxSURB" \
"VGiBzVpdjBxXlf7OvfXT1V3dM+NJ99jxOrYm0TiZsZcQWyCBsp4AUQQPINaaAMKKFiSzTxBpEYqw" \
"hCaDhBAgoezLLkJCKA+rleiHXQhKyDprjUVw5M1iiONxEm8ycrzjZHDHnunu6q7qqnvP2Qd3De35" \
"cX7WDxzpakZV1bfOd8/fd88tEhHcKiEiWj/f3Nwc5f/Pzs7Kuucht0gB51ZMkgMQEczNzdHs7Czq" \
"9ToBwKFDh9aA1Ot1AYCZmRmZm5vLQdCtALRhBT/IHMD1lZ+cnKRqtUoXLlygkZERmpqawptvvrkG" \
"ZPfu3bKwsIDx8XFpt9vSaDTk/PnzMmCpD6zM/xdIriTNz8+rcrlMV65cUUEQUBRFyvM88jyPWq0W" \
"VSoVSdNU0jSVOI4lDEOu1Wq8CaAPpNAHcq3clQatUKvV1MLCgh4aGlJxHOswDFWv11NRFKlKpQIA" \
"0FoLEXEYhjYIAk7T1MZxzCsrKzw5OcnrXvO+AL1fIAQAjz/+eO7/qlwuU7vd1ktLSzoMQy0ijtba" \
"6fV62vd9rbVWzExJksBxHPY8z4qI8X3fdDodq7U2ExMTttFo0Pz8PA9YJ1+09xQ/7+pag5lo0AK5" \
"Gw0PD6tGo+ForZ1KpeI0m03PcRxXa+0SkcPMWilFzCxaawZgrLWZtTbTWqciYsIwzFZWVqzW2m7h" \
"brlsqeyWQNalUqrX6xsA9Ho9bYzRSZK4ffFExM+HUso1xjhElMeS0VpnxpiUiHoAekTUM8ZkQRBk" \
"rVbLKqWs1tpGUSTVapUbjYbkWW52dla2stBWQDZkos0AEJEDwLHWeiLiE1GBiArMHBBRAYBPRC4z" \
"K6UUi4hRSqUikmit4zRNE611nGVZqrVOsyzLjDFGKWWVUjYMQ240GpwDulmG2wBkfSCvrKyoXbt2" \
"bQlAa+2KiG+tDZRSgYgUAZSIKGDmgrXWO3HixJ6DBw++vW3btghAj5ljx3E61touEXVFJAHQ01qn" \
"juOkAAwAM2ihWq3GBw4c4D6ADWA2swjlIMbHx1W73dZpmmprrfY8z80BWGu93JX6VigCKAEoiUjY" \
"arWGf/azn93/u9/97m+iKBr2PC85cODAC1/96ldP3HHHHVcAdEQkygGJSOI4TmKMSbXWqbU2y7Is" \
"KxQKGTMbz/NsuVy27XZbpqenGcANbrYeyA0gXn75ZX377bfrbrfr+r7v+r5/QwwQUSG3xACIMjOH" \
"x44dO/yHP/zhgO/7UqlUKIoixHGM7du3X37yySf/WUQiIooARAA6RBSLSJxbx3XdRCnVS9M0zbIs" \
"K5VKGQBTLpft4uIir687G4CgX9ziONZaa6fb7brFYtHr+3shdx9rbQCgSESBUqrIzCUAoYiUm83m" \
"yJEjR/7e9333jjvuWJu80Wig0Wjge9/73r8cPHjwIoBIRCIAHa11h5njvqvFRNS11sbMnPi+nyRJ" \
"krqum1prTRAEtp8EOLeKGowNAKjX69RoNNTw8LCy1mrf910APjMXiSg0xgwx8wgRjRLRbQCqzFwD" \
"UOv/rT799NP3ZVnmjo6OQmu9Nm677TYQEZ599tkDzFwVkSqAmlKqaq2tichtzDwqIiMAhpi57Hle" \
"sdfrFVzXdZVSjrVWNxoNlSej3BBrBTEP8EOHDlEcx1QqlVSr1XKUUi6AgogUmblMRBURqSilyiJS" \
"zl1qwLVKrVZrFADCMITWes0iWmu4ritRFA33FyEAUOzHVxdARESBiPjM7PSLqSil2PM8a621zMzV" \
"apUB8GCNuaGyz87O4qc//SmNjIyoy5cva621Y631lFK+4zjFvusMvfbaa3t+8pOf/O2lS5f2pmnq" \
"jY+PLx89evT81NSUARA4jhPkig8CGQDkisg2IgoajcbIE088cc8rr7yyU0SkWq0ufelLX/r3Bx54" \
"4JyICBFZIjLW2gxAViwWje/75Hke1et1mpmZEQBQgy+o1+s0MjJCQRBQEARKRLTW2gXgAygwc7i4" \
"uLjj2LFjj73yyiv3ua5bKpfL7uuvv/5X3/72tz91+vTp3QCGtdaFQSCDAwAppVwRGb58+fLY17/+" \
"9QfPnDlzp+/7hWKxGFy+fPmuH/3oR/9w/PjxfVrrUj+R+Eopl4gca61ut9tqcXGRBnW/AUgunudR" \
"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" \

#define HTML_TRANSPARENT_NAV "<div style=\"position: fixed; bottom: 2px; right: 2px;\">" \
  "<img src=\"data:image/png;base64," HTML_TRANSPARENT_NAV_ARROW "\" "                \
  "  onclick=\"window.scrollBy(0, window.innerHeight)\"/></div>\n"

#define HTML_BOTTOM "p-bottom"
#define HTML_ANAME_BOTTOM "<a name=\""HTML_BOTTOM"\"></a></div>"

#define HTML_P_PATKA "p class=\"patka\""

// header
void hlavicka(char *title, short int level = 0, short int spec = 0);
void hlavicka(char *title, FILE * expt, short int level = 0, short int spec = 0);

// XML header
void xml_hlavicka(void);
void xml_hlavicka(FILE * expt);

// footer
void patka(void);
void patka(FILE * expt);

// XML footer
void xml_patka(void);
void xml_patka(FILE * expt);

void myhpage_init_globals();

#endif // __MYHPAGE_H_

