#pragma once
#include <CoreImport.h>
#include <google/protobuf/stubs/common.h>

namespace Cry
{
	namespace Import
	{
		class InitializeProto
		{
		public:
			InitializeProto() = default;
			~InitializeProto()
			{
				// 回收所有动态分配的对象
				google::protobuf::ShutdownProtobufLibrary();
			}
		};
	};
};


