#if !defined(CRY_STRINGTRIM_H)
#define CRY_STRINGTRIM_H
#pragma once
#include <Foundation.h>
#include <vector>
namespace Cry
{
	namespace Text
	{
		class FunctionExport StringTrim
		{
		public:
			enum Options
			{
				TOK_EMPTY = 1,			// É¾³ýÊ×Î²¿Õ
				TOK_TRIM = 2			// ·Ö¸î×Ö·û´®
			};
		public:
			StringTrim() = delete;
		public:
			StringTrim(const std::string lpszString, const std::string Mark, uint32_t nFlags = TOK_EMPTY | TOK_TRIM);

			typedef std::vector<std::string> Array;
			typedef Array::const_iterator Device;

			Device begin() const;
			Device end() const;
			std::size_t size() const;

			const std::string& operator [] (std::size_t index) const;
			std::string& operator [] (std::size_t index);
		public:
			static std::string Trim(std::string& lpszText);
		private:
			// ½ûÖ¹¸´ÖÆ´«Ö·
			StringTrim(const StringTrim&) = delete;
			StringTrim& operator = (const StringTrim&) = delete;
		private:
			Array										m_Result;
		};

		inline StringTrim::Device StringTrim::begin() const
		{
			return m_Result.begin();
		}
		inline StringTrim::Device StringTrim::end() const
		{
			return m_Result.end();
		}
		inline std::string& StringTrim::operator [] (std::size_t index)
		{
			return m_Result[index];
		}
		inline const std::string& StringTrim::operator [] (std::size_t index) const
		{
			return m_Result[index];
		}
		inline std::size_t StringTrim::size() const
		{
			return m_Result.size();
		}
	}
}
#endif