#pragma once
#include <string>
#include "../model/PerformElement.h"
#include "../CEventBuffer.h"

namespace chilli{
	namespace Device {

		class Device :public model::PerformElement {
		protected:
			typedef std::shared_ptr<fsm::StateMachine> Connction;

		public:
			Device(model::ProcessModule * model, const std::string &id, const std::string &smFileName);
			virtual ~Device();

			//inherit from PerformElement
			virtual void Start() override;
			virtual void Stop() override;
			virtual bool IsClosed() override;
			virtual bool pushEvent(const model::EventType_t &evt) override;
			virtual void mainEventLoop() override;

			//inherit from SendInterface
			virtual void fireSend(const std::string &strContent, const void * param) override;

		protected:
			void processSend(const std::string &strContent, const void * param, bool & bHandled);

		//private:
			std::map<std::string, Connction> m_Connections;
			const std::string m_SMFileName;
			helper::CEventBuffer<model::EventType_t> m_EvtBuffer;
		};
		typedef std::shared_ptr<Device>  DevicePtr;
	}
}