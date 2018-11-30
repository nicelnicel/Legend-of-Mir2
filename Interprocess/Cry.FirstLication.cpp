#include <Global>
#include <Cry.FirstLication.h>
#include <Injection/Message.h>
#include <InterProcess/Cry.Signal.Service.h>
#include <SendCmd.pb.h>
#include <StringXor.h>
namespace QWindows
{
	FirstLication::FirstLication(Cry::Signal::NetworkEngineService* Service, QWidget *Parent) : QWidget(Parent), m_Service(Service)
	{
		if (!m_Service->GetObjectInterface()->Add("FirstLication", this))
		{
			DebugMsg("对象[%s]已经存在\n", "FirstLication");
		}
		this->SetupInterface(this);
	}

	FirstLication::~FirstLication()
	{

	}
	bool FirstLication::SetupInterface(QWidget *Parent)
	{
		uint32_t w = 0, h = 0;
		if (!QtWin::isCompositionEnabled())
		{
			w = 602;
			h = 400;
			DebugMsg("Aero:关闭[%d] w:%d h:%d\n", reinterpret_cast<HWND>(this->winId()), w, h);
			QApplication::setStyle(QStyleFactory::create("Fusion"));
		}
		else
		{
			w = 600;
			h = 400;
			DebugMsg("Aero:开启[%d] w:%d h:%d\n", reinterpret_cast<HWND>(this->winId()), w, h);
		}
		if (this->QWidget::objectName().isEmpty())
		{
			this->QWidget::setObjectName(QStringLiteral("Dialog"));
		}
		this->setWindowTitle(QString::fromLocal8Bit(_T("")));
		this->resize(w, h);
		this->setMaximumSize(QSize(w, h));
		this->setMinimumSize(QSize(w, h));
		this->setWindowFlags(this->windowFlags()& ~Qt::WindowMaximizeButtonHint);
		this->setFixedSize(QSize(w, h));
		try
		{
			(m_Tab = m_Pair.insert(主体框架, new QTabWidget(Parent)))->setObjectName(QString::fromLocal8Bit(_T("主体标签")));
			(m_Widget[0] = m_Pair.insert(基本设置, new QWidget(m_Tab)))->setObjectName(QString::fromLocal8Bit(_T("基本设置")));
			(m_Widget[1] = m_Pair.insert(保护设置, new QWidget(m_Tab)))->setObjectName(QString::fromLocal8Bit(_T("保护设置")));
			/* 水平布局 Star*/
			(m_WidgetLayout = m_Pair.insert(水平框架, new QWidget(m_Widget[0])))->setObjectName(QString::fromLocal8Bit(_T("水平框架")));
			(m_HBoxLayout = m_Pair.insert(水平布局, new QHBoxLayout(m_WidgetLayout)))->setObjectName(QString::fromLocal8Bit(_T("水平布局")));
			(m_CheckBox[0] = m_Pair.insert(攻击不卡, new QCheckBox()))->setObjectName(QString::fromLocal8Bit(_T("攻击不卡")));
			(m_CheckBox[1] = m_Pair.insert(魔法不卡, new QCheckBox()))->setObjectName(QString::fromLocal8Bit(_T("魔法不卡")));
			(m_CheckBox[2] = m_Pair.insert(超级不卡, new QCheckBox()))->setObjectName(QString::fromLocal8Bit(_T("超级不卡")));
			/* 水平布局 End*/
			/* 测试布局 Star*/
			(m_TestWidget = m_Pair.insert(测试框架, new QWidget(m_Widget[0])))->setObjectName(QString::fromLocal8Bit(_T("测试框架")));
			(m_TestLayout = m_Pair.insert(测试布局, new QHBoxLayout(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("测试布局")));
			(m_PushButton[0] = m_Pair.insert(注入消息, new QPushButton(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("注入消息")));
			(m_PushButton[1] = m_Pair.insert(卸载消息, new QPushButton(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("卸载消息")));
			(m_PushButton[2] = m_Pair.insert(发送消息, new QPushButton(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("发送消息")));
			{
				m_Tab->setGeometry(QRect(2, 2, 598, 397)); 
				m_Tab->addTab(m_Widget[0], QString::fromLocal8Bit(_T("基本设置")));
				m_Tab->addTab(m_Widget[1], QString::fromLocal8Bit(_T("保护设置")));
				m_Tab->setCurrentIndex(0);
				m_WidgetLayout->setGeometry(QRect(10, 10, 240, 20));
				m_HBoxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
				m_HBoxLayout->setContentsMargins(0, 0, 0, 0); 
				
				m_HBoxLayout->addWidget(m_CheckBox[0]); 
				m_HBoxLayout->addWidget(m_CheckBox[1]);
				m_HBoxLayout->addWidget(m_CheckBox[2]);

				m_CheckBox[0]->setText(QString::fromLocal8Bit(_T("攻击不卡")));
				m_CheckBox[1]->setText(QString::fromLocal8Bit(_T("魔法不卡")));
				m_CheckBox[2]->setText(QString::fromLocal8Bit(_T("超级不卡")));
				for (auto &Args : m_CheckBox)
				{
					Args->setStyle(QStyleFactory::create(_T("Fusion")));
				}
				m_TestWidget->setGeometry(QRect(320, 330, 250, 26));
				m_TestLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
				m_TestLayout->setContentsMargins(0, 0, 0, 0);

				m_TestLayout->addWidget(m_PushButton[0]);
				m_TestLayout->addWidget(m_PushButton[1]);
				m_TestLayout->addWidget(m_PushButton[2]);

				m_PushButton[0]->setText(QString::fromLocal8Bit(_T("注入消息")));
				m_PushButton[1]->setText(QString::fromLocal8Bit(_T("卸载消息")));
				m_PushButton[2]->setText(QString::fromLocal8Bit(_T("发送消息")));

				for (auto &Args : m_PushButton)
				{
					Args->setStyle(QStyleFactory::create(_T("Fusion")));
				}
				
				QObject::connect(m_PushButton[0], &QPushButton::clicked, this, &FirstLication::OnInjection);
				QObject::connect(m_PushButton[1], &QPushButton::clicked, this, &FirstLication::OnUninstall);
				QObject::connect(m_PushButton[2], &QPushButton::clicked, this, &FirstLication::OnSend);

				/*
				1、Qt::AutoConnection： 默认值，使用这个值则连接类型会在信号发送时决定。如果接收者和发送者在同一个线程，则自动使用Qt::DirectConnection类型。如果接收者和发送者不在一个线程，则自动使用Qt::QueuedConnection类型。
				2、Qt::DirectConnection：槽函数会在信号发送的时候直接被调用，槽函数运行于信号发送者所在线程。效果看上去就像是直接在信号发送位置调用了槽函数。这个在多线程环境下比较危险，可能会造成奔溃。
				3、Qt::QueuedConnection：槽函数在控制回到接收者所在线程的事件循环时被调用，槽函数运行于信号接收者所在线程。发送信号之后，槽函数不会立刻被调用，等到接收者的当前函数执行完，进入事件循环之后，槽函数才会被调用。多线程环境下一般用这个。
				4、Qt::BlockingQueuedConnection：槽函数的调用时机与Qt::QueuedConnection一致，不过发送完信号后发送者所在线程会阻塞，直到槽函数运行完。接收者和发送者绝对不能在一个线程，否则程序会死锁。在多线程间需要同步的场合可能需要这个。
				5、Qt::UniqueConnection：这个flag可以通过按位或（|）与以上四个结合在一起使用。当这个flag设置时，当某个信号和槽已经连接时，再进行重复的连接就会失败。也就是避免了重复连接。
				*/

				QObject::connect(this, &FirstLication::SendNotify, this, &FirstLication::OnNotify, Qt::BlockingQueuedConnection);

				QObject::connect(this, &FirstLication::PostNotify, m_Service, &Cry::Signal::NetworkEngineService::OnNotify);
			}
			QMetaObject::connectSlotsByName(this);
		}
		catch (std::string e)
		{
			DebugMsg(e.c_str());
		}
		return true;
	}
	bool FirstLication::OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize)
	{
		return emit SendNotify(uMsg, pData, uSize);
	}
	bool FirstLication::OnNotify(const uint32_t uMsg, const void * pData, const uint32_t uSize)
	{
		SocketData::CmdResponse Resp;
		if (!Resp.ParsePartialFromArray(pData, uSize))
		{
			return false;
		}
		if (Resp.status())
		{
			this->setWindowTitle(QString::fromLocal8Bit("客户端返回正确"));
		}
		else
		{
			this->setWindowTitle(QString::fromLocal8Bit("客户端返回错误"));
		}
		return false;
	}
	void FirstLication::OnInjection()
	{
		if (Cry::Kernel::Message::InstallWindowsMessageEx(FindWindow("TApplication", "Legend of Mir2"), TEXT("./Library.dll"), TEXT("InterFaceDll")))
		{
			DebugMsg("安装成功\n");
		}
	}
	void FirstLication::OnUninstall()
	{
		if (PostMessage(FindWindow("TApplication", "Legend of Mir2"), WM_USER + 9999, 9527, 1))
		{
			if (!SleepEx(30, TRUE))
			{
				if (Cry::Kernel::Message::UninstallWindowsMessageEx())
				{
					DebugMsg("卸载成功\n");
				}
			}
		}
	}
	void FirstLication::OnSend()
	{
		SocketData::CmdRequest Req;
		Req.set_content(Cry::Encrypt::Xor::Operate("是大家我就看了阿萨"));
		Req.set_timer(1111);

		if (!emit PostNotify(0, Req))
		{
			DebugMsg("发送失败\n");
		}
	}
}