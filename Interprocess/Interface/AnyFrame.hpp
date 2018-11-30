#pragma once
#if !defined(_AnyFrame_)
#define _AnyFrame_
#include <map>
#include <any>
class AnyEx
{
public:
	template<class _Valty>
	auto insert(uint32_t uId, _Valty&& _Val) -> _Valty
	{
		if (m_pair.find(uId) == std::end(m_pair))
		{
			return std::any_cast<_Valty>(std::move(m_pair.emplace(std::pair(uId, _Val)).first->second));
		}
		throw std::string("创建窗口组件错误");
	};
	template<class _Valty>
	auto find(uint32_t uId) -> _Valty
	{
		if (m_pair.find(uId) != std::end(m_pair))
		{
			return std::any_cast<_Valty>(std::move(m_pair.find(uId)->second));
		}
		return nullptr;
	};
	template<class _Valty>
	void release(uint32_t uId)
	{
		if (m_pair.find(uId) != std::end(m_pair))
		{
			delete std::any_cast<_Valty>(std::move(m_pair.find(uId)->second));
			m_pair.erase(uId);
		}
	};
public:
	std::map<uint32_t, std::any>				m_pair;
};
#endif