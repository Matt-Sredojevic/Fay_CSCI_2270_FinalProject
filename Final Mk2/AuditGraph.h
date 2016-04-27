#ifndef AUDITGRAPH_H
#define AUDITGRAPH_H
#include<vector>
#include<iostream>

struct ClassNode;

struct options
{
	bool complete;
	std::vector<ClassNode *> vec;
};

struct ClassNode
{
	std::string title;
	std::string prefix;
	int number;
	int hours;
	std::vector<options> prereq;
	std::vector<options> coreq;
	~ClassNode()
	{
		prereq.clear();
		coreq.clear();
	}
	void addPRE(std::vector<ClassNode *> vec)
	{
		options temp;
		temp.vec = vec;
		temp.complete = false;
		prereq.push_back(temp);
	}
	void addCO(std::vector<ClassNode *> vec)
	{
		options * temp = new options;
		temp->vec = vec;
		temp->complete = false;
		coreq.push_back(*temp);
	}
};

class AuditGraph
{
	public:
		AuditGraph();
		~AuditGraph();
		void readMinor();
		void readElective();
		void listAll();
		void listComplete();
		void showReq(std::string prefix, int number);
		void addMinor(std::vector<ClassNode *> vec);
		void addComplete(std::string prefix, int number);
		ClassNode * addAll(std::string prefix, int number, std::string title, int hours, bool pre, bool co);
		void getPRE(std::string file, ClassNode * node);
		void getCO(std::string file, ClassNode * node);
		void remaining();
	protected:
	private:
		std::vector<options> minor;
		std::vector<ClassNode *> electives;
		std::vector<ClassNode *> complete;
		std::vector<ClassNode> all;
		int totalHours;
		ClassNode * findNode(std::string prefix, int number);
};

#endif // AUDITGRAPH_H
