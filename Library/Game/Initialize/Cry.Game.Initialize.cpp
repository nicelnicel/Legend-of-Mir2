#include <Global>
#include <Game/Initialize/Cry.Game.Initialize.h>
#include <Import/Memory/Cry.Game.Compare.hpp>
namespace Cry
{
	namespace Base
	{

		DataBase::DataBase()
		{
			/*u32 uResult = ;*/
		}
		DataBase::~DataBase()
		{
		}

		bool DataBase::Initialize()
		{
			bool bSucess = true;

			try
			{
				///发送文本 -> (BE ? ? ? ? ? ? ? ? ? ? ? ? 8B 06 8B 08 FF ? ? ? ? 8B D0)
				m_PointerEx.emplace(std::make_pair("\xD7\x1F\xAB\x70\xAE\x79\xD1\x03\x00\x00", Cry::Memory::Masks::SearchMemoryEx(0x516000, 0x516FFF, "\x22\xF8\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x22\x9D\x50\x8B\x40\x85\x22\x9D\x50\x85\x40\xFB\x26\x9D\x5F\x82\x40\x82\x5F\x9D\x58\xFF\x40\xF9\x50\x00\x00")));
				
				bSucess = this->CheckSucess();
			}
			catch (std::exception & e)
			{
				DebugMsg("初始化数据出现异常[%s]\n", e.what());
				bSucess = false;
				
			}
			return bSucess;
		}
		u32 DataBase::Get(std::string lpszObject)
		{
			if (!m_PointerEx.empty())
			{
				if (auto list = m_PointerEx.find(lpszObject); list != std::end(m_PointerEx))
				{
					return list->second;
				}
			}
			return 0;
		}
		bool DataBase::CheckSucess()
		{
			bool bSucess = true;
			for (auto & [Object, Pointer] : m_PointerEx)
			{
				if (!Pointer)
				{
					DebugMsg("游戏对象[%s]初始失败\n", Text::Xor::Operate(Object.c_str()).c_str());
					bSucess = false;
				}
				else
				{
					DebugMsg("游戏对象[%s]初始成功 [%p]\n", Text::Xor::Operate(Object.c_str()).c_str(), Pointer);
				}
			}
			return bSucess;
		}
	};
};