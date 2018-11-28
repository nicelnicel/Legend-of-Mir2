#include <Standard>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <string>
#include <mutex>
namespace Cry
{
	namespace Action
	{
		class remove_queue
		{
		public:
			explicit remove_queue() = default;
			explicit inline remove_queue(std::string name) : m_name(name)
			{
				this->remove();
			}
			inline  ~remove_queue()
			{
				this->remove();
			}
			inline void remove()
			{
				if (boost::interprocess::message_queue::remove(m_name.c_str()))
				{
					DebugMsg("remove ok\n");
				}
				else
				{
					DebugMsg("remove fail\n");
				}
			}
		private:
			std::string							m_name;
		protected:
			remove_queue(const remove_queue&);
		};

		class message_queue : protected remove_queue, boost::interprocess::message_queue
		{
		public:
			explicit message_queue() = default;
			explicit message_queue(boost::interprocess::create_only_t obj, std::string name, uint32_t max_num_msg, uint32_t max_msg_size) : remove_queue(name), boost::interprocess::message_queue(obj, name.c_str(), max_num_msg, max_msg_size)
			{

			}
			explicit message_queue(boost::interprocess::open_only_t obj, std::string name) : boost::interprocess::message_queue(obj, name.c_str())
			{

			}

			virtual ~message_queue()
			{

			}
			void send(const void * data, const uint32_t buffer_size, uint32_t priority = 0)
			{
				std::lock_guard<std::mutex> lockGuard(m_send);
				{
					this->boost::interprocess::message_queue::send(data, buffer_size, priority);
				}
			}
			bool try_send(const void * data, const uint32_t buffer_size, uint32_t priority = 0)
			{
				return this->boost::interprocess::message_queue::try_send(data, buffer_size, priority);
			}
			bool receive(void * buffer, const uint32_t max_msg_size, uint32_t & recvd_size, uint32_t & priority)
			{
				std::lock_guard<std::mutex> lockGuard(m_recv);
				{
					this->boost::interprocess::message_queue::receive(buffer, max_msg_size, recvd_size, priority);
				}
				return recvd_size > 0;
			}
			bool try_receive(void * buffer, const uint32_t max_msg_size, uint32_t & recvd_size, uint32_t & priority)
			{
				return this->boost::interprocess::message_queue::try_receive(buffer, max_msg_size, recvd_size, priority);
			}
			bool empty() const
			{
				return this->msg_count() == 0;
			}
			/// 缓冲区大小
			uint32_t buff_size() const
			{
				return this->boost::interprocess::message_queue::get_max_msg_size();
			}
			/// 最大消息
			uint32_t msg_size() const
			{
				return this->boost::interprocess::message_queue::get_max_msg();
			}
			/// 剩余消息
			uint32_t msg_count() const
			{
				return this->boost::interprocess::message_queue::get_num_msg();
			}
		public:
			std::mutex								m_send;
			std::mutex								m_recv;
		protected:
			message_queue(const message_queue&) = delete;
		};
	};
};