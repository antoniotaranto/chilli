#include "ACDModule.h"
#include "ACDExtension.h"
#include <log4cplus/loggingmacros.h>
#include "../tinyxml2/tinyxml2.h"
#include <json/json.h>


namespace chilli{
namespace ACD{


ACDModule::ACDModule(const std::string & id):ProcessModule(id)
{
	log =log4cplus::Logger::getInstance("chilli.ACDModule");
	LOG4CPLUS_DEBUG(log,"Constuction a ACD module.");
}


ACDModule::~ACDModule(void)
{
	LOG4CPLUS_DEBUG(log,"Destruction a ACD module.");
}


bool ACDModule::LoadConfig(const std::string & configContext)
{
	using namespace tinyxml2;
	tinyxml2::XMLDocument config;
	if(config.Parse(configContext.c_str()) != XMLError::XML_SUCCESS) 
	{ 
		LOG4CPLUS_ERROR(log, "load config error:" << config.ErrorName() << ":" << config.GetErrorStr1());
		return false;
	}
	
	for (XMLElement *child = config.FirstChildElement("Extension");
		child != nullptr;
		child = child->NextSiblingElement("Extension"))
	{
		const char * num = child->Attribute("ExtensionNumber");
		const char * sm = child->Attribute("StateMachine");
		num = num ? num : "";
		sm = sm ? sm : "";

		if (this->g_Extensions.find(num) == this->g_Extensions.end())
		{
			model::ExtensionPtr ext(new ACDExtension(this, num, sm));
			this->g_Extensions[num] = ext;
			this->m_Extensions[num] = ext;
		}
		else {
			LOG4CPLUS_ERROR(log, "alredy had extension:" << num);
		}
	}
	
	return true;
}


void ACDModule::fireSend(const std::string & strContent, const void * param)
{
	LOG4CPLUS_WARN(log, "fireSend not implement.");
}

}
}
