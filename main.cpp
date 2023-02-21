/*******************************************/
/*     created by aben-ham 11/6/22         */
/*******************************************/
#include "headers/ft_containers_fox_test/fox.h"


class Tree{
public:
	typedef ft::BinaryNode<std::string> nodeType;
	typedef nodeType* nodePointer;

	enum{
		LEFT, RIGHT
	};

private:
	nodePointer _parent;
public:
	Tree(const std::string& nodeName) : _parent(new nodeType(nodeName)){
	}

	Tree(nodePointer node): _parent(node){}

public:
	int height(nodeType *node) const{
		if (!node)
			return (-1);
		int leftHeight = height(node->leftChild);
		int rightHeight = height(node->rightChild);
		return (std::max(leftHeight, rightHeight) + 1);
	}

	nodePointer addNode(nodePointer node, const std::string &nodeName, int pos){
		nodePointer newNode = new nodeType(nodeName);
		if (pos == LEFT)
			node->leftChild = newNode;
		else
			node->rightChild = newNode;
		return (newNode);
	}

	void	printTree(std::ostream &os = std::cout){
		int h = height(_parent) + 1;
		if (h >= 0)
			_parent->printTree(os, h);
	}

	nodePointer getRoot(){
		return _parent;
	}
};

//assuming that s1 is starting with '|"|(
const char *skip_quotes_and_parenthesis(const char *s1)
{
	int quotes;
	int parenth;

	if (*s1 == '\'')
		return (std::strchr(s1 + 1, '\'') + 1);
	if (*s1 == '"')
		return (std::strchr(s1 + 1, '"') + 1);
	quotes = 0;
	parenth = 1;
	s1++;
	while (*s1) {
		if (*s1 == '\'' || *s1 == '\"') {
			if (!quotes)
				quotes = *s1;
			else if (*s1 == quotes)
				quotes = 0;
		}
		if (quotes && s1++)
			continue;
		if (!parenth)
			break ;
		if (*s1 == '(')
			parenth++;
		if (*s1 == ')')
			parenth--;
		s1++;
	}
	return (s1);
}

bool split(const char* command, const char* token, const char **s1, const char **s2){
	const char *ptr;

	ptr = command;

	*s1 = command;
	while (*ptr){
		if (std::strchr("'\"(", *ptr)){
			ptr = skip_quotes_and_parenthesis(ptr);
		} else {
			if (*ptr == *token && *(ptr + 1) == *(token + 1)){
				*s2 = ptr + 2;
				return true;
			} else if (*ptr == *token && *(token + 1) != '|'){
				*s2 = ptr + 1;
				return true;
			}
			ptr++;
		}
	}
	return (false);
}

const char *first_operator(const char *command)
{
	const char *s1;
	const char *s2;
	const char *s3;
	bool res1;
	bool res2;

	res1 = split(command, "||", &s1, &s2);
	res2 = split(command, "&&", &s1, &s3);
	if (res1 && res2){
		if (s2 < s3)
			return (s2 - 2);
		else
			return (s3 - 2);
	}
	if (res1)
		return (s2 - 2);
	if (res2)
		return (s3 - 2);
	return (NULL);
}

const char *first_red(const char *command){
	const char *s;
	const char *s1;
	const char *s2;
	const char *s3;
	bool res1;
	bool res2;
	bool res3;

	res1 = split(command, ">", &s, &s1);
	res2 = split(command, "<<", &s, &s2);
	res3 = split(command, "<", &s, &s3);
	if (res1 && res2 && res3){
		if (s1 < s2 && s1 < s3)
			return (s1 - 1);
		if (s2 < s1 && s2 < s3)
			return (s2 - 2);
		return (s3 - 1);
	}
	if (res1 && res2){
		if (s1 < s2)
			return (s1 - 1);
		else
			return (s2 - 2);
	}
	if (res1 && res3){
		if (s1 < s3)
			return (s1 - 1);
		else
			return (s3 - 1);
	}
	if (res2 && res3){
		if (s2 < s3)
			return (s2 - 2);
		else
			return (s3 - 1);
	}
	if (res1)
		return (s1 - 1);
	if (res2)
		return (s2 - 2);
	if (res3)
		return (s3 - 1);
	return (NULL);
}

std::string remove_parenthesis(const char *str){
	const char *first = std::strchr(str, '(');
	const char *end = std::strrchr(str, ')');
	return (std::string(first + 1, end));
}

