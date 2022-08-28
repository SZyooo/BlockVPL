#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
using std::string;
using std::vector;
using std::pair;
using std::unordered_map;
using std::ofstream;
using std::endl;

class Node;
extern const Node* EmptyRooNode;
class Node {
public:
	Node(string print_name,const Node* parent = EmptyRooNode):_print_name(print_name),_parent(parent) {
		if (parent == nullptr) {
			_parent = EmptyRooNode;
		}
	}
	virtual std::vector<std::string> PrintStatements()const = 0;
	void SetParent(Node* parent_node) {
		_parent = parent_node;
	}
	virtual string GetPrintName()const {
		return _parent->GetPrintName() + _print_name;
	}
private:
	const Node* _parent;
	string _print_name;
};
class EmptyNode :public Node {
public:
	virtual std::vector<std::string> PrintStatements()const { return {}; }
	EmptyNode() :Node("", nullptr) {}
	virtual string GetPrintName()const {
		return "";
	}
};
extern const Node* EmptyRooNode;


const string SPACE = " ";
const string TAB = "	";
class VariableNode :public Node {
public:
	//����variable_name������ left��right,parameter1�ȵ�
	//variable_str:����n���ȵ�
	VariableNode(string variable_type_name,int number,string variable_str, bool is_literal,const Node* parent = nullptr)
		:Node(variable_type_name + std::to_string(number), parent), _variable_str(variable_str), _is_literal(is_literal) {}
	virtual std::vector<std::string> PrintStatements()const {
		std::string statement("Variable ");
		statement += GetPrintName();
		std::string is_litaral;
		if (_is_literal) is_litaral = "true";
		else is_litaral = "false";
		statement += "(\"" + _variable_str + "\"," + is_litaral + ");";
		vector<string> res{statement};
		return res;
	}
private:
	//�������������� n
	std::string _variable_str;
	bool _is_literal;
};
enum OP{LESS,GREATER,LESSEQUAL,GREATEREQUAL,EQUAL,NONEQUAL};


class ConditionNode :public Node {
public:
	//Variable loop1conditionleft("n",false);
	//left:n	left_is_literal:false	parent_name:loop1condition
	ConditionNode(string left, bool left_is_literal,string right, bool right_is_literal, OP op, const Node* parent = nullptr)
		:Node("Condition",parent)
	{
		string left_print = GetPrintName() + "left";
		string right_print = GetPrintName() + "right";
		_left_node = new VariableNode(left_print,1,left,left_is_literal,this);
		_right_node = new VariableNode(right_print,2, right, right_is_literal,this);
;		switch (op)
		{
		case LESS:_op = "LS";break;
		case GREATER:_op = "GRT"; break;
		case LESSEQUAL:_op = "LSEQ";break;
		case GREATEREQUAL:_op = "GRTEQ"; break;
		case EQUAL:_op = "EQ";break;
		case NONEQUAL:_op = "NEQ";break;
		default:_op = "EQ";break;
		}
	}
	virtual std::vector<std::string> PrintStatements()const {
		vector<string> res;
		vector<string> l = _left_node->PrintStatements();
		vector<string> r = _right_node->PrintStatements();
		res.insert(res.end(), l.begin(), l.end());
		res.insert(res.end(), r.begin(), r.end());
		string statement = "Condition" + SPACE + GetPrintName() + "(" + _left_node->GetPrintName() + "," + _right_node->GetPrintName() + "," + _op + ");";
		res.push_back(statement);
		return res;
	}
	~ConditionNode()
	{
		delete _left_node; _left_node = nullptr;
		delete _right_node; _right_node = nullptr;
	}
private:
	VariableNode* _left_node, * _right_node;
	string _op;
};


