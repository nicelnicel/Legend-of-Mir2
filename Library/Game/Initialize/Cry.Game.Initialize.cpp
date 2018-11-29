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
			m_Pointer.emplace(m_Pointer.begin(), "123", Cry::Memory::Masks::SearchMemoryEx(0x401000, 0x5F9FFF, "\x58\xFF\x40\xF9\x53\x9D\x25\x85\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x54\x9D\x23\x8D\x40\x8A\x54\x9D\x5F\x82\x40\x85\x50\x9D\x22\xFF\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x8D\x50"));
			for (auto & [Object, Pointer] : m_Pointer)
			{
				if (!Pointer)
				{
					DebugMsg("∂‘œÛ[%s]≥ı º ß∞‹%08X\n", Object.c_str(), Pointer);
					return false;
				}
			}
			return true;
		}
	};
};