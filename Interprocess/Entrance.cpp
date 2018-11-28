#include <Global>
#include <Helper>
#include <Cry.FirstLication.h>
#include <Entrance.h>
#include <QtPlugin>
#include <QTextCodec>
#include <QMessageBox>
#include <QStyleFactory>
#include <QMetaType>
#include <Module.h>
#include <Interprocess/Cry.Signal.Service.h>
#include <Import/Cry.Glog.hpp>
#include <Import/Cry.Event.hpp>
#include <Import/Cry.Proto.hpp>
#include <charconv>
//#include <google/protobuf/message.h>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

int32_t CryEntrance::Run(HINSTANCE hInstance, int nCmdCount, Cry::Signal::NetworkEngineService * Service)
{
	char lpFilename[1][MAX_PATH];
	char *argv[] = { lpFilename[0] };
	if (Cry::Kernel::Module::GetModuleFullPath(hInstance, lpFilename[0]))
	{
		QApplication a(nCmdCount, argv);
		qRegisterMetaType<uint32_t>("uint32_t");
		//qRegisterMetaType<std::string>("std::string");
		m_Windwos = std::move(Service->SetWindowsInterface(std::make_shared<QWindows::FirstLication>(Service, nullptr)));
		this->show();
		return a.exec();
	}
	return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	Cry::Import::InitializeGlog Init_Golg;
	{
		Cry::Import::InitializeEvent Init_Event;
		Cry::Import::InitializeProto Init_Proto;
		{
			Cry::Signal::NetworkEngineService Service("0.0.0.0:9999", "Inter.Process.Service", 3);
			if (Service.CreateService())
			{
				if (theapp.Run(hInstance, 1, std::move(&Service)) == QDialog::Rejected)
				{
					if (!Service.CancelService())
					{
						LOG_INFO << "SignalServer Stop Fail";
					}
					else
					{
						LOG_INFO << "SignalServer Stop Okay";
					}
				}
			}
		}
	}
	LOG_INFO << "Bye Bye";
	return 0;
}