#include "StringTrim.h"
#include <Ascii.hpp>
namespace Cry
{
	namespace Text
	{
		StringTrim::StringTrim(const std::string lpszString, const std::string Mark, uint32_t nFlags)
		{
			std::string lpszText;
			bool bTrim = ((nFlags & TOK_TRIM) != 0);
			bool bEmpty = ((nFlags & TOK_EMPTY) != 0);
			bool LastLoop = false;
			for (auto it = lpszString.begin(); it != lpszString.end(); ++it)
			{
				if (Mark.find(*it) != std::string::npos)
				{
					if (bTrim)
					{
						this->Trim(lpszText);
					}
					if (!lpszText.empty() || !bEmpty)
					{
						m_Result.push_back(lpszText);
					}
					if (!bEmpty)
					{
						LastLoop = true;
					}
					lpszText.clear();
				}
				else
				{
					lpszText += *it;
					LastLoop = false;
				}
			}
			if (!lpszText.empty())
			{
				if (bTrim)
				{
					this->Trim(lpszText);
				}
				if (!lpszText.empty() || !bEmpty)
				{
					m_Result.push_back(lpszText);
				}
			}
			else if (LastLoop)
			{
				m_Result.push_back(std::string());
			}
		}
		std::string StringTrim::Trim(std::string& lpszText)
		{
			std::string::size_type front = 0;
			std::string::size_type back = 0;
			std::string::size_type length = lpszText.length();
			std::string::const_iterator tIt = lpszText.begin();
			std::string::const_iterator tEnd = lpszText.end();
			for (; tIt != tEnd; ++tIt, ++front)
			{
				if (!Ascii::isSpace(*tIt))
				{
					break;
				}
			}
			if (tIt != tEnd)
			{
				std::string::const_reverse_iterator tRit = lpszText.rbegin();
				std::string::const_reverse_iterator tRend = lpszText.rend();
				for (; tRit != tRend; ++tRit, ++back)
				{
					if (!Ascii::isSpace(*tRit))
					{
						break;
					}
				}
			}
			lpszText = lpszText.substr(front, length - back - front);
			return lpszText;
		}
	}
}