//eg1��Block loop1branch1block1(exe, "PRINT", output, loop1branch1block1params);��������ֵ
//eg2��Block loop1branch1block2(exe, "ADD", output, loop1branch1block2params, "n");n������ֵ�����棨��ֵ�ַ���/��������
class BlockNode :public Node {
public:
	//<n,true>
	BlockNode(const vector<pair<string, bool>>& params,string block_name, int number,string exe, string output, string return_str,const Node* parent = nullptr)
		:Node("Block"+std::to_string(number), parent), _exe_path_name(exe), _output_path_name(output),_block_name(block_name), _return_variable_str(return_str)
	{
		for (int i = 0; i < params.size(); i++) {
			VariableNode* param = new VariableNode("Param",i, params[i].first, params[i].second,this);
			_params.push_back(param);
		}
	}
	virtual std::vector<std::string> PrintStatements()const {
		vector<string> res;
		string param_vec_name = GetPrintName() + "params";
		string state_param_vec = "vector<Variable>" + SPACE + param_vec_name + ";";
		res.push_back(state_param_vec);
		for (int i = 0; i < _params.size(); i++) {
			auto state_variable = _params[i]->PrintStatements();
			res.insert(res.end(), state_variable.begin(),state_variable.end());
			string push_back_state = param_vec_name + ".push_back(" + _params[i]->GetPrintName() + ");";
			res.push_back(push_back_state);
		}
		string block_dec =
			"Block" + SPACE + GetPrintName() + "(\"" + _exe_path_name + "\"," + "\"" + _block_name + "\",\"" + _output_path_name + "\"," + param_vec_name;
		if (_return_variable_str.length() == 0) {
			block_dec += ");";
		}
		else {
			block_dec += ",\"" + _return_variable_str + "\");";
		}
		res.push_back(block_dec);
		return res;
	}
	~BlockNode()
	{
		for (int i = 0; i < _params.size(); i++) {
			delete _params[i];
		}
	}
private:
	vector<VariableNode*> _params;
	string _exe_path_name, _output_path_name;//"xx.exe", "output.txt"
	string _block_name;//PRINT,ADD
	string _return_variable_str;//����ֵ���ַ��������յĻ���ʾ��������ֵ���߲����շ���ֵ,����2��n
};

class BranchNode :public Node {
public:
	BranchNode(const vector<BlockNode*>&blocks,int number,string left_variable_name,string right_variable_name,bool left_is_literal,bool right_is_literal,OP op,const Node* parent = nullptr)
        : Node("Branch" + std::to_string(number),parent),_blocks(blocks)
	{
        for(int i=0;i<_blocks.size();i++){
            _blocks[i]->SetParent(this);
        }
		_branch_condition = new ConditionNode(left_variable_name, left_is_literal, right_variable_name, right_is_literal, op,this);
	}
	virtual std::vector<std::string> PrintStatements()const {
		vector<string> res;
		string segment_print_name = GetPrintName() + "segment";
		string segment_dec = "vector<Block>" + SPACE + segment_print_name + ";";
		res.push_back(segment_dec);
		vector<string> condition_statements = _branch_condition->PrintStatements();
		res.insert(res.end(), condition_statements.begin(), condition_statements.end());
		for (int i = 0; i < _blocks.size(); i++) {
			vector<string> block_statements = _blocks[i]->PrintStatements();
			for (int i = 0; i < block_statements.size(); i++) {
				string stm = TAB + block_statements[i];
				res.push_back(stm);
			}
			string push_back_statement = segment_print_name + ".push_back(" + _blocks[i]->GetPrintName() + ");";
			res.push_back(push_back_statement);
		}
		string branch_dec = "Branch" + SPACE + GetPrintName() + "(" + segment_print_name + "," + _branch_condition->GetPrintName() + ");";
		res.push_back(branch_dec);
		return res;
	}
	~BranchNode()
	{
		for (int i = 0; i < _blocks.size(); i++) {
			delete _blocks[i];
		}
		delete _branch_condition;
	}
private:
	vector<BlockNode*> _blocks;
	ConditionNode* _branch_condition;
};

