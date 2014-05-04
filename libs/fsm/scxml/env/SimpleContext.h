#pragma once
#ifndef _SCXML_ENV_SIMPLECONTEXT_HEADER_
#define _SCXML_ENV_SIMPLECONTEXT_HEADER_
#include "../Context.h"
#include <string>
#include <map>
#include <log4cplus/logger.h>

namespace fsm
{
namespace env
{
	class SimpleContext : public Context
	{

	private:

		log4cplus::Logger log;

	public:

		SimpleContext(); 
		virtual ~SimpleContext();
	
		SimpleContext(Context *const parent); //this(parent, nullptr);

		SimpleContext(std::map<std::string,std::string>const &initialVars); //this(nullptr, initialVars);

		SimpleContext(Context *const parent, std::map<std::string,std::string>const & initialVars);


		/// <summary>
		/// Clear this Context.
		/// </summary>
		/// <seealso cref= org.apache.commons.scxml.Context#reset() </seealso>
		virtual void Reset();

		virtual Context *getParent();

		virtual void setLocal(const std::string &name, const std::string & value,bool eventVar=true);

		
	protected:
		virtual void SetEventVars(const std::map<std::string,std::string> & vars);
		virtual void ClearEventVars();
		/// <summary>
		/// Get the Map of all local variables in this Context.
		/// </summary>
		/// <returns> Returns the vars. </returns>
	public:
		virtual std::map<std::string,std::string> & getEventVars();

		/// <summary>
		/// Set the log used by this <code>Context</code> instance.
		/// </summary>
		/// <param name="log"> The new log. </param>

		virtual std::string eval( const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode);
		virtual bool evalCond(const std::string &expr,const std::string &filename, unsigned int line,void *xmlNode);
		virtual void ExecuteFile(const std::string &fileName);


		virtual bool CompileScript(const std::string &script,const std::string &filename, unsigned int line,void*);
		virtual void SetContextPrivate(void *data);

	private:
		void InitializeInstanceFields();
	};
}
}

#endif // end simple context head file