#include "StdAfx.h"
#include "HostListConfig.h"

HostListConfig::HostListConfig(void)
{
	m_pRootElement	= NULL;
	m_pDocument		= NULL;
}

HostListConfig::~HostListConfig(void)
{
	delete m_pDocument;
}

bool HostListConfig::Init( char* FilePath )
{
	m_pDocument = new TiXmlDocument(FilePath);
	if (NULL == m_pDocument)
	{
		return false;
	}
	m_pDocument->LoadFile();
	m_pRootElement = m_pDocument->RootElement();

	return true;
}

void HostListConfig::ReadHostList( std::vector<Host>& vtHostList )
{
	TiXmlElement* pHostListElement = m_pRootElement->FirstChildElement();
	TiXmlElement* pHostElement = pHostListElement->FirstChildElement();
	Host tempHost;
	for (;pHostElement != NULL;pHostElement = pHostElement->NextSiblingElement())
	{
		TiXmlAttribute* pName	= pHostElement->FirstAttribute();
		TiXmlAttribute* pIp		= pName->Next();
		TiXmlAttribute* pPort	= pIp->Next();
		strcpy(tempHost.name,pName->Value());
		strcpy(tempHost.ip,pIp->Value());
		tempHost.port = pPort->IntValue();
		vtHostList.push_back(tempHost);
	}
}

void HostListConfig::AddHost( Host host )
{
	TiXmlElement* pHostListElement = m_pRootElement->FirstChildElement();
	TiXmlElement* pHostElement = new TiXmlElement("Host");
	pHostListElement->LinkEndChild(pHostElement);
	pHostElement->SetAttribute("Name",host.name);
	pHostElement->SetAttribute("Ip",host.ip);
	pHostElement->SetAttribute("Port",host.port);
	m_pDocument->SaveFile();
}

void HostListConfig::DeleteHost( char* name )
{
	TiXmlElement* pHostListElement = m_pRootElement->FirstChildElement();
	/*pHostListElement->
	TiXmlElement* pHostElement = new TiXmlElement("Host");
	pHostListElement->LinkEndChild(pHostElement);
	pHostElement->SetAttribute("Name",host.name);
	pHostElement->SetAttribute("Ip",host.ip);
	pHostElement->SetAttribute("Port",host.port);
	m_pDocument->SaveFile();*/
}
