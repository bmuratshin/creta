#pragma once

	extern void throw_(const char *str);
	void fthrow_(const char* fmt, ...);
	extern int64_t __wtoi64(const wchar_t *s);
	extern int64_t __str2i64(const char *s, unsigned base);
	extern int64_t parse_string_literal(wchar_t **str_ptr, wchar_t *result, wchar_t bra = L'"');
	extern int64_t escape_string_literal(const wchar_t *str, wchar_t *result, int64_t&result_len);
	extern int64_t escape_sql_literal(const wchar_t *str, wchar_t *result, int64_t&result_len);
	extern int64_t escape_json_literal(const wchar_t *str, wchar_t *result, int64_t&result_len);
	extern int64_t escape_sql_string_nl(const char* str, char* result, int64_t& result_len);

