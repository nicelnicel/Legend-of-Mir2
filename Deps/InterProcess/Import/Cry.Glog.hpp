#pragma once
#include <string>
#include <glog/logging.h>
namespace Cry
{
	namespace Import
	{
		class InitializeGlog
		{
		public:
			InitializeGlog(const std::string &logName = std::string("Server"), const std::string &desDir = std::string("./Log/"))
			{
				google::InitGoogleLogging(logName.c_str());
				google::SetLogDestination(google::GLOG_INFO, desDir.c_str());
				google::InstallFailureSignalHandler();
				FLAGS_colorlogtostderr = true;
				FLAGS_stop_logging_if_full_disk = true;
				FLAGS_v = 3;
			}
			~InitializeGlog()
			{
				// 回收所有动态分配的对象
				google::ShutdownGoogleLogging();
			}
		};
	}
}