void	parse(Tree &tree, std::string command, Tree::nodePointer node){
	const char* s1;
	const char* s2;

	const char* firstOp = first_operator(command.c_str());
	if (firstOp){
		split(command.c_str(), std::string(firstOp, 2).c_str(), &s1, &s2);
		node->data = std::string(firstOp, 2);
		Tree::nodePointer n1 = tree.addNode(node, std::string(s1, s2 - 2), Tree::LEFT);
		Tree::nodePointer n2 = tree.addNode(node, std::string(s2), Tree::RIGHT);
		parse(tree, std::string(s1, s2 - 2), n1);
		parse(tree, std::string(s2), n2);
	}else{
		bool res = split(command.c_str(), "|", &s1, &s2);
		if (res){
			node->data = "|";
			Tree::nodePointer n1 = tree.addNode(node, std::string(s1, s2 - 1), Tree::LEFT);
			Tree::nodePointer n2 = tree.addNode(node, std::string(s2), Tree::RIGHT);
			parse(tree, std::string(s1, s2 - 1), n1);
			parse(tree, std::string(s2), n2);
		}else{
			const char* firstRedirection = first_red(command.c_str());
			if (firstRedirection && firstRedirection != command.c_str()){
				std::string tmp = std::string(command.c_str(), firstRedirection);
				s1 = tmp.c_str();
				s2 = firstRedirection;
				node->data = "R";
				Tree::nodePointer n1 = tree.addNode(node, std::string(s1), Tree::LEFT);
				Tree::nodePointer n2 = tree.addNode(node, std::string(s2), Tree::RIGHT);
				parse(tree, std::string(s1), n1);
				parse(tree, std::string(s2), n2);
			} else if (std::strchr(command.c_str(), '(')){
				std::string newCommand = remove_parenthesis(command.c_str());
				node->data = newCommand;
				parse(tree, newCommand, node);
			}
		}
	}
}

#include <unistd.h>
#include <string.h>
#include <sstream>

void exec(Tree::nodePointer node, int in, int out);

char** getCommandArgs(const std::string &command){
	std::vector<std::string> vector;
	std::istringstream iss(command);
	std::string token;
	while (std::getline(iss, token, ' ')){
		vector.push_back(token);
	}
	char **res = new char*[vector.size() + 1];
	int i = 0;
	for (std::vector<std::string>::iterator iter = vector.begin(); iter != vector.end(); ++iter){
		if (!iter->empty()){
			res[i] = new char[iter->size() + 1];
			std::strcpy(res[i], iter->c_str());
			res[i][iter->size()] = 0;
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}

void	ft_dup2(int f1, int f2)
{
	if (f1 == f2)
		return ;
	dup2(f1, f2);
	close(f1);
}

void exec_command(const std::string &command, int in, int out){
	int pid;

	pid = fork();
	if (pid == 0) {
		ft_dup2(in, 0);
		ft_dup2(out, 1);
		char **args = getCommandArgs(command);
		std::cerr << "*" << command << std::endl;
		if (execv(args[0], args) == -1)
			(std::cerr << "error" << std::endl, exit(1));
	}
	waitpid(pid, 0, 0);

}

void	pipe_nodes(Tree::nodePointer node, int in, int out)
{
	int	pid;
	int	fds[2];

	pipe(fds);
	pid = fork();
	if (!pid) {
		close(fds[0]);
		exec(node->leftChild, in, fds[1]);
		exit(0);
	}
	close(fds[1]);
	exec(node->rightChild, fds[0], out);
	close(fds[0]);
	waitpid(pid, 0, 0);
}

void exec(Tree::nodePointer node, int in, int out){
	if (node->data == "|") {
		pipe_nodes(node, in, out);
		return ;
	}
//	std::cerr << node->data << std::endl;
	exec_command(node->data, in, out);
}

void start(){
	Tree t = Tree(".");
	std::string command = "(/bin/ls -la | /usr/bin/wc) | ((/bin/cat) | /usr/bin/wc)";
	//std::string command = "ls | l";
	parse(t, command, t.getRoot());
	t.printTree();
	exec(t.getRoot(), 0, 1);
	//first_operator(command.c_str());

	//const char* s1;
	//const char* s2;
	//split(command.c_str(), "&&", &s1, &s2);

}

int main(){
	//mainTests();

	//Tree t = Tree("|");
	start();
	/*t.addNode(t.getRoot(), "ls", Tree::LEFT);
	Tree::nodePointer node1 = t.addNode(t.getRoot(), "|", Tree::RIGHT);
	t.addNode(node1, "A", Tree::LEFT);
	t.addNode(node1, "B", Tree::RIGHT);
	t.addNode(t.getRoot()->rightChild->rightChild, "|", Tree::LEFT);
	t.addNode(t.getRoot()->leftChild, "ls", Tree::RIGHT);*/

	//t.printTree();



	return (0);
}
