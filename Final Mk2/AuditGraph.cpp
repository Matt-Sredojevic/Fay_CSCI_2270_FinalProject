#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include "AuditGraph.h"
///This Project was edited by Matthew Sredojevic

//===================================================================================================================

AuditGraph::AuditGraph()
{
	std::fstream sizeDoc;
	sizeDoc.open("TableSize.txt");
	int res = 100;
	if (sizeDoc.is_open())
	{
		std::string l;
		std::getline(sizeDoc, l);
		std::stringstream ss(l);
		ss >> res;
		sizeDoc.close();
	}
	else
	{
		std::cerr << "TableSize.txt is missing" << std::endl;
		std::cout << std::endl;
	}
	all.reserve(res);
}

//===================================================================================================================

AuditGraph::~AuditGraph()
{
	std::fstream sizeDoc;
	sizeDoc.open("TableSize.txt", std::fstream::out | std::fstream::trunc);
	if(sizeDoc.is_open())
	{
		sizeDoc << all.size();
		sizeDoc.close();
	}
	minor.clear();
	electives.clear();
	complete.clear();
	all.clear();
}

//===================================================================================================================

void AuditGraph::readMinor()
{
	std::ifstream minor;
	std::string l;
	int spinner = 0;
	minor.open("CSCI Minor.txt");
	if(minor.is_open())
	{
		int j = 0;
		std::vector<ClassNode *> vec;
		while(getline(minor, l))
		{
			if(l=="and")
			{
				j++;
				spinner = 0;
				addMinor(vec);
				vec.clear();
			}
			else
			{
				std::string data, prefix, title;
				int number, hours;
				bool pre, co;
				std::istringstream line(l);
				while(getline(line, data, ','))
				{
					if(spinner==0)
					{
						prefix = data;
					}
					else if(spinner==1)
					{
						std::stringstream ss(data);
						ss >> number;
					}
					else if(spinner==2)
					{
						title = data;
						title.erase(title.begin());
					}
					else if(spinner==3)
					{
						std::stringstream ss(data);
						ss >> hours;
					}
					else if(spinner==4)
					{
						std::stringstream ss(data);
						ss >> pre;
					}
					else if(spinner==5)
					{
						std::stringstream ss(data);
						ss >> co;
						ClassNode * temp = addAll(prefix, number, title, hours, pre, co);
						vec.push_back(temp);
					}
					spinner = (spinner+1)%6;
				}
			}
		}
		addMinor(vec);
	}
}

//===================================================================================================================

void AuditGraph::readElective()
{
	std::ifstream elect;
	std::string l;
	int spinner = 0;
	elect.open("CSCI electives.txt");
	if(elect.is_open())
	{
		int j = 0;
		while(getline(elect, l))
		{
			std::string data, prefix, title;
			int number, hours;
			bool pre, co;
			std::istringstream line(l);
			while(getline(line, data, ','))
			{
				if(spinner==0)
				{
					prefix = data;
				}
				else if(spinner==1)
				{
					std::stringstream ss(data);
					ss >> number;
				}
				else if(spinner==2)
				{
					title = data;
					title.erase(title.begin());
				}
				else if(spinner==3)
				{
					std::stringstream ss(data);
					ss >> hours;
				}
				else if(spinner==4)
				{
					std::stringstream ss(data);
					ss >> pre;
				}
				else if(spinner==5)
				{
					std::stringstream ss(data);
					ss >> co;
					ClassNode * temp = addAll(prefix, number, title, hours, pre, co);
					electives.push_back(temp);
				}
				spinner = (spinner+1)%6;
			}
		}
	}
}

//===================================================================================================================

void AuditGraph::printElective()
{
    std::cout << "===========Electives===========" << std::endl;
	std::ifstream elect;
	std::string l;
	int spinner = 0;
	elect.open("CSCI electives.txt");
	if(elect.is_open())
	{
		int j = 0;
		while(getline(elect, l))
		{
			std::string data, prefix, title;
			int number, hours;
			bool pre, co;
			std::istringstream line(l);
			while(getline(line, data, ','))
			{
				if(spinner==0)
				{
					prefix = data;
					std::cout<<prefix<<"   ";
				}
				else if(spinner==1)
				{
					std::stringstream ss(data);
					ss >> number;
					std::cout<<number<<"   ";
				}
				else if(spinner==2)
				{
					title = data;
					title.erase(title.begin());
					std::cout<<title<<"   ";
				}
				else if(spinner==3)
				{
					std::stringstream ss(data);
					ss >> hours;
					std::cout<<"("<<hours<<")"<<std::endl;
				}
				spinner = (spinner+1)%6;
			}
		}
	}
	std::cout << std::endl;
}

