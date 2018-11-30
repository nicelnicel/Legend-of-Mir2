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
			DataBase() = default;
			virtual ~DataBase();
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
			DataBase & GetDataBase() { return *this; };
		public:
			std::unordered_map<std::string, u32>			m_PointerEx;
		protected:
			DataBase(const DataBase &) = default;
			DataBase &operator=(const DataBase &) = default;
		};
	};
};