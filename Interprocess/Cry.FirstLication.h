#pragma once
#include <Interface/AnyFrame.hpp>
#include <QWidget>
#include <QtWin>
#include <QApplication>
#include <QStyleFactory>
#include <QMessageBox>
#include <QVariant>
#include <QFrame>
#include <QHBoxLayout>
#include <QEvent>
#include <QTabWidget>
#include <QCheckBox>
#include <QPushButton>
#include <Action/Cry.Action.Interface.h>
#include <google/protobuf/message.h>
namespace Cry
{
	namespace Signal
	{
		class NetworkEngineService;
		class Work;
	}
};
namespace QWindows
{
	class FirstLication : public QWidget, public Cry::Action::UnknownInterfaceEx
	{
	public:
		Q_OBJECT
	public:
		explicit FirstLication(Cry::Signal::NetworkEngineService* Server, QWidget *Parent = nullptr);
		~FirstLication();
		enum
		{
			主体框架,
			主体标签,
			基本设置,
			保护设置,
			水平框架,
			水平布局,
			攻击不卡,
			魔法不卡,
			超级不卡,

			测试框架 = 1000,
			测试布局,
			注入消息,
			卸载消息,
			发送消息,
		};
	private:
		void OnInjection();
		void OnUninstall();
	protected slots:
		void OnSend();
	protected slots:
		bool OnNotify(const uint32_t uMsg, const void * pData, const uint32_t uSize);
	signals:
		bool SendNotify(const uint32_t uMsg, const void * pData, const uint32_t uSize);
		bool PostNotify(const uint32_t uMsg, const google::protobuf::Message & pData);
	private:
		virtual bool OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize) override;
	public:
		AnyEx										m_Pair;
	private:
		QTabWidget									*m_Tab;
		QWidget										*m_Widget[5];
		QWidget										*m_WidgetLayout;
		QCheckBox									*m_CheckBox[3];
		QHBoxLayout									*m_HBoxLayout;
		// 测试框架使用
		QWidget										*m_TestWidget;
		QHBoxLayout									*m_TestLayout;
		QPushButton									*m_PushButton[3];
	private:
		Cry::Signal::NetworkEngineService*						m_Service;
	public:
		bool SetupInterface(QWidget *Parent);
	};
}