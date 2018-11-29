#pragma once
#include <string>
#include <vector>
#include <unordered_map>
namespace Cry
{
	namespace Base
	{
		class DataBase
 		{
		public:
			using lPDataBase = DataBase;
			DataBase();
			~DataBase();
		public:
			// 初始
			bool Initialize();
		public:
			// 获得数据
			u32 Get(std::string Object);
		private:
			// 检查数据完整性
			bool CheckSucess();
		public:
			lPDataBase & GetDataBase() { return *this; };
		public:
			std::unordered_map<std::string, u32>			m_PointerEx;
		};
	};
};