class LoopNode:public Node {
public:
	LoopNode(const vector<BranchNode*>& branches, int number, string left_variable_name, string right_variable_name, bool left_is_literal, bool right_is_literal, OP op, const Node* parent = nullptr)
		:Node("loop" + std::to_string(number), parent), _branches(branches), _loop_condition(new ConditionNode(left_variable_name, left_is_literal, right_variable_name, right_is_literal, op, this))
	{
		for (int i = 0; i < _branches.size(); i++) {
			_branches[i]->SetParent(this);
		}
	}
	virtual std::vector<std::string> PrintStatements()const {
		vector<string> res;
		vector<string> condition_statements = _loop_condition->PrintStatements();
		res.insert(res.end(), condition_statements.begin(), condition_statements.end());
		string branches_vec_name = GetPrintName() + "Branches";
		string branches_vec_dec = "vector<Branch>" + SPACE + branches_vec_name + ";";
		res.push_back(branches_vec_dec);
		for (int i = 0; i < _branches.size(); i++) {
			vector<string> branch_statements = _branches[i]->PrintStatements();
			for (auto& statement : branch_statements) {
				res.push_back(TAB + statement);
			}
			string push_back_statement = branches_vec_name + ".push_back(" + _branches[i]->GetPrintName() + ");";
			res.push_back(push_back_statement);
		}
		string loop_dec = "Loop" + SPACE + GetPrintName() + "(" + branches_vec_name + "," + _loop_condition->GetPrintName() + ");";
		res.push_back(loop_dec);
		return res;
	}
	~LoopNode()
	{
		for (int i = 0; i < _branches.size(); i++) {
			delete _branches[i];
		}
		delete _loop_condition;
	}
private:
	vector<BranchNode*> _branches;
	ConditionNode* _loop_condition;
};

class ProgramNode :public Node {
public:
	//unordered_map<string, string> poolmap{ {"n","1"}};
	ProgramNode(const vector<LoopNode*>& loops,const unordered_map<string,string>& pool_map)
		:Node("Program"), _loops(loops),_variable_pool(pool_map) {
		for (int i = 0; i < _loops.size(); i++) {
			_loops[i]->SetParent(this);
		}
	}
	virtual std::vector<std::string> PrintStatements()const {
		vector<string> res;
		string pool_map_name = "poolmap";
		string pool_map_dec = "unordered_map<string, string>" + SPACE + pool_map_name + ";";
		res.push_back(pool_map_dec);
		for (auto it = _variable_pool.begin(); it != _variable_pool.end(); it++) {
			string insert_statement = pool_map_name + ".insert({\"" + it->first + "\",\"" + it->second + "\"});";
			res.push_back(insert_statement);
		}
		string variable_pool_name = "pool";
		string variable_pool_dec = "VariablePool" + SPACE + variable_pool_name + "(" + pool_map_name + ");";
		res.push_back(variable_pool_dec);
		string loops_name = "loops";
		string loop_dec = "vector<Loop>" + SPACE + loops_name + ";";
		res.push_back(loop_dec);
		for (int i = 0; i < _loops.size(); i++) {
			vector<string> loop_statements = _loops[i]->PrintStatements();
			for (auto& statement : loop_statements) {
				res.push_back(TAB + statement);
			}
			string push_back_statement = loops_name + ".push_back(" + _loops[i]->GetPrintName() + ");";
			res.push_back(push_back_statement);
		}
		string program_name = GetPrintName();
		string program_dec = "Program" + SPACE + program_name + "(" + loops_name + "," + variable_pool_name + ");";
		res.push_back(program_dec);
		return res;
	}
	~ProgramNode()
	{
		for (int i = 0; i < _loops.size(); i++ ) {
			delete _loops[i];
		}
	}
private:
	vector<LoopNode*> _loops;
	unordered_map<string, string> _variable_pool;
};

class PageNode :public Node {
public:
	PageNode(ProgramNode* program) :Node(""), _program(program) {
		_program->SetParent(this);
	}
	virtual std::vector<std::string> PrintStatements()const {
		vector<string> res;
		string include_statement = "#include \"VRE.h\"";
		res.push_back(include_statement);
		string main_func_begin_state = "int main() {";
		res.push_back(main_func_begin_state);
		vector<string> program_statements = _program->PrintStatements();
		for (auto& statement : program_statements) {
			res.push_back(TAB + statement);
		}
		string run_program_statement = TAB + _program->GetPrintName() + ".Run();";
		res.push_back(run_program_statement);
		string main_func_end_state = "\n}";
		res.push_back(main_func_end_state);
		return res;
	}
	void PrintToCPPFile(ofstream& f) {
		vector<string> statements = PrintStatements();
		for (auto& statement : statements) {
			f << statement << endl;
		}
	}
	~PageNode()
	{
		delete _program;
	}
private:
	ProgramNode* _program;
};
