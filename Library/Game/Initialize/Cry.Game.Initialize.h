#pragma once
#include <string>
#include <vector>
namespace Cry
{
	namespace Base
	{
		struct Pointer
		{
		public:
			Pointer() {};
			Pointer(std::string Object, u32 uValue) : m_Object(Object), m_Pointer(uValue) {};
			~Pointer() {};
		public:
			inline Pointer & operator=(const Pointer & uValue)
			{
				return *this;
			};
			inline bool operator==(const u32 & uValue)
			{
				return this->m_Pointer == uValue;
			};
			inline bool operator!=(const u32 & uValue)
			{
				return this->m_Pointer != uValue;
			};
			operator u32() const
			{
				return this->m_Pointer;
			}
			operator i32() const
			{
				return this->m_Pointer;
			}
			operator std::string() const
			{
				return this->m_Object;
			}
			inline Pointer* operator->()
			{
				return this;
			};
		public:
			std::string			m_Object;		// Game Class
			u32					m_Pointer;		// Long Pointer
		};

		typedef Pointer *lPPointer;

		class DataBase
 		{
		public:
			using lPDataBase = DataBase;
			DataBase();
			~DataBase();
		public:
			bool Initialize();
		public:
			lPDataBase & GetDataBase() { return *this; };
		public:
			
			std::vector<Pointer>			m_Pointer;
		};
	};
};