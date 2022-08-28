#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <Windows.h>
#include <fstream>
//包括纯值和变量
using namespace std;
class Variable {
public:
	//变量
	Variable(string str, bool literal) :_str(str), _is_literal(literal) {}
	bool IsLiteral() const { return _is_literal; }
	string GetString() const { return _str; };
private:
	bool _is_literal;
	string _str;;
};
//变量池
class VariablePool {
public:
	VariablePool(const unordered_map<string, string>& pairs)
		:_name_val(pairs){}
	string GetValue(const string& name){
		return _name_val[name];
	}
	void SetValue(const string& name, const string& val) {
		_name_val[name] = val;
	}
private:
	unordered_map<string, string> _name_val;
};

//Block
class Block {
public:
	Block(string exe_path,string block_name,string output_path,const vector<Variable>& params,string return_variable_name = "")
		:_exe_path(exe_path),_block_name(block_name),_output_path(output_path),_return(return_variable_name),_params(params) {}
	bool Run(VariablePool& pool) {
		string command = "\"\"" +_exe_path + "\" " + _block_name + " \"" + _output_path + "\"\"";
		for (int i = 0; i < _params.size(); i++) {
			string param;
			if (_params[i].IsLiteral()) {
				param = _params[i].GetString();
			}
			else {
				param = pool.GetValue(_params[i].GetString());
			}
			command += " " + param;
		}
		const char* c = command.c_str();
		system(c);
		ifstream f(_output_path);
		string state;
		getline(f, state);
		if (state == "FAIL") {
			_error_msg = "";
			getline(f, _error_msg);
			f.close();
			return false;
		}
		else {
			if (_return.length() != 0) {
				string res;
				getline(f, res);
				pool.SetValue(_return, res);
			}
			f.close();
			return true;
		}

	}
	string GetError()const { return _error_msg; }
private:
	string _exe_path, _block_name, _output_path, _return;
	string _error_msg;
	vector<Variable> _params;
};
enum OP{LS,LSEQ,GRT,GRTEQ,EQ,NEQ};
class Condition {
public:
	Condition(Variable& left, Variable& right, OP op) 
		:_left(left),_right(right),_op(op)
	{}
	bool Exeuse(VariablePool& pool) const {
		string l_str = _left.IsLiteral() ? _left.GetString() : pool.GetValue(_left.GetString());
		string r_str = _right.IsLiteral() ? _right.GetString() : pool.GetValue(_right.GetString());
		bool res = false;
		double lv = 0, rv = 0;
		switch (_op)
		{
		case LS:
			lv = atof(l_str.c_str());
			rv = atof(r_str.c_str());
			res = lv < rv;
			break;
		case LSEQ:
			lv = atof(l_str.c_str());
			rv = atof(r_str.c_str());
			res = lv <= rv;
			break;
		case GRT:
			lv = atof(l_str.c_str());
			rv = atof(r_str.c_str());
			res = lv > rv;
			break;
		case GRTEQ:
			lv = atof(l_str.c_str());
			rv = atof(r_str.c_str());
			res = (lv >= rv);
			break;
		case EQ:default:
			res = l_str == r_str;
			break;
		case NEQ:
			res = l_str != r_str;
			break;
		}
		return res;
	}
private:
	Variable _left, _right;
	OP _op;
};

class Branch {
public:
	Branch(const vector<Block>& segment,const Condition& condition):_segment(segment),_condition(condition) {}
	bool Check(VariablePool& pool) { return _condition.Exeuse(pool); }
	bool Run(VariablePool& pool) {
		bool success = true;
		for (int i = 0; i < _segment.size(); i++) {
			success = _segment[i].Run(pool);
			if (!success)
			{
				_error_msg = _segment[i].GetError();
				success = false;
			}
		}
		return success;
	}
	string GetError()const { return _error_msg; };
private:
	vector<Block> _segment;
	Condition _condition;
	string _error_msg;
};
class Loop {
public:
	Loop(const vector<Branch>& branches,const Condition& condition)
		:_branches(branches),_condition(condition) {}
	bool Run(VariablePool& pool) {
		while (_condition.Exeuse(pool)) {
			for (int i = 0; i < _branches.size(); i++) {
				if (_branches[i].Check(pool)) {
					_branches[i].Run(pool);
					break;
				}
			}
		}
		return true;
	}
	string GetError() const { return _error_msg; }
private:
	vector<Branch> _branches;
	Condition _condition;
	string _error_msg;
};
class Program {
public:
	Program(const vector<Loop>& loops, VariablePool& pool) :_loops(loops),_variable_pool(pool) {}
	bool Run() {
		for (int i = 0; i < _loops.size(); i++) {
			bool success = _loops[i].Run(_variable_pool);
			if (!success) {
				return false;
			}
		}
		system("pause");
		return true;
	}
private:
	vector<Loop> _loops;
	VariablePool _variable_pool;
	string _error_msg;
};