//===================================================================================================================

void AuditGraph::listAll()
{
	std::cout << "============Classes============" << std::endl;
	for(int i=0; i<all.size(); i++)
	{
		std::cout << all[i].prefix << "   ";
		std::cout << all[i].number << "   ";
		std::cout << all[i].title << "   ";
		std::cout << "(" << all[i].hours << ")" << std::endl;
	}

}

//===================================================================================================================

void AuditGraph::listComplete()
{
	std::cout << "==============Classes Completed==============" << std::endl;
	for(int i=0; i<complete.size(); i++)
	{
		std::cout << complete[i]->prefix << "   ";
		std::cout << complete[i]->number << "   ";
		std::cout << complete[i]->title << "   ";
		std::cout << "(" << complete[i]->hours << ")" << std::endl;
	}
	std::cout << std::endl;
}

//===================================================================================================================

void AuditGraph::showReq(std::string prefix, int number)
{
	ClassNode * node = findNode(prefix, number);
	std::cout << std::endl;
	if(node==NULL)
	{
		std::cout << "Class not recognized" << std::endl;
		return;
	}
	if(node->prereq.size()==0)
	{
		std::cout << "No Prerequisites" << std::endl;
	}
	else
	{
		std::cout << "==========Prerequisites========== " << std::endl;
		for(int i=0; i<node->prereq.size(); i++)
		{
			for(int j=0; j<node->prereq[i].vec.size(); j++)
			{
				std::cout << node->prereq[i].vec[j]->prefix << "   ";
				std::cout << node->prereq[i].vec[j]->number << "   ";
				std::cout << node->prereq[i].vec[j]->title << "   ";
				std::cout << "(" << node->prereq[i].vec[j]->hours << ")" << std::endl;
				if(j<node->prereq[i].vec.size()-1)
				{
					std::cout << "or" << std::endl;
				}
			}
			if(i<node->prereq.size()-1)
			{
				std::cout << std::endl;
				std::cout << "--------AND--------" << std::endl;
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
	if(node->coreq.size()==0)
	{
		std::cout << "No Corequisites" << std::endl;
	}
	else
	{
		std::cout << "==========Corequisites========== " << std::endl;
		for(int i=0; i<node->coreq.size(); i++)
		{
			for(int j=0; j<node->coreq[i].vec.size(); j++)
			{
				std::cout << node->coreq[i].vec[j]->prefix << "   ";
				std::cout << node->coreq[i].vec[j]->number << "   ";
				std::cout << node->coreq[i].vec[j]->title << "   ";
				std::cout << "(" << node->coreq[i].vec[j]->hours << ")" << std::endl;
				if(j<node->coreq[i].vec.size()-1)
				{
					std::cout << "or" << std::endl;
				}
			}
			if(i<node->coreq.size()-1)
			{
				std::cout << std::endl;
				std::cout << "--------AND--------" << std::endl;
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

//===================================================================================================================

void AuditGraph::addMinor(std::vector<ClassNode *> vec)
{
	options * temp = new options;
	temp->vec = vec;
	temp->complete = false;
	minor.push_back(*temp);
}

//===================================================================================================================

void AuditGraph::addComplete(std::string prefix, int number)
{
	ClassNode * node = findNode(prefix, number);
	for(int i=0; i<complete.size(); i++)
	{
		if(complete[i]==node)
		{
			std::cout << "Class has already been completed" << std::endl;
			return;
		}
	}
	complete.push_back(node);
	for(int i=0; i<minor.size(); i++)
	{
		for(int j=0; j<minor[i].vec.size(); j++)
		{
			if(minor[i].vec[j]->title==node->title)
			{
				minor[i].complete = true;
				break;
			}
		}
	}
	for(int i=0; i<electives.size(); i++)
	{
		if(electives[i]->title==node->title)
		{
			totalHours = totalHours + electives[i]->hours;
		}
	}
}

//===================================================================================================================

ClassNode * AuditGraph::addAll(std::string prefix, int number, std::string title, int hours, bool pre, bool co)
{
	ClassNode * search = findNode(prefix, number);
	if(findNode(prefix, number)==NULL)
	{
		ClassNode * temp = new ClassNode;
		temp->prefix = prefix;
		temp->number = number;
		temp->title = title;
		temp->hours = hours;
		if(pre)
		{
			std::string file = "prereq/pre ";
			file.append(prefix);
			file.append(" ");
			std::stringstream ss;
			ss << number;
			std::string num = ss.str();
			file.append(num);
			file.append(".txt");
			getPRE(file, temp);
		}
		if(co)
		{
			std::string file = "coreq/co ";
			file.append(prefix);
			file.append(" ");
			std::stringstream ss;
			ss << number;
			std::string num = ss.str();
			file.append(num);
			file.append(".txt");
			getCO(file, temp);
		}
		all.push_back(*temp);
		return temp;
	}
	else
	{
		return findNode(prefix, number);
	}
}

//===================================================================================================================

void AuditGraph::getPRE(std::string file, ClassNode * node)
{
	std::ifstream PRE;
	std::string l;
	int spinner = 0;
	PRE.open(file.c_str());
	if(PRE.is_open())
	{
		int j = 0;
		std::vector<ClassNode *> vec;
		while(getline(PRE, l))
		{
			if(l=="and")
			{
				j++;
				spinner = 0;
				node->addPRE(vec);
				vec.clear();
			}
			else
			{
				std::string data, prefix, title;
				int number, hours;
				bool pre, co;
				std::istringstream line(l);
				while(getline(line, data, ','))
				{
					if(spinner==0)
					{
						prefix = data;
					}
					else if(spinner==1)
					{
						std::stringstream ss(data);
						ss >> number;
					}
					else if(spinner==2)
					{
						title = data;
						title.erase(title.begin());
					}
					else if(spinner==3)
					{
						std::stringstream ss(data);
						ss >> hours;
					}
					else if(spinner==4)
					{
						std::stringstream ss(data);
						ss >> pre;
					}
					else if(spinner==5)
					{
						std::stringstream ss(data);
						ss >> co;
						ClassNode * temp = addAll(prefix, number, title, hours, pre, co);
						vec.push_back(temp);
					}
					spinner = (spinner+1)%6;
				}
			}
		}
		node->addPRE(vec);
	}
}

//===================================================================================================================

void AuditGraph::getCO(std::string file, ClassNode * node)
{
	std::ifstream CO;
	std::string l;
	int spinner = 0;
	CO.open(file.c_str());
	if(CO.is_open())
	{
		int j = 0;
		std::vector<ClassNode *> vec;
		while(getline(CO, l))
		{
			if(l=="and")
			{
				j++;
				spinner = 0;
				node->addCO(vec);
				vec.clear();
			}
			else
			{
				std::string data, prefix, title;
				int number, hours;
				bool pre, co;
				std::istringstream line(l);
				while(getline(line, data, ','))
				{
					if(spinner==0)
					{
						prefix = data;
					}
					else if(spinner==1)
					{
						std::stringstream ss(data);
						ss >> number;
					}
					else if(spinner==2)
					{
						title = data;
						title.erase(title.begin());
					}
					else if(spinner==3)
					{
						std::stringstream ss(data);
						ss >> hours;
					}
					else if(spinner==4)
					{
						std::stringstream ss(data);
						ss >> pre;
					}
					else if(spinner==5)
					{
						std::stringstream ss(data);
						ss >> co;
						ClassNode * temp = addAll(prefix, number, title, hours, pre, co);
						vec.push_back(temp);
					}
					spinner = (spinner+1)%6;
				}
			}
		}
		node->addCO(vec);
	}
}

//===================================================================================================================

ClassNode * AuditGraph::findNode(std::string prefix, int number)
{
	for(int i=0; i<all.size(); i++)
	{
		if(all[i].prefix==prefix && all[i].number==number)
		{
			return &all[i];
		}
	}
	return NULL;
}

//===================================================================================================================

void AuditGraph::remaining()
{
	std::cout << "==========REMAINING REQUIREMENTS==========" << std::endl;
	bool done = true;
	for(int i=0; i<minor.size(); i++)
	{
		if(!minor[i].complete)
		{
			done = false;
			for(int j=0; j<minor[i].vec.size(); j++)
			{
				std::cout << minor[i].vec[j]->prefix << "   ";
				std::cout << minor[i].vec[j]->number << "   ";
				std::cout << minor[i].vec[j]->title << "   ";
				std::cout << "(" << minor[i].vec[j]->hours << ")" << std::endl;;
				if(j<minor[i].vec.size()-1)
				{
					std::cout << "or" << std::endl;
				}
			}
			std::cout << std::endl;
			std::cout << "--------AND--------" << std::endl;
			std::cout << std::endl;
		}
	}
	if(totalHours<6)
	{
		done = false;
		std::cout << "Complete another " << 6-totalHours << " credit hours of computer science electives" << std::endl;
	}
	else
	{
		std::cout << "No remaining electives needed for the 21 credit hour requirement" << std::endl;
	}
	if(done)
	{
		std::cout << "All requirements met! Congratulations!" << std::endl;
	}
	std::cout << std::endl;
}
