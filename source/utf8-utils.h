/**********************************************************/
/*                                                        */
/* utf8-utils.h                                           */
/* (c)2014-2021 | Juraj Vidéky, Richard Královič          */
/*                                                        */
/* description | utilities for UTF-8 (Unicode) encoding   */
/*               (string manipulation, etc.)              */
/*                                                        */
/**********************************************************/

#ifndef __UTF8_UTILS_H_
#define __UTF8_UTILS_H_

struct Utf8DecoderState {
	int to_read;
	int result;
};

inline void InitUtf8DecoderState(struct Utf8DecoderState* state) {
	state->to_read = -1;
	state->result = 0;
}

inline int Utf8StreamingDecoder(char c, struct Utf8DecoderState* state) {
	if ((c & 0x80) == 0) {
		state->to_read = 0;
		state->result = c;
		return 1;
	}
	if ((c & 0xe0) == 0xc0) {
		state->to_read = 1;
		state->result = c & 0x3f;
		return 0;
	}
	if ((c & 0xf0) == 0xe0) {
		state->to_read = 2;
		state->result = c & 0x0f;
		return 0;
	}
	if ((c & 0xf8) == 0xf0) {
		state->to_read = 3;
		state->result = c & 0x07;
		return 0;
	}
	if (state->to_read > 0 && (c & 0xc0) == 0x80) {
		state->to_read--;
		state->result = (state->result << 6) | (c & 0x3f);
		return !state->to_read;
	}
	state->to_read = -1;
	return 0;
}

inline int DecodeWchar(const char** s) {
	struct Utf8DecoderState state;
	InitUtf8DecoderState(&state);
	while (!Utf8StreamingDecoder(*(*s)++, &state)) {}
	return state.result;
}

inline void EncodeWchar(int w, char** s) {
	if (w < 0x80) {
		*((*s)++) = w;
	}
	else if (w >= (1 << 22)) {
		*((*s)++) = '?';
	}
	else {
		char buf[3];
		int len = 0;
		int pfx = 0x80;

		while (w >= (1 << (6 - len))) {
			pfx = 0x80 | (pfx >> 1);
			buf[len++] = (w & 0x3f) | 0x80;
			w = w >> 6;
		}
		*((*s)++) = pfx | w;
		while (len > 0) {
			*((*s)++) = buf[--len];
		}
	}
}

// Safely append wchar at given position into a buffer
inline void AppendWchar(int w, int buf_size, char* buf, int* index) {
	if (buf_size - *index < 5) return;
	char* s = buf + *index;
	EncodeWchar(w, &s);
	*index = (int)(s - buf);
}

int WcharToUppercase(int w);

int RemoveDiacriticsFromWchar(int w);

#endif // __UTF8_UTILS